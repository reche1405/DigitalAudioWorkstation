#ifndef MIDIPARSER_H
#define MIDIPARSER_H
#include "MidiFile.h"
#include "midistructs.h"
namespace Midi {

class MidiParser
{
public:
    ~MidiParser() = default;
    static bool loadFile(QString& path);
    static MidiAsset parseFile(QString& path);

private:
    static MidiEvent parseEvent(const smf::MidiEvent& event, MidiPlot &plot);
    static MidiSequence parseTrack(const smf::MidiFile& midiFile, int track, MidiPlot &plot);

};

} // namespace Midi

#endif // MIDIPARSER_H
