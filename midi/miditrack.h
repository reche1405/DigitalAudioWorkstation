#ifndef MIDITRACK_H
#define MIDITRACK_H
#include "../core/track.h"
#include "midinode.h"

namespace Midi {

class MidiTrack : public Core::BaseTrack
{
public:
    MidiTrack();
private:
    MidiChain m_midiChain;
    Audio::ProcessChain m_processChain;
};

} // namespace Midi

#endif // MIDITRACK_H
