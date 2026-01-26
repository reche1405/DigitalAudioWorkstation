#ifndef TRACK_H
#define TRACK_H

#include "audiodoublebuffer.h"
#include "parameter.h"
#include "../audio/audionode.h"
namespace Core {

class BaseTrack {
protected:
    bool m_isMuted = false;
    QString m_name;
    Core::ID& m_id ;
    Core::Gain m_gain;
    Core::Pan m_pan;
    Audio::ProcessChain m_chain;
    Core::TrackType m_type;
    size_t m_bufferSize{512};
    AudioDoubleBuffer m_audioBuffer{m_bufferSize};


public:
    BaseTrack() :
        m_id(Core::IdManager::instance().generateId())
    {};
    virtual ~BaseTrack() {};
    virtual void process(size_t playheadFrame) = 0;
    void addEffect(std::unique_ptr<Audio::AudioNode> effect);
    void setName(std::string newName);
    Core::ID& id() const { return m_id; }
    Core::TrackType type() const {return m_type; }
    AudioDoubleBuffer& audioBuffer() {return m_audioBuffer;}
    void mixToMaster(float* src, float* dest, size_t numFrames);
};

} // namespace Core

#endif // TRACK_H
