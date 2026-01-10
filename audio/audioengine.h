#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include "../core/ringbuffer.h"
#include "../core/transport.h"
#include "RtAudio.h"
#include "QDebug"
namespace Audio {

    class AudioEngine
    {
    public:
        AudioEngine() :
            m_ringBuffer(new CoreUtils::RingBuffer<float>(16384 * 2)),
            m_transport(new CoreUtils::Transport()) {

            // Open the default output device and
            // If there is an error then print to the console.
            RtAudio::DeviceInfo info = m_dac.getDeviceInfo(1);
            qDebug() << "Output channels: " << info.outputChannels;

        };
        ~AudioEngine();
        bool openDevice(unsigned int id, unsigned int _sampleRate, unsigned int _bufferFrames);
        void closeStream();
        int processAudio(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames);

        void renderIntoBuffer(float* buffer, uint32_t chunk, int64_t startFrame);

        void initialize();

        void play() const {m_transport->play();}
        void pause() const {m_transport->pause();}

        CoreUtils::Transport& transport() const {return *m_transport;}
        CoreUtils::RingBuffer<float>& ringBuffer() const {return *m_ringBuffer;}
    private:
        RtAudio m_dac;
        RtAudio::StreamParameters m_parameters;
        int outputDeviceId;
        int inputDeviceId;
        CoreUtils::RingBuffer<float> *m_ringBuffer;
        CoreUtils::Transport *m_transport;
        int m_debugCounter = 0;
    };
}

#endif // AUDIOENGINE_H
