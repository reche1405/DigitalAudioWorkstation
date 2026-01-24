#include "mixer.h"
#include "../audio/audiotrack.h"
#include "../midi/miditrack.h"
namespace Core {

void Mixer::addNewTrack(Core::TrackType type) {
    if(type == Core::TrackType::Audio) {
        auto track = std::make_unique<Audio::AudioTrack>();
        m_tracks.push_back(std::move(track));
    }

    // else if (type == Core::TrackType::MIDI) {
    //     auto track = std::make_unique<Midi::MidiTrack>();
    //     m_tracks.push_back(std::move(track));
    // }
    // TODO: Once we have abstracted track, this will be an else statememnt
    // And the above will be a make uniwue Audio::AudioTrack
}

void Mixer::mixMasterBuffer(Audio::AudioBuffer buffer)
{
    size_t samplesToProcess = buffer.size();
    size_t numFrames = samplesToProcess / 2;
        m_masterBuffer = buffer;
    float leftGain = 0.5f;
    float rightGain = 0.5f;

    for (uint32_t i = 0; i < numFrames; ++i) {
        // Interleaved L/R
        m_masterBuffer.samples[i * 2]     *= leftGain;  // Left
        m_masterBuffer.samples[i * 2 + 1] *= rightGain; // Right

        // Hard Limiter (Simple protection)
        m_masterBuffer.samples[i * 2]     = std::clamp(m_masterBuffer.samples[i * 2], -1.0f, 1.0f);
        m_masterBuffer.samples[i * 2 + 1] = std::clamp(m_masterBuffer.samples[i * 2 + 1], -1.0f, 1.0f);
    }

}
} // namespace Core
