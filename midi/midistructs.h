#ifndef MIDISTRUCTS_H
#define MIDISTRUCTS_H
#include "../core/structs.h"

struct MidiEvent {
    int64_t tick;
    uint8_t statusByte;
    uint8_t data1;
    uint8_t data2;
    int channel;
    bool isNoteOn() const {return (statusByte & 0xF0) == 0x90 && data2 > 0;}

};
struct MidiSequence {
    std::vector<MidiEvent> events;
    int ppq;
    // the below function will be used in the audio callback when the track processes audio.
    std::vector<MidiEvent> getEventsForTickRange(int64_t startTick, int64_t endTick) {
        std::vector<MidiEvent> currentEvents;
        for(int i=0; i< events.size(); ++i) {

            MidiEvent _event = events.at(i);

            if (_event.tick > endTick) break;
            if(startTick < _event.tick && _event.tick < endTick) {
                currentEvents.push_back(events.at(i));
            }
        }
        return currentEvents;
    }
};

struct MidiPlotNote {
    int64_t startTick;
    int64_t durationTicks;
    uint8_t pitch;

};

struct MidiPlot {
    std::vector<MidiPlotNote> notes;

    // Returns a vector of pitches.
    // This will be useful when drawing midi clips
    // From C0 - C7 but still centering the graphic.
    std::vector<uint8_t> pitchRange() {
        std::vector<uint8_t> range;
        uint8_t min = 127;
        uint8_t max = 0;
        for(MidiPlotNote note : notes) {
            if (note.pitch < min ) min = note.pitch;
            if (note.pitch > max) max = note.pitch;
        }
        range.push_back(min);
        range.push_back(max);
        return range;
    };
};

struct MidiAsset : public CoreUtils::Asset {
    int ppq;
    double durationTicks;
    MidiSequence data;
    MidiPlot visualPlot;
    CoreUtils::AssetType type() const override {return CoreUtils::AssetType::MIDI; }

};


#endif // MIDISTRUCTS_H
