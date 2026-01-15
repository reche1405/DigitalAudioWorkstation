#include "midiparser.h"
#include <qdebug.h>

namespace Midi {

MidiAsset MidiParser::parseFile(QString &path)
{
    // Craig Sapp MIDI File parser.
    smf::MidiFile midiFile;
    std::string filename = path.toStdString();

    // The returned MidiAsset
    MidiAsset asset;

    // The plot notes
    MidiPlot plot;
    asset.visualPlot = plot;


    if(!midiFile.read(filename)) {

        qDebug() << "Error reading file.";
        return asset;

    }
    // Todo, loop over tracks
    for(int i =0; i < midiFile.getTrackCount(); ++i) {
        MidiSequence sequence = parseTrack(midiFile, i, plot);
        asset.data = sequence;
    }


    return asset;
}

MidiEvent MidiParser::parseEvent(const smf::MidiEvent &event, MidiPlot &plot)
{
    MidiEvent eventStruct;
    eventStruct.channel = event.getChannelNibble();
    eventStruct.statusByte = event.getCommandNibble();
    eventStruct.tick = event.tick;

    // The event is either a note on or a note off then follow the below procedure.
    if(event.isNote()) {
        eventStruct.data1 = event.getKeyNumber();
        eventStruct.data2 = event.getVelocity();

        // We now have access to the midi plot in this function.
        // And can create a midiplot note and push it to the back of the plot
        if(event.isNoteOn()) {

            MidiPlotNote note;
            note.startTick = event.tick;
            note.durationTicks = event.getTickDuration();
            note.pitch = event.getKeyNumber();
            note.velocity = event.getVelocity();
            note.channel = event.getChannelNibble();
            plot.notes.push_back(note);
        }
    }

    // The event is a pitchbend event, requiring the MSB and the LSB.
    else if (event.isPitchbend()) {
        eventStruct.data1 = event.getP1();
        eventStruct.data2 = event.getP2();
    }

    // The event is a continous control event, with data detailing controller number
    // And controller value.
    else if (event.isController()) {
        eventStruct.data1 = event.getP1();
        eventStruct.data2 = event.getP2();
    }

    return eventStruct;
}

MidiSequence MidiParser::parseTrack(const smf::MidiFile &midiFile, int track, MidiPlot &plot)
{
    MidiSequence sequence;
    sequence.tpq = midiFile.getTPQ();

    for(int j = 0; j < midiFile[track].size(); ++j) {
        // for each event create a new midi event
        MidiEvent event = parseEvent(midiFile[track][j], plot);
        //
        sequence.events.push_back(event);
    }
    return sequence;
}



} // namespace Midi
