#ifndef MIDISTRUCTS_H
#define MIDISTRUCTS_H
#include "../core/structs.h"
namespace Midi {

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
        int tpq;
        // the below function will be used in the audio callback when the track processes audio.
        std::vector<MidiEvent> getEventsForTickRange(int64_t startTick, int64_t endTick) const {
            std::vector<MidiEvent> currentEvents;
            for(int i=0; i< events.size(); i++) {

                MidiEvent _event = events.at(i);
                if (_event.tick > endTick) break;

                if(startTick < _event.tick && _event.tick < endTick) {
                    currentEvents.push_back(events.at(i));
                }
            }
            return currentEvents;
        }
    };

    struct MidiNote {
        int64_t startTick;
        int64_t durationTicks;
        uint8_t pitch;
        uint8_t channel;
        int velocity;

    };

    struct MidiScore {
        std::vector<MidiNote> notes;

        // Returns a vector of pitches.
        // This will be useful when drawing timeline midi clips
        // From C0 - C7 but still centering the graphic.

        std::vector<uint8_t> pitchRange() {
            std::vector<uint8_t> range;
            uint8_t min = 127;
            uint8_t max = 0;
            for(MidiNote note : notes) {
                if (note.pitch < min ) min = note.pitch;
                if (note.pitch > max) max = note.pitch;
            }
            range.push_back(min);
            range.push_back(max);
            return range;
        };
    };

    struct MidiAsset : public Core::Asset {
        double durationTicks;
        MidiSequence data;
        MidiScore visualPlot;
        Core::AssetType type() const override {return Core::AssetType::MIDI; }

    };

    struct MidiClip: public Core::Clip {
        std::shared_ptr<MidiAsset> asset;
        bool isLooped = false;
        int64_t loopsStartTick;
        int64_t loopEndTick;

    };

    struct MidiMessage {
        int samplePosition;
        MidiEvent event;

    };

    struct MidiBuffer {
        std::vector<MidiMessage> messages;

        void addEvent(MidiEvent& event, int samplePosition) {
            messages.push_back({samplePosition, event});
            std::sort(messages.begin(), messages.end(),
            [](const auto& a, const auto& b)  {
                return a.samplePosition < b.samplePosition;

            });
        }
        void clear() {messages.clear();}
        bool isEmpty() const {return messages.empty();}
        auto begin() {return messages.begin();}
        auto end() {return messages.end();}
    };



}
#endif // MIDISTRUCTS_H
