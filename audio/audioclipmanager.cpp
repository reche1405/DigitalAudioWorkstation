#include "audioclipmanager.h"
#include "../core/math.h"
#include "../core/musictimemanager.h"
namespace Audio {

AudioClipManager::AudioClipManager() {}


void AudioClipManager::prepare(int numChannels, size_t bufferSize, uint32_t sampleRate)
{
    m_numChannels = numChannels;
    m_projectSampleRate = sampleRate;
    size_t requiredSize = bufferSize * numChannels;
    if(m_scratchBuffer.size() < requiredSize) {
        m_scratchBuffer.resize(requiredSize, 0.0f);
        m_scratchBufferSize = requiredSize;
    }
}

void AudioClipManager::localProcess(size_t currentGlobalFrame, int numChannels, size_t framesToProcess)
{
    std::fill(m_scratchBuffer.begin(), m_scratchBuffer.begin() + (framesToProcess * numChannels), 0.0f);

    Core::MusicTimeManager& manager = Core::MusicTimeManager::instance();

    size_t globalEndFrame = currentGlobalFrame + framesToProcess;
    for(const auto& clip : m_clips) {

        size_t clipEndFrame = manager.getGlobalEndFrame(clip);
        size_t clipGlobalStartFrame = manager.getGlobalStartFrame(clip);
        if(clipGlobalStartFrame < globalEndFrame && clipEndFrame > currentGlobalFrame) {
            size_t bufferOffset = (clipGlobalStartFrame > currentGlobalFrame)
            ? clipGlobalStartFrame - currentGlobalFrame : 0;
            size_t clipReadOffset = (currentGlobalFrame > clipGlobalStartFrame)
                                        ? currentGlobalFrame - clipGlobalStartFrame : 0;

            size_t assetStartFrame = clipGlobalStartFrame + clipReadOffset;
            mixClipToBuffer(clip, bufferOffset, assetStartFrame, numChannels);
        }

    }

}

void AudioClipManager::toTrackBuffer(float *trackBuffer, size_t size)
{
    if(!m_bufferReady) {
        return;
    }
    size_t copySize = std::min(size, m_scratchBufferSize);
    std::memcpy(trackBuffer, m_scratchBuffer.data(), copySize * sizeof(float));

    markBufferConsumed();
}


void AudioClipManager::mixClipToBuffer(const AudioClip& clip,
        size_t bufferOffset, size_t assetStart, int numChannels) {
    Core::MusicTimeManager& manager = Core::MusicTimeManager::instance();
    const auto& samples = clip.asset->audioData->samples;
    int assetChannels = clip.asset->channels;

    double ratio = static_cast<double>(clip.asset->sampleRate) / static_cast<double>(m_projectSampleRate);

    size_t bufferFrames = m_scratchBufferSize / numChannels;
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

            m_scratchBuffer[(bufferOffset + f) * numChannels + ch] += interpolated;
            // m_bufferReady.store(true);
        }
    }
}

 void AudioClipManager::process(AudioBuffer& buffer, size_t currentGlobalFrame, int numChannels) {

};


} // namespace Audio
