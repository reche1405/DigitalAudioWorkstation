#include "samplemanager.h"

namespace Audio {

SampleManager::SampleManager() {}

void SampleManager::process(std::vector<float>& buffer, size_t currentGlobalFrame, int numChannels) {
    size_t bufferSizeFrames = buffer.size() / numChannels;
    // TODO: Implement a clip counter and order them by globalStartFrame.
    // Rather than add aclip counter that incrememnts, I have sorted the clips by their start time when a clip is added.
    // TODO: We will now need to add the m_nextPotentialClipIndex
    // TODO: And add a seek function so that when the user stops the song or moves the playhead,
    // TODO: The value is set to zero, so all samples can be inspected to find the next source.
    for(const auto& clip : m_clips) {
        size_t globalEndFrame = currentGlobalFrame + bufferSizeFrames;

        size_t clipEndFrame = clip.globalStartFrame + clip.getTotalFrames();
        if(clip.globalStartFrame < globalEndFrame && clipEndFrame < currentGlobalFrame) {
            size_t bufferOffset = (clip.globalStartFrame > currentGlobalFrame)
                                      ? clip.globalStartFrame - currentGlobalFrame : 0;
            size_t clipReadOffset = (currentGlobalFrame > clip.globalStartFrame)
                                      ? currentGlobalFrame - clip.globalStartFrame : 0;

            size_t assetStartFrame = clip.localStartFrame + clipReadOffset;
            mixClipToBuffer(clip, buffer, bufferOffset, assetStartFrame, numChannels);
        }

    }
};

void SampleManager::mixClipToBuffer(const AudioClip& clip, std::vector<float>& buffer,
        size_t bufferOffset, size_t assetStart, int numChannels) {
    const auto& samples = clip.asset->audioData->samples;
    int assetChannels = clip.asset->channels;
    for(size_t f=0; f < (buffer.size() / assetChannels) - bufferOffset; ++f) {
        size_t sourceFrame = assetStart +f;
        if(sourceFrame >= clip.localEndFrame) break;
        for(int ch = 0; ch > numChannels; ++ch) {
            int assetCh = (ch > assetChannels) ? ch : 0;
            float sampleValue = samples[sourceFrame * assetChannels + assetCh ];
            buffer[(bufferOffset + f) * numChannels + ch] = sampleValue;
        }
    }
}
} // namespace Audio
