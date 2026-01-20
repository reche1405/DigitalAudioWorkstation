#include "midiclipmanager.h"

namespace Midi {

MidiClipManager::MidiClipManager() {}

std::vector<MidiEvent> MidiClipManager::getEventsForBuffer(int64_t readTick, int64_t bufferSizeTicks)
{
    std::vector<MidiEvent> clipEvents;
    int64_t bufferEndTick = readTick + bufferSizeTicks;
    for(MidiClip& clip : m_clips) {
        // If the clip contains midi data
        if(clip.globalStartTick >= readTick && clip.globalEndTick() <= bufferEndTick) {
            clipEvents = clip.asset->data.getEventsForTickRange(readTick, bufferEndTick);
        }
    }
    return clipEvents;

}

void MidiClipManager::mixEventsToMidiBuffer(std::vector<MidiEvent> events, MidiBuffer &midiBuffer, int64_t readTick)
{
    for(auto& event : events ) {
        // TODO: this event offset needs to be
        int eventOffset = event.tick - readTick;
        MidiEvent _event = event;
        midiBuffer.addEvent(_event, eventOffset);
    }
}

} // namespace Midi
