#include "miditrack.h"
#include "../core/musictimemanager.h"
namespace Midi {

MidiTrack::MidiTrack() : BaseTrack() {
      m_type = Core::TrackType::MIDI;
}

void MidiTrack::process(Audio::AudioBuffer& buffer, size_t currentGlobalFrame, int numChannels)
{
    Core::MusicTimeManager& manager = Core::MusicTimeManager::instance();
    std::fill(buffer.samples.begin(), buffer.samples.end(), 0.0f);
    // First calculate all of the buffer information in ticks.
    int64_t currentGlobalTick = manager.framesToTicks(currentGlobalFrame);
    size_t bufferEndFrame = buffer.size() / numChannels;
    int64_t bufferEndTick = manager.framesToTicks(bufferEndFrame);
    int64_t bufferSizeTicks = bufferEndTick - currentGlobalTick;

    // Get a list of midi events that occur in the tick range;
    std::vector<MidiEvent> events = m_clipManager.getEventsForBuffer(currentGlobalTick, bufferSizeTicks);
    m_clipManager.mixEventsToMidiBuffer(events, m_midiBuffer,currentGlobalTick);
    m_instrument->process(buffer, m_midiBuffer);
    m_chain.process(buffer);

}

} // namespace Midi
