#include "mixer.h"

namespace Core {

void Mixer::addNewTrack(Core::TrackType type) {
    if(type == Core::TrackType::Audio) {
        auto track = std::make_unique<Audio::AudioTrack>();
        m_tracks.push_back(std::move(track));
    }
    // TODO: Once we have abstracted track, this will be an else statememnt
    // And the above will be a make uniwue Audio::AudioTrack
}

void Mixer::mixMasterBuffer(size_t samplesToProcess, uint64_t writePos, uint32_t numFrames)
{

        std::fill(m_masterBuffer.begin(), m_masterBuffer.begin() + samplesToProcess , 0.0f);
    for (auto& t : m_tracks) {
        std::fill(m_trackBuffer.begin(), m_trackBuffer.begin() + samplesToProcess , 0.0f);
        // TODO: pass the current frame from this globaltimeline manager: URGENT
        t->process(m_trackBuffer, writePos);

        for(int i = 0; i < m_masterBuffer.size(); i++) {
            m_masterBuffer[i] += m_trackBuffer[i];
        }
    }

    float leftGain = 0.5f;
    float rightGain = 0.5f;

    for (uint32_t i = 0; i < numFrames; ++i) {
        // Interleaved L/R
        m_masterBuffer[i * 2]     *= leftGain;  // Left
        m_masterBuffer[i * 2 + 1] *= rightGain; // Right

        // Hard Limiter (Simple protection)
        m_masterBuffer[i * 2]     = std::clamp(m_masterBuffer[i * 2], -1.0f, 1.0f);
        m_masterBuffer[i * 2 + 1] = std::clamp(m_masterBuffer[i * 2 + 1], -1.0f, 1.0f);
    }

}
} // namespace Core
