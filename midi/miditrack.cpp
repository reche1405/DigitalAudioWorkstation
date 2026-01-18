#include "miditrack.h"

namespace Midi {

MidiTrack::MidiTrack() : BaseTrack() {
      m_type = Core::TrackType::MIDI;
}

} // namespace Midi
