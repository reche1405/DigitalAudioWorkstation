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
    virtual void process(Audio::AudioBuffer& audioBuffer, Midi::MidiBuffer& midiBuffer);
    std::string title() const {return m_title;}
    void setTitle(std::string newTitle) {m_title = newTitle; }
private:
    std::string m_title;
};

} // namespace Intruments

#endif // INSTRUMENTNODE_H
