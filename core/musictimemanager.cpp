#include "musictimemanager.h"
#include "QDebug"
namespace CoreUtils {

    MusicTimeManager::MusicTimeManager() {
        //float bpm,
        // int beatsPerBar, int beatLength,int sampleRate) {
        // float second = 1000.0;
        // float minute = 60.0;
        // m_bpm = bpm;
        // m_beatsPerBar = beatsPerBar;
        // m_beatLength = beatLength;
        // float beatsPerSecond = bpm / minute;
        // m_msPerBeat = (1.0 / beatsPerSecond) * second;
        // m_sampleRate = sampleRate;
        qInfo() << "Intialised music time manager";
    }
    MusicTimeManager& MusicTimeManager::instance() {
        static MusicTimeManager musicManager;

        return musicManager;
    }


    MusicTime MusicTimeManager::ticksToNotation(int64_t totalTicks) {
        MusicTime mt;
        int64_t ticksPerBar = getTicksPerBar();

        int64_t remainder = totalTicks;
        mt.setBar(remainder / ticksPerBar);
        remainder %= ticksPerBar;
        mt.setBeat(remainder / m_pointsPerQuarter);
        remainder %= m_pointsPerQuarter;
        mt.setTick((int)remainder);

        return mt;
    }
    int64_t MusicTimeManager::getTicksPerBar() {
        int ticksPerSixteenth = m_pointsPerQuarter / m_beatLength;
        int sixteenthBeat = m_beatLength;
        int beatsPerBar = m_beatsPerBar;
        int64_t ticksPerBar = (int64_t)m_pointsPerQuarter * beatsPerBar;
        return ticksPerBar;
    }

    int64_t MusicTimeManager::framesToTicks(int totalFrames) {
        double frames =  (double)totalFrames * (m_pointsPerQuarter * m_bpm) / (60.0 * m_sampleRate);
        return static_cast<int64_t>(frames + 0.5f);
    }

    size_t MusicTimeManager::ticksToFrames(int64_t totalTicks)
    {
        double seconds = (double)totalTicks / (m_bpm / 60.0f * m_pointsPerQuarter);
        return static_cast<size_t>(seconds * m_sampleRate);

    }

    size_t MusicTimeManager::getGlobalStartFrame(const Clip &clip)
    {
        return ticksToFrames(clip.globalStartTick);
    }

    size_t MusicTimeManager::getLocalEndFrame(const Clip &clip)
    {
        return ticksToFrames(clip.localEndTick);
    }

    size_t MusicTimeManager::getGlobalEndFrame(const Clip &clip)
    {
        return ticksToFrames(clip.globalEndTick());
    }




    MusicTime MusicTimeManager::countsToNotation(qreal counts) {
        counts = fmax(counts,(qreal) 0.0);
        MusicTime mt(1,1,1,0.0);
        qreal beats = 0;
        qreal bars = 0;
        //qDebug() << "Counts: " << counts;

        if(counts >= m_beatLength) {
            beats = int(counts / (int)m_beatLength);
            counts = (int)counts %  (int)m_beatLength;
        }
        //qDebug() << "Counts after beat caclc" << counts;
        //qDebug() << "Beats after beat calc" << beats;

        if(beats >= m_beatsPerBar) {
            bars = (int)(beats / (int)(m_beatsPerBar));
            beats = (int)beats % (int)(m_beatsPerBar);
        }
        mt.setCount((int)counts + 1);
        mt.setBar((int)bars + 1);
        mt.setBeat((int)beats + 1);
        return mt;
    }

