#ifndef MUSICTIME_H
#define MUSICTIME_H
#include "QString"
namespace CoreUtils {

enum class NotationDetail : int {BAR = 1, BEAT = 2, COUNT = 3};

    struct MusicTime
    {
    public:
        MusicTime(int64_t bar = 1, int beat = 1, int count = 1, int ticks=0);
        void setBar(int64_t bar);
        void setBeat(int beat);
        void setCount(int count);
        void setTick(int tick);
        int getBar() const {return m_bar; }
        int getBeat() const {return m_beat; }
        int getCount() const {return m_count; }
        float getTicks() const {return m_tick; }
        QString toString(NotationDetail lod = NotationDetail::BAR) const {
            QString output = QString::number(m_bar + 1);
            if (lod > NotationDetail::BAR) {
                QString beats = QString::number(m_beat + 1);
                output.append(".");
                output.append(beats);
            }
            if(lod > NotationDetail::BEAT) {
                output.append(".");
                QString counts = QString::number(m_count);
                output.append(counts);
            }
            return output;
        }

    private:
        int64_t m_bar;
        int m_beat;
        int m_count;
        float m_tick;
    };


}

#endif // MUSICTIME_H
