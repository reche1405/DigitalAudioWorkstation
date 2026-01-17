#include "audionode.h"

namespace Audio {

ProcessChain::~ProcessChain() {};

    void ProcessChain::process(std::vector<float>& buffer)  {
        for(auto& effect : m_effects) {
            effect->process(buffer);
        }
    }

    void ProcessChain::updateSampleRate(double sr) {
        for (auto& effect : m_effects) {
            effect->updateSampleRate(sr);
        }
    }

    void ProcessChain::updateBPM(double bpm)
    {
        for (auto& effect : m_effects) {
            effect->updateBPM(bpm);
        }
    }


    void ProcessChain::addEffect(std::unique_ptr<AudioNode> effect) {
        m_effects.push_back(std::move(effect));
    }
} // namespace Audio


