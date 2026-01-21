#ifndef TRANSPORT_H
#define TRANSPORT_H
#include <algorithm>
#include <atomic>
#include <stdint.h>
#include "QDebug"
namespace Core {

class Transport
{
public:
    Transport();
    void play() {
        qDebug() << "The transport is playing";
        m_isPlaying.store(true);}
    void stop() {
        m_isPlaying = false;
        m_currentFrame = 0;
    }
    void pause() {
        m_isPlaying.store(false);
        m_currentFrame = 0;
    }
    void toggleLoop();

    void updatePosition(uint32_t numFrames);

    uint32_t getSamplesUntilLoopEnd(uint32_t numSamplesRequested);

    bool isPlaying()  {return m_isPlaying.load(); }

    bool isLooped() {return m_isLooped.load();}
    int64_t getCurrentFrame()  {return m_currentFrame.load();}
    void setPosition(int64_t newFrame);
    void setToLoopStart();


private:
    std::atomic<bool> m_isPlaying {false};
    std::atomic<bool> m_isLooped {false};
    std::atomic<int64_t> m_currentFrame {0};
    std::atomic<int64_t> m_loopStart {0};
    std::atomic<int64_t> m_loopEnd {44100 * 2};
};

} // namespace CoreUtils

#endif // TRANSPORT_H
