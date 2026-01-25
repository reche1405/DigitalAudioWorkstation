#include "audiotrack.h"

namespace Audio {

AudioTrack::AudioTrack() : BaseTrack()

{
    m_type = Core::TrackType::Audio;
};
// This is a custom process function for an audio track, there will aslos be a custom process function
// For a MIDI track.
void AudioTrack::process(AudioBuffer& buffer, size_t playheadFrame) {
    // Fill the buffer with 0s
    std::fill(buffer.samples.begin(), buffer.samples.end(), 0.0f);
    int numChannels = 2;
    // Get the sampler to fill the buffer with data
    m_sampler.process(buffer, playheadFrame, numChannels);
    m_audioBuffer.processBlock([this] )

    m_chain.process(buffer);
    for(size_t i = 0; i < buffer.size(); i+= numChannels ) {
        float currentGain = m_gain.getNextValue();
        float currentPan = m_pan.getNextValue();

        float left = std::clamp(1.0f - currentPan, 0.0f, 1.0f);
        float right = std::clamp(1.0f + currentPan, 0.0f, 1.0f);

        buffer.samples[i] *= (currentGain * left);
        buffer.samples[i + 1] += (currentGain * right);
    }
}


} // namespace Audio

