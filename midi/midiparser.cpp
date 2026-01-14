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
        MidiSequence sequence;
        for(int j = 0; j < midiFile[i].size(); ++j) {
            // for each event create a new midi event
            MidiEvent event = parseEvent(midiFile[i][j]);
            sequence.events.push_back(event);
        }
        // once at the end of a track, create a midi sequence
    }

    return asset;
}

MidiEvent MidiParser::parseEvent(const smf::MidiEvent &event)
{

}

MidiSequence MidiParser::parseTrack(const smf::MidiFile &midiFile, int track)
{

}



} // namespace Midi
