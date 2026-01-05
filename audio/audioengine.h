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
            m_ringBuffer(new CoreUtils::RingBuffer<float>(1024)),
            m_transport(new CoreUtils::Transport()) {
            RtAudio audio;
            m_dac = audio;

            // Open the default output device and
            // If there is an error then print to the console.


            if(!(openDevice(m_dac.getDefaultOutputDevice()))) {
                qWarning() << "Error opening device";
            };
        };
        ~AudioEngine();
        bool openDevice(unsigned int id);
        void closeStream();
        int processAudio(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames);
        void initialize();
    private:
        RtAudio m_dac;
        RtAudio::StreamParameters m_parameters;
        int outputDeviceId;
        int inputDeviceId;
        CoreUtils::RingBuffer<float> *m_ringBuffer;
        CoreUtils::Transport *m_transport;
    };
}

#endif // AUDIOENGINE_H
