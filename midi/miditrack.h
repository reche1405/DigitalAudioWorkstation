#ifndef MIDITRACK_H
#define MIDITRACK_H
#include "../core/track.h"
#include "midiclipmanager.h"
#include "midinode.h"
#include "../instruments/instrumentnode.h"

namespace Midi {

class MidiTrack : public Core::BaseTrack
{
public:
    MidiTrack();
    void processAudio(Audio::AudioBuffer& buffer, size_t currentGlobalFrame, int numChannels);
    void processMidi(size_t currentGlobalFrame, int numChannels);
    void process(Audio::AudioBuffer& buffer, size_t currentGlobalFrame, int numChannels);
    // The plan is for process to call process midi in which the midi clip, any midi effects, and
    // Eventually the midi dispatcher process a vector of midi events into a midi buffer.

    // The midi buffer can then be passed to the instrument at hand.
    // The instrument internally process the midi and writes to the audio buffer reference.
    // The audio buffer is then processed by reference in the process chain.
    // This is void as the referenced audiobuffer is mixed in the audio mixer
    // elsewhere.

    // This will be used to dispatch events to the local midiBuffer.
    void addEvent(MidiEvent event, int samplePosition) {m_midiBuffer.addEvent(event, samplePosition);}
private:
    MidiChain m_midiChain;
    std::unique_ptr<Instruments::InstrumentNode> m_instrument;
    Audio::ProcessChain m_processChain;
    MidiBuffer m_midiBuffer;
    MidiClipManager m_clipManager;

};

} // namespace Midi

#endif // MIDITRACK_H
