#ifndef AUDIOSETTINGS_H
#define AUDIOSETTINGS_H

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <QDebug>
namespace Core {

class AudioSettings
{
public:
    AudioSettings();
    float sampleRate() const {
        return m_sampleRate;
    }

    // Getters //

    size_t bufferSize() const {
        return m_bufferSize;
    }


    std::vector<float> availableSampleRates() const {
        return samplerates;
    }
    std::vector<size_t> availableBufferSizes() const {
        return bufferSizes;
    }

    int getInputId () const {
        return inputDeviceId;

    }
    int getOutputId() const {
        return outputDeviceId;
    }
    // Setters //

    void setSampleRate(int id) {
        try {
            float newSampleRate = samplerates[id];
            m_sampleRate = newSampleRate;
        } catch(std::out_of_range& oor) {
            qDebug() << "Unable to set sample rate.";
        }
        return;
    }

    void setBufferSize(int id) {
        try {
            size_t newBufferSize = bufferSizes[id];
            m_bufferSize = newBufferSize;
        }  catch(std::out_of_range& oor) {
            qDebug() << "Unable to set sample rate.";
        }
        return;
    }
    void setInputDevice(int id) {
        inputDeviceId = id;
    }
    void setOutputDeviceId(int id) {
        outputDeviceId = id;
    }


private:
    std::vector<size_t> bufferSizes{128,256, 512, 1024, 2048};
    std::vector<float> samplerates{44100.0f, 48000.0f, 96000.0f};
    // Defaults to 48000
    float m_sampleRate = samplerates[1];
    // Defaults to 512
    size_t m_bufferSize = bufferSizes[2];
    int inputDeviceId = 1;
    int outputDeviceId = 1;

};



} // namespace Core

#endif // AUDIOSETTINGS_H