    MusicTime MusicTimeManager::msToNotation(float ms) {
        // 120 beats in a minute / 60 to get beats per second = 2.0,  1.0 / return value is the total beats
        // imagine 500 ms was passed
        // this(500.0)
        // we need to calculate how many beats that is with ms_per_beat
        // then use a function that takes a number of beats and creates a
        // Music time, that this function will then return
        float msPerBeat = m_msPerBeat;
        int beat = 1;
        int bar = 1;
        int count = 1;
        float subCountMs = 0.0;
        float temp = ms;
        // While the temp time is greater than or equal to a 6th count.
        while (temp >= msPerBeat / m_beatLength) {
            // if temp is greater than a bar
            if (temp >= msPerBeat * m_beatsPerBar) {
                bar += 1;
                temp -= (msPerBeat * m_beatsPerBar);
            // Else if temps is greater than a beat
            } else if (temp >= msPerBeat) {
                beat += 1;
                temp -= msPerBeat;
            } else if (temp > msPerBeat / m_beatLength) {
                while(temp >= msPerBeat / m_beatLength) {
                    count += 1;
                    temp -= msPerBeat / m_beatLength;
                }
            }
        }
        // Here temp is less than a 64th count in milliseconds.
        // Eg 120BPM 4/4 500ms per beat, 125ms per count
        // 0.0 -> 124.9;
        if(temp > 0.0) {
            subCountMs = temp;
            temp -= temp;
        }

        MusicTime mt(beat,bar,count, subCountMs);
        return mt;


    }

    float MusicTimeManager::notationToMs(MusicTime mt) {
        int bars, beats, counts;
        bars = mt.getBar();
        beats = mt.getBeat();
        counts = mt.getCount();
        float ms = 0.0;
        while (bars > 1) {
            ms += m_msPerBeat * m_beatsPerBar;
                bars -= 1;
        }
        while (beats > 1) {
            ms += m_msPerBeat;
            beats -=1;
        }
        while (counts < 1) {
            ms += m_msPerBeat / m_beatLength;
            counts -= 1;
        }
        return ms;
    }

    int MusicTimeManager::notaionToSamples(MusicTime mt) {
        float ms = notationToMs(mt);
        return static_cast<int>((ms / 1000) * m_sampleRate);
    }

    MusicTime MusicTimeManager::samplesToNotation(int samples) {
        float ms = (samples / m_sampleRate) * 1000;
        return msToNotation(ms);
    }

    void MusicTimeManager::setBpm(float bpm) {
        m_bpm = bpm;
    }

    void MusicTimeManager::setSampleRate(int sampleRate) {
        m_sampleRate = sampleRate;
    }

    void MusicTimeManager::setTimeSignature(int beatsPerBar, int beatLength) {
        m_beatsPerBar = beatsPerBar;
        m_beatLength = beatLength;
    }
    MusicTime MusicTimeManager::addTimes(MusicTime first, MusicTime second) {
        float combinedMs = 100;
        int combinedBars = 0;
        int combinedBeats = 0;
        int combinedCounts = 0;

         MusicTime mt(1,1,1,0.0);
        // If the combined milliseconds are smaller than a count
        if (!(combinedMs >= m_msPerBeat / m_beatLength)) {
             // mt.setMs(combinedMs);
        } else {
            // Otherwise, while they are, decrease the value of a count and add a temporary count
            while(combinedMs >= m_msPerBeat / m_beatLength) {

                combinedCounts += 1;
                combinedMs -= m_msPerBeat / m_beatLength;
            }
            // mt.setMs(combinedMs);
        }
        combinedCounts += first.getCount() + second.getCount();

        if (!(combinedCounts >= m_beatLength)) {
            mt.setCount(combinedCounts);
        } else {
            while(combinedCounts >= m_beatLength) {
                combinedBeats += 1;
                combinedCounts -= m_beatLength;
            }
            mt.setCount(combinedCounts);
        }

        combinedBeats += first.getBeat() + second.getBeat();
        if (combinedBeats >= m_beatsPerBar) {
            while(combinedBeats >= m_beatsPerBar) {
                combinedBars += 1;
                combinedBeats -= m_beatsPerBar;
            }
        }
        mt.setBeat(combinedBeats);

        combinedBars += first.getBar() + second.getBar();
        mt.setBar(combinedBars);
        return mt;
    }
    void MusicTimeManager::setPointsPerQuarter(int ppq) {
        m_pointsPerQuarter = ppq;
    }
}
