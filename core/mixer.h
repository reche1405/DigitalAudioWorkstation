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

    float *mixMasterBuffer(size_t numFrames);
    void addNewAudioTrack();
    // void addNewMidiTrack();
    void addNewTrack(TrackType type = TrackType::Audio);
    void mixMasterBuffer(Audio::AudioBuffer buffer);
    Audio::AudioBuffer masterBuffer() const {return m_masterBuffer;}
    std::vector<std::unique_ptr<Core::BaseTrack>>& tracks() {return m_tracks;}



private:

    int m_nMasterChannels = 2;
    Audio::AudioBuffer m_masterBuffer;
    Audio::AudioBuffer m_trackBuffer;
    std::vector<std::unique_ptr<Core::BaseTrack>> m_tracks;
    Audio::ProcessChain m_masterChain;
};

} // namespace Core

#endif // MIXER_H
