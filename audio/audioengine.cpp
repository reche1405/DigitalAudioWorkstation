#include "audioengine.h"
#include "QDebug"
#include "QString"
#include <stdint.h>
namespace Audio {

    static int audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                                 double srteamTime, RtAudioStreamStatus status, void *userData) {

        AudioEngine *engine = static_cast<AudioEngine*>(userData);
        return engine->processAudio(outputBuffer, inputBuffer, nBufferFrames);
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



    int AudioEngine::processAudio(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames) {
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
        // std::fill(buffer, buffer +(nBufferFrames * 2), 0.0f);
        // if (!m_transport) return 0;

        // if(!m_transport->isPlaying()) {
        //     for(unsigned int i=0; i<nBufferFrames*2; i++) buffer[i] = 0.001f;
        //     return 0;}


        // while(completedSamples < totalFramesToProcess) {
        //     m_debugCounter++;
        //     if (m_debugCounter % 100 == 0) {
        //         //qDebug() << "Callback active. Current Frame:" << m_transport->getCurrentFrame();
        //     }
        //     unsigned int samplesRemaining = totalFramesToProcess - completedSamples;
        //     uint32_t chunk = m_transport->getSamplesUntilLoopEnd(samplesRemaining);

        //     if (chunk > 0) {

        //         renderIntoBuffer(buffer + (completedSamples * 2 ), chunk, m_transport->getCurrentFrame());
        //         m_transport->updatePosition(chunk);
        //         completedSamples += chunk;
        //     } else {
        //         if(m_transport->isLooped()) {
        //             m_transport->setToLoopStart();
        //                 if (m_transport->getSamplesUntilLoopEnd(samplesRemaining) == 0) break;
        //         } else {
        //             break;
        //         }
        //     }

        // }
        // return 0;
    }

}
