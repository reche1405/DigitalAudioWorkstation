#include "audiotrack.h"

namespace Audio {

AudioTrack::AudioTrack() : BaseTrack()

{
    m_type = Core::TrackType::Audio;
};
// This is a custom process function for an audio track, there will aslos be a custom process function
// For a MIDI track.
void AudioTrack::process(size_t playheadFrame) {
    // Fill the buffer with 0s
    int numChannels = 2;
    size_t bufferFrames = m_audioBuffer.capacity() / 2;
    // Get the sampler to fill the buffer with data
    m_sampler.localProcess(playheadFrame, numChannels, bufferFrames);

    m_audioBuffer.processBlock([this](float* data, size_t size) {
        m_sampler.toTrackBuffer(data, size);

    } );

    // // m_chain.process(buffer);
    // for(size_t i = 0; i < buffer.size(); i+= numChannels ) {
    //     float currentGain = m_gain.getNextValue();
    //     float currentPan = m_pan.getNextValue();

    //     float left = std::clamp(1.0f - currentPan, 0.0f, 1.0f);
    //     float right = std::clamp(1.0f + currentPan, 0.0f, 1.0f);

    //     buffer.samples[i] *= (currentGain * left);
    //     buffer.samples[i + 1] += (currentGain * right);
    // }
}


} // namespace Audio

