#ifndef AUDIOCLIPMANAGER_H
#define AUDIOCLIPMANAGER_H

#include <vector>
#include "audiostructs.h"
#include "../core/clipmanager.h"
namespace Audio {

class AudioClipManager : public Core::ClipManager
{
private:
    std::vector<AudioClip> m_clips;
    uint32_t m_projectSampleRate = 44100;
public:
    AudioClipManager();
    void addClip(AudioClip clip) {

        m_clips.push_back(clip);
        std::sort(m_clips.begin(), m_clips.end());
    }
    std::vector<AudioClip> clips() const {return m_clips;}
    void removeClip(AudioClip clip);
    void setGlobalStartFrame(AudioClip clip, size_t globalStart);
    void setLocalStartFrame(AudioClip clip, size_t localStart);
    void setLocalEndFrame(AudioClip clip, size_t endFrame);
    void process(AudioBuffer& buffer, size_t currentGlobalFrame, int numChannels);
    void mixClipToBuffer(const AudioClip& clip, AudioBuffer& buffer, size_t bufferOffset, size_t assetStartFrame, int numChannels);
    void prepare(uint32_t sampleRate) override {m_projectSampleRate = sampleRate;};
};

} // namespace Audio

#endif // AUDIOCLIPMANAGER_H
