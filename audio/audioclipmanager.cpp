#include "audioclipmanager.h"
#include "../core/math.h"
#include "../core/musictimemanager.h"
namespace Audio {

AudioClipManager::AudioClipManager() {}

void AudioClipManager::process(std::vector<float>& buffer, size_t currentGlobalFrame, int numChannels) {
    size_t bufferSizeFrames = buffer.size() / numChannels;
    // TODO: Implement a clip counter and order them by globalStartFrame.
    // Rather than add aclip counter that incrememnts, I have sorted the clips by their start time when a clip is added.
    // TODO: We will now need to add the m_nextPotentialClipIndex
    // TODO: And add a seek function so that when the user stops the song or moves the playhead,
    // TODO: The value is set to zero, so all samples can be inspected to find the next source.

    Core::MusicTimeManager& manager = Core::MusicTimeManager::instance();

    size_t globalEndFrame = currentGlobalFrame + bufferSizeFrames;
    for(const auto& clip : m_clips) {

        size_t clipEndFrame = manager.getGlobalEndFrame(clip);
        size_t clipGlobalStartFrame = manager.getGlobalStartFrame(clip);
        if(clipGlobalStartFrame < globalEndFrame && clipEndFrame > currentGlobalFrame) {
            size_t bufferOffset = (clipGlobalStartFrame > currentGlobalFrame)
                                      ? clipGlobalStartFrame - currentGlobalFrame : 0;
            size_t clipReadOffset = (currentGlobalFrame > clipGlobalStartFrame)
                                      ? currentGlobalFrame - clipGlobalStartFrame : 0;

            size_t assetStartFrame = clipGlobalStartFrame + clipReadOffset;
            mixClipToBuffer(clip, buffer, bufferOffset, assetStartFrame, numChannels);
        }

    }
};

void AudioClipManager::mixClipToBuffer(const AudioClip& clip, std::vector<float>& buffer,
        size_t bufferOffset, size_t assetStart, int numChannels) {
    Core::MusicTimeManager& manager = Core::MusicTimeManager::instance();
    const auto& samples = clip.asset->audioData->samples;
    int assetChannels = clip.asset->channels;

    double ratio = static_cast<double>(clip.asset->sampleRate) / static_cast<double>(m_projectSampleRate);

    size_t bufferFrames = buffer.size() / numChannels;
    size_t framesToProcess = bufferFrames - bufferOffset;

    for(size_t f=0; f < framesToProcess; ++f) {
        size_t sourceFrame = static_cast<double>(assetStart + f) * ratio;

        size_t indexA = static_cast<size_t>(sourceFrame);
        size_t indexB = indexA + 1;
        float fraction = static_cast<float>(sourceFrame - indexA);
        size_t clipLocalEndFrame = manager.getLocalEndFrame(clip);
        if(indexA >= clipLocalEndFrame || (indexB * assetChannels) >= samples.size()) break;
        for(int ch = 0; ch < numChannels; ++ch) {
            int assetCh = (ch < assetChannels) ? ch : 0;

            float sA = samples[indexA * assetChannels + assetCh];
            float sB = samples[indexB * assetChannels + assetCh];

            float interpolated = Core::Math::lerp(sA, sB, fraction);

            buffer[(bufferOffset + f) * numChannels + ch] += interpolated;
        }
    }
}
} // namespace Audio
