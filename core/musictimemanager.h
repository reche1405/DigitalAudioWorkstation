#ifndef MUSICTIMEMANAGER_H
#define MUSICTIMEMANAGER_H

#include <memory>
#include "musictime.h"
namespace CoreUtils {
    class MusicTimeManager
    {
    private:

        float m_bpm;
        int m_beatsPerBar;
        int m_beatLength;
        int m_sampleRate;
        int m_pointsPerQuarter; // The total amount of points in a qaurter note.
        float m_msPerBeat;


        MusicTimeManager(const MusicTimeManager&) = delete;
        MusicTimeManager& operator=(const MusicTimeManager&) = delete;

        MusicTime formatBeats(MusicTime mt);
        MusicTime formatBars(MusicTime mt);

    public:
        //The bpm such as 120.00 indicates the speed of the track,
        // Beats per bar is the numerator of timesignature, beatLength is
        // The number of 64th notes in a beat. this can only be 2, 4, 8, 16.

        explicit MusicTimeManager();
        using SharedPtr = std::shared_ptr<MusicTimeManager>;
        static MusicTimeManager& instance();


        // The correct way to convert any timeline information ito musicTime would be to use the below.
        // We then need to find out how many ticks there are
        MusicTime ticksToNotation(int64_t totalTicks);
        int64_t framesToTicks(int totalFrames);


        MusicTime msToNotation(float ms);
        float notationToMs(MusicTime mt);
        int notaionToSamples(MusicTime mt);
        MusicTime countsToNotation(qreal counts);
        MusicTime samplesToNotation(int samples);
        int notationToCounts(MusicTime mt);

        void setBpm(float bpm);
        void setTimeSignature(int beatsPerBar, int beatLength);
        void setSampleRate(int sampleRate);
        void setPointsPerQuarter(int ppq);
        MusicTime addTimes(MusicTime first, MusicTime second);
        float getBMP() const {return m_bpm; }

        int64_t getTicksPerBar();
        int getPointsPerQuarter() const {return m_pointsPerQuarter; }
        int getBeatsPerBar() const {return m_beatsPerBar; }
        int getBeatLength() const {return m_beatLength; }
        int getCountsPerBar() const {return m_beatsPerBar * m_beatLength; }

    };


    enum Interval : int {
        SIXTEEN_BAR = 1024,
        EIGHT_BAR = 512,
        FOUR_BAR = 264,
        TWO_BAR = 128,
        BAR = 64,
        HALF_BAR = 32,
        QUARTER_BAR =16 ,
        EIGHTH_BAR = 8,
        SIXTEENTH_BAR = 4,
        THIRTYSECONDTH_BAR = 2,
        SIXTYFORTH_BAR = 1
    };
}

#endif // MUSICTIMEMANAGER_H
