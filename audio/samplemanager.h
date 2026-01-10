#ifndef SAMPLEMANAGER_H
#define SAMPLEMANAGER_H

#include <vector>
#include "audiostructs.h"
namespace Audio {

class SampleManager
{
private:
    std::vector<AudioClip> m_clips;
    uint32_t m_projectSampleRate = 44100;
public:
    SampleManager();
    void addClip(AudioClip clip) {

        m_clips.push_back(clip);
        std::sort(m_clips.begin(), m_clips.end());
    }
    std::vector<AudioClip> clips() const {return m_clips;}
    void removeClip(AudioClip clip);
    void setGlobalStartFrame(AudioClip clip, size_t globalStart);
    void setLocalStartFrame(AudioClip clip, size_t localStart);
    void setLocalEndFrame(AudioClip clip, size_t endFrame);
    void process(std::vector<float>& buffer, size_t currentGlobalFrame, int numChannels);
    void mixClipToBuffer(const AudioClip& clip, std::vector<float>& buffer, size_t bufferOffset, size_t assetStartFrame, int numChannels);
    void prepare(uint32_t sampleRate);
};

} // namespace Audio

#endif // SAMPLEMANAGER_H
