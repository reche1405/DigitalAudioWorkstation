#include "audioengine.h"
#include "QDebug"
#include "QString"
#include <stdint.h>
namespace Audio {

    static int audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                                 double srteamTime, RtAudioStreamStatus status, void *userData) {

        AudioEngine *engine = static_cast<AudioEngine*>(userData);
        return engine->writeToBuffer(outputBuffer, inputBuffer, nBufferFrames);
    }



    bool AudioEngine::openDevice(unsigned int id, unsigned int _sampleRate, unsigned int _bufferFrames) {
        m_parameters.deviceId = m_dac.getDefaultOutputDevice();
        m_parameters.nChannels = 2;
        m_parameters.firstChannel = 0;

        unsigned int sampleRate = _sampleRate;
        unsigned int bufferFrames = _bufferFrames;
        try {
            m_dac.openStream(&m_parameters, nullptr,RTAUDIO_FLOAT32,
                             sampleRate, &bufferFrames, &Audio::audioCallback, this);
            m_dac.startStream();
            //qDebug() << "Device stream opened";
            return true;
        } catch(RtAudioError &e) {
            qDebug() << "Stream Error:" << QString::fromStdString(e.getMessage());
            return false;
        }
    }



    int AudioEngine::writeToBuffer(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames) {
        if (!m_transport) return 0; // Essential safety check!
        float *buffer = static_cast<float*>(outputBuffer);
        unsigned int framesToProcess = nBufferFrames * 2;
        unsigned int samplesRead = m_ringBuffer->popBlock(buffer,framesToProcess);

        if(samplesRead < framesToProcess) {
            std::fill(buffer + samplesRead, buffer + framesToProcess, 0.0f);
            // printf("UNDERFLOW: Only read %u of %u\n", samplesRead, framesToProcess);
        }
        m_transport->updatePosition(samplesRead / 2);
        return 0;
    }

    void AudioEngine::addNewTrack(Core::TrackType type)
    {
        m_mixer.addNewTrack(type);
    }

    void AudioEngine::mixMasterBuffer(uint32_t bufferSize)
    {
        if(!m_transport->isPlaying()) {
            return;
        }
        int64_t playhead = m_transport->getCurrentFrame();
        int64_t waiting = m_ringBuffer->availableSamples() / 2;
        int64_t writePos = playhead + waiting;
        size_t nSamples = bufferSize * 2;
        Audio::AudioBuffer buffer;
        buffer.init();
        std::atomic tracksComplete{0};
        std::condition_variable cv;
        std::mutex mtx;
        auto& tracks = m_mixer.tracks();
        int trackCount = tracks.size();
        for (auto &track : tracks) {
            m_threadPool.enqueue([&track, &tracksComplete, &cv, &mtx, &nSamples, &writePos, &buffer, &trackCount]() {
                track->process(buffer,writePos);

                std::lock_guard lock(mtx);
                if(++tracksComplete == trackCount) {
                    cv.notify_one();
                }
            });
        }
        {
            std::unique_lock lock(mtx);
            cv.wait_for(lock,std::chrono::milliseconds(10), [&tracksComplete, &trackCount]() {
                return tracksComplete == trackCount;
            });
        }
        m_mixer.mixMasterBuffer(buffer);



        // 4. Push to Ring Buffer
        // We try to push the entire block. If it returns less than numFrames*2,
        // it means the ring buffer is full (the audio engine is falling behind).
        size_t pushed = m_ringBuffer->pushBlock(m_mixer.masterBuffer().data(), bufferSize);

    }

}
