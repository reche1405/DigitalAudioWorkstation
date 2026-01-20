#ifndef INSTRUMENTNODE_H
#define INSTRUMENTNODE_H

#include "../audio/audionode.h"
#include "../midi/midinode.h"
namespace Instruments {

class InstrumentNode : public Audio::AudioNode, public Midi::MidiNode
{
public:
    virtual ~InstrumentNode() = default;
    virtual void processMidi() = 0;
    virtual void process(std::vector<float>& audioBuffer, Midi::MidiBuffer& midiBuffer);
};

} // namespace Intruments

#endif // INSTRUMENTNODE_H
