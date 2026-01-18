#ifndef MIDICLIPMANAGER_H
#define MIDICLIPMANAGER_H

#include "../core/clipmanager.h"
#include "midistructs.h"
namespace Midi {

class MidiClipManager : public Core::ClipManager
{
private:
    std::vector<MidiClip> m_clips;
    uint32_t m_projectSampleRate;
public:
    MidiClipManager();
    void addClip(MidiClip clip) {
        m_clips.push_back(clip);
        std::sort(m_clips.begin(), m_clips.end());
    };
    void prepare(uint32_t sampleRate) override {m_projectSampleRate = sampleRate;};

    // The clip manager will search for any midi events that occur between current
    // global tick (readTick) and bufferSizeTicks. and return a list of these results as a reference.
    std::vector<MidiEvent> getEventsForBuffer(int64_t readTick, int64_t bufferSizeTicks );

    // The below function will then turn all of these event references into midi messages
    // the sample offset of the midi message will be the event.tick - readTick
    void mixEventsToMidiBuffer(std::vector<MidiEvent> events, MidiBuffer& midiBuffer, int64_t readTick);

};

} // namespace Midi

#endif // MIDICLIPMANAGER_H
