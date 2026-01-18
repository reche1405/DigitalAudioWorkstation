#include "track.h"

namespace Core {
void BaseTrack::addEffect(std::unique_ptr<Audio::AudioNode> effect) {
    m_chain.addEffect(std::move(effect));
}
void BaseTrack::setName(std::string name) {
    m_name = QString::fromStdString(name);
}

} // namespace Core
