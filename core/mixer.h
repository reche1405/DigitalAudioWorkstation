#ifndef MIXER_H
#define MIXER_H

#include <memory>
#include "../audio/track.h"
#include "../audio/audionode.h"
#include <vector>
namespace Core {

class Mixer
{
public:
    Mixer();
    void mixMasterBuffer(uint32_t numFrames);
    void addNewAudioTrack();
    // void addNewMidiTrack();
    void addNewTrack(TrackType type = TrackType::Audio);
private:
    std::vector<float> m_masterBuffer;
    std::vector<float> m_trackBuffer;
    std::vector<std::unique_ptr<Audio::BaseTrack>> m_tracks;
    Audio::ProcessChain m_masterChain;
    void mixMasterBuffer(size_t samplesToProcess, uint64_t writePos, uint32_t numFrames);
};

} // namespace Core

#endif // MIXER_H
