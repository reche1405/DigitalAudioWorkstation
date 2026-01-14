#include "transport.h"

namespace Core {

Transport::Transport() {}
void Transport::toggleLoop() {
    bool current = m_isLooped.load();
    m_isLooped.store(!current);
}


void Transport::updatePosition(uint32_t numFrames) {

    if(!m_isPlaying) {
        return;
    }
    m_currentFrame += numFrames;
    int64_t currentSnapshot = m_currentFrame.load();
    int64_t loopEndSnapshot = m_loopEnd.load();
    if(m_isLooped.load() && currentSnapshot > loopEndSnapshot) {
        int64_t overflow = currentSnapshot - loopEndSnapshot;
        m_currentFrame.store(m_loopStart.load() + overflow);
    }
}

uint32_t Transport::getSamplesUntilLoopEnd(uint32_t numSamplesRequested) {
    if (!m_isLooped.load()) {
        return numSamplesRequested;
    }
    int64_t current = m_currentFrame.load();
    int64_t end = m_loopEnd.load();
    if (current > end ) return 0;
    int64_t samplesToLimit = end - current;
    return static_cast<uint32_t>( std::min<int64_t>((int64_t)numSamplesRequested, samplesToLimit));
}

void Transport::setPosition(int64_t newFrame) {
    m_currentFrame.store(newFrame);
}
void Transport::setToLoopStart() {
    m_currentFrame.store(m_loopStart.load());
}
} // namespace CoreUtils
