#ifndef AUDIONODE_H
#define AUDIONODE_H

#include "vector"
#include <memory>
namespace Audio {

class AudioNode
{
public:
    AudioNode() = default;
    virtual ~AudioNode() {};
    virtual void process(std::vector<float>& buffer) = 0;
    virtual void updateSampleRate(double sr) = 0;
};

class ProcessChain : public AudioNode {
private:
    std::vector<std::unique_ptr<AudioNode>> m_effects;
public:
    ProcessChain() = default;
    ~ProcessChain();
    void addEffect(std::unique_ptr<AudioNode> effect);
    void process(std::vector<float>& buffer) override;
    void updateSampleRate(double sr) override;
};

} // namespace Audio

#endif // AUDIONODE_H
