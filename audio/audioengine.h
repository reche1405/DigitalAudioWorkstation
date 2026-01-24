#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include "../core/ringbuffer.h"
#include "../core/transport.h"
#include "RtAudio.h"
#include "QDebug"
#include <thread>
#include "../core/mixer.h"
#include "../core/audiothreadpool.h"
namespace Audio {

    class AudioEngine
    {
    public:
        AudioEngine() :
            m_ringBuffer(new Core::RingBuffer<float>(16384 * 2)),
            m_transport(new Core::Transport())
                {
            // Open the default output device and
            // If there is an error then print to the console.
            RtAudio::DeviceInfo info = m_dac.getDeviceInfo(1);
            qDebug() << "Output channels: " << info.outputChannels;

        };
        ~AudioEngine() {
            m_dac.stopStream();
        };
        bool openDevice(unsigned int id, unsigned int _sampleRate, unsigned int _bufferFrames);
        void closeStream();
        int writeToBuffer(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames);

        void renderIntoBuffer(float* buffer, uint32_t chunk, int64_t startFrame);

        void initialize();
        void play() const {m_transport->play();}
        void pause() const {m_transport->pause();}



        void addNewTrack(Core::TrackType type = Core::TrackType::Audio);
        void mixMasterBuffer(uint32_t bufferSize);

        Core::Transport& transport() const {return *m_transport;}
        Core::RingBuffer<float>& ringBuffer() const {return *m_ringBuffer;}
        Core::Mixer& mixer() {return m_mixer;}


        // Todo, implement the below on their own loops.
        void trackLoop();
        void mixMasterLoop();


    private:
        RtAudio m_dac;
        RtAudio::StreamParameters m_parameters;
        int outputDeviceId;
        int inputDeviceId;
        Core::RingBuffer<float> *m_ringBuffer;
        Core::Transport *m_transport;
        int m_debugCounter = 0;
        Core::Mixer m_mixer;
        Core::AudioThreadPool m_threadPool;

        std::atomic<bool> needsMix{false};
        std::mutex mixMutex;

    };
}

#endif // AUDIOENGINE_H
