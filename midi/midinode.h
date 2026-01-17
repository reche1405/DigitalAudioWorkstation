#ifndef MIDINODE_H
#define MIDINODE_H

#include "../core/node.h"
#include "midistructs.h"
namespace Midi {

class MidiNode : public Core::Node
{
public:
    MidiNode() = default;
    virtual void processMidi(MidiBuffer &buffer) = 0;
    void updateBPM(double bpm) override {
        m_bpm = bpm;
    }

protected:
    double m_bpm;

};

class MidiChain : public MidiNode {
protected:
    std::vector<std::unique_ptr<MidiNode>> m_midiEffects;
public:
    MidiChain() = default;
    void processMidi(MidiBuffer&buffer) override {
        for(auto& effect : m_midiEffects) {
            effect->processMidi(buffer);
        }
    }
    void updateSampleRate(double sr) override {
        for (auto& effect : m_midiEffects) {
            effect->updateSampleRate(sr);
        }
    }
    void addEffect(std::unique_ptr<MidiNode> effect) {
        m_midiEffects.push_back(effect);
    }
    void updateBPM(double bpm) override {
        for(auto& effect : m_midiEffects) {
            effect->updateBPM(bpm);
        }
    }
};

} // namespace Midi

#endif // MIDINODE_H
