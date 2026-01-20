#ifndef TRACK_H
#define TRACK_H

#include "parameter.h"
#include "../audio/audionode.h"
namespace Core {

class BaseTrack {
protected:
    bool m_isMuted = false;
    QString m_name;
    Core::ID& m_id ;
    Core::Parameter m_gain;
    Core::Parameter m_pan;
    Audio::ProcessChain m_chain;
    Core::TrackType m_type;

public:
    BaseTrack() : m_gain(Core::ParamConstraints{Core::ParameterType::Continuous, 0.0f, 1.0f, 20.0f, 0}),
        m_pan(Core::ParamConstraints{Core::ParameterType::Continuous, -1.0f, 1.0f, 40.0f, 0}),
        m_id(Core::IdManager::instance().generateId())
    {};
    virtual ~BaseTrack() {};
    virtual void process(Audio::AudioBuffer& buffer, size_t playheadFrame) = 0;
    void addEffect(std::unique_ptr<Audio::AudioNode> effect);
    void setName(std::string newName);
    Core::ID& id() const { return m_id; }
    Core::TrackType type() const {return m_type; }
};

} // namespace Core

#endif // TRACK_H
