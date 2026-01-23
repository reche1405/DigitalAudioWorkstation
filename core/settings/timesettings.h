#ifndef TIMESETTINGS_H
#define TIMESETTINGS_H

#include <vector>
namespace Core {

class TimeSettings
{
private:
    std::vector<int> countOptions{2, 4, 8, 16, 32};
    float m_bpm = 120.0f;
    int m_beatsPerBar = 4;
    int m_countsPerBeat = countOptions[1];
    size_t ticksPerQuarter = 960;
public:
    TimeSettings();

    float bpm() const {
        return m_bpm;
    }

    std::pair<int, int> timeSignature() const {
        int barBeats = m_beatsPerBar;
        int beatCounts = m_countsPerBeat;
        return std::pair(barBeats, beatCounts);
    }

    size_t tpq() const {
        return ticksPerQuarter;
    }


};

} // namespace Core

#endif // TIMESETTINGS_H
