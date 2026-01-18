#ifndef MIDICLIPMANAGER_H
#define MIDICLIPMANAGER_H

#include "../core/clipmanager.h"
#include "midistructs.h"
namespace Midi {

class MidiClipManager : public Core::ClipManager
{
private:
    std::vector<MidiClip> m_clips;
    // At a later point, messages may also be coming from this midi buffer.

    uint32_t m_projectSampleRate;
public:
    MidiClipManager();
    void addClip(MidiClip clip);
    void prepare(uint32_t sampleRate) override {m_projectSampleRate = sampleRate;};
    void addToMidiBuffer(MidiBuffer& midiBuffer);

};

} // namespace Midi

#endif // MIDICLIPMANAGER_H
