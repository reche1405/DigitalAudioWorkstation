#ifndef MIXER_H
#define MIXER_H

#include <memory>
#include "../core/track.h"
#include "../audio/audionode.h"

#include <vector>
namespace Core {

class Mixer
{
public:
    Mixer() {

        m_masterBuffer.init(2048, 0.0f);
        m_trackBuffer.init(2048, 0.0f);
    }
    ~Mixer() = default;

    void mixMasterBuffer(uint32_t numFrames);
    void addNewAudioTrack();
    // void addNewMidiTrack();
    void addNewTrack(TrackType type = TrackType::Audio);
    void mixMasterBuffer(size_t samplesToProcess, uint64_t writePos, uint32_t numFrames);
    Audio::AudioBuffer masterBuffer() const {return m_masterBuffer;}
    std::vector<std::unique_ptr<Core::BaseTrack>>& tracks() {return m_tracks;}

private:
    Audio::AudioBuffer m_masterBuffer;
    Audio::AudioBuffer m_trackBuffer;
    std::vector<std::unique_ptr<Core::BaseTrack>> m_tracks;
    Audio::ProcessChain m_masterChain;
};

} // namespace Core

#endif // MIXER_H
