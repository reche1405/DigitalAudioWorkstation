#include "musictime.h"
namespace CoreUtils {
    MusicTime::MusicTime(int64_t bar, int beat, int count, int tick) {
        m_bar = bar;
        m_beat = beat;
        m_count = count;
        m_tick = tick;
    }

    void MusicTime::setBar(int64_t bar) {
        this->m_bar = bar;
    }
    void MusicTime::setBeat(int beat) {
        this->m_beat = beat;
    }
    void MusicTime::setCount(int count) {
        this->m_count = count;
    }
    void MusicTime::setTick(int tick) {
        this->m_tick = tick;
    }
}
