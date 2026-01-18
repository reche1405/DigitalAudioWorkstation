#ifndef NODE_H
#define NODE_H

#include <memory>
#include <vector>
namespace Core {

class Node {
public:
    virtual ~Node() = default;
    virtual void updateSampleRate(double sr) = 0;
    virtual void updateBPM(double bpm) = 0;
};

class ProcessChain  {
private:
    std::vector<std::unique_ptr<Node>> m_nodes;
public:
    ProcessChain() = default;
    ~ProcessChain();
    template <typename T>
    std::shared_ptr<T> addNode(std::unique_ptr<T> node) {
        m_nodes.push_back(node);
    };
    void process() {

    };
    void processAudio(std::vector<float>& buffer);
    // void processMidi(MidiBuffer &midi) {

    void updateSampleRate(double sr);
};
}
#endif // NODE_H
