#include "midiparser.h"

namespace Midi {

MidiAsset MidiParser::parseFile(QString &path)
{
    // To do, parse each event, and convert it to a midi event,
    // Then convert the entire track worth of midi events into a
    // Midi Sequence
    // Which finally gets stored in the below asset.
    MidiAsset asset;
    return asset;
}



} // namespace Midi
