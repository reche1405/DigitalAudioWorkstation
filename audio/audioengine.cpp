#include "audioengine.h"
#include "QDebug"
#include "QString"

namespace Audio {

    static int audioCallback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                                 double srteamTime, RtAudioStreamStatus status, void *userData) {
        AudioEngine *engine = static_cast<AudioEngine*>(userData);
        return engine->processAudio(outputBuffer, inputBuffer, nBufferFrames);
    }



    bool AudioEngine::openDevice(unsigned int id) {
        m_parameters.deviceId = id;
        m_parameters.nChannels = 2;
        m_parameters.firstChannel = 0;

        unsigned int sampleRate = 44100;
        unsigned int bufferFrames = 256;

        try {
            m_dac.openStream(&m_parameters, nullptr,RTAUDIO_FLOAT32,
                             sampleRate, &bufferFrames, &audioCallback, this);
            m_dac.startStream();
            return true;
        } catch(RtAudioError &e) {
            qDebug() << "Stream Error:" << QString::fromStdString(e.getMessage());
            return false;
        }
    }



    int AudioEngine::processAudio(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames) {
        float *buffer = static_cast<float*>(outputBuffer);
        for (unsigned int i=0; i < nBufferFrames * 2; i++) {
            buffer[i] = 0.0f;
        }
        return 0;
    }
}
