#include "track.h"

namespace Core {
void BaseTrack::addEffect(std::unique_ptr<Audio::AudioNode> effect) {
    m_chain.addEffect(std::move(effect));
}
void BaseTrack::setName(std::string name) {
    m_name = QString::fromStdString(name);
}

void BaseTrack::mixToMaster(float* src, float* dest, size_t numFrames)
{
    m_audioBuffer.readBlock(src, numFrames);

    for(size_t i = 0; i< numFrames; i++) {
        dest[i] += src[i];
    }

}

} // namespace Core
