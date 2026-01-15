#include "midiparser.h"
#include <qdebug.h>

namespace Midi {

MidiAsset MidiParser::parseFile(QString &path)
{
    smf::MidiFile midiFile;
    std::string filename = path.toStdString();
    MidiAsset asset;

    if(!midiFile.read(filename)) {

        qDebug() << "Error reading file.";
        return asset;

    }
    // Todo, loop over tracks
    for(int i =0; i < midiFile.getTrackCount(); ++i) {
        MidiSequence sequence = parseTrack(midiFile, i);

    }

    return asset;
}

MidiEvent MidiParser::parseEvent(const smf::MidiEvent &event)
{
    MidiEvent eventStruct;
    eventStruct.channel = event.getChannelNibble();
    eventStruct.statusByte = event.getCommandByte();
    eventStruct.tick = event.tick;

    if(event.isNoteOn() || event.isNoteOff()) {
        eventStruct.data1 = event.getKeyNumber();
        eventStruct.data2 = event.getVelocity();

    }

    return eventStruct;
}

MidiSequence MidiParser::parseTrack(const smf::MidiFile &midiFile, int track)
{
    MidiSequence sequence;
    sequence.ppq = midiFile.getTPQ();
    for(int j = 0; j < midiFile[track].size(); ++j) {
        // for each event create a new midi event
        MidiEvent event = parseEvent(midiFile[track][j]);
        sequence.events.push_back(event);
    }
    return sequence;
}



} // namespace Midi
