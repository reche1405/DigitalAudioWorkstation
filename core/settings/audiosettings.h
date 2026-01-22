#ifndef AUDIOSETTINGS_H
#define AUDIOSETTINGS_H

#include <cstddef>
#include <vector>
namespace Core {

class AudioSettings
{
public:
    AudioSettings();
private:
    std::vector<size_t> bufferSizes{128,256, 512, 1024, 2048};
    std::vector<double> samplerates{44100, 48000, 96000};
    double m_sampleRate = 48000;
    size_t m_bufferSize = bufferSizes[2];
};

} // namespace Core

#endif // AUDIOSETTINGS_H
