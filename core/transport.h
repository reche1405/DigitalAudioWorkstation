#ifndef TRANSPORT_H
#define TRANSPORT_H
#include <atomic>
namespace CoreUtils {

class Transport
{
public:
    Transport();
    void play() {m_isPlaying = true;}
    void stop() {
        m_isPlaying = false;
        m_currentFrame = 0;
    }
    void updatePosition(int numFrames) {
        if(!m_isPlaying) return;
        m_currentFrame += numFrames;

    }
private:
    std::atomic<bool> m_isPlaying {false};
    std::atomic<bool> m_isLooped {false};
    std::atomic<int64_t> m_currentFrame {0};
    std::atomic<int64_t> m_loopStart {0};
    std::atomic<int64_t> m_loopEnd {44100 * 4};
};

} // namespace CoreUtils

#endif // TRANSPORT_H
