#ifndef INSTRUMENTNODE_H
#define INSTRUMENTNODE_H

#include "../audio/audionode.h"
#include "../midi/midinode.h"
namespace Intruments {

class InstrumentNode : public Audio::AudioNode, public Midi::MidiNode
{
public:
    virtual ~InstrumentNode() = default;
};

} // namespace Intruments

#endif // INSTRUMENTNODE_H
