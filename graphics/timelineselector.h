#ifndef TIMELINESELECTOR_H
#define TIMELINESELECTOR_H

#include <cstdint>
namespace Graphics {



class TimelineSelector
{
public:
    TimelineSelector();


private:
    // The frame that the playhead returns to when audio playback is stopped.

    uint64_t m_editFrame;

};

} // namespace Graphics

#endif // TIMELINESELECTOR_H
