#ifndef AUDIOTRACK_H
#define AUDIOTRACK_H

#include "QString"
#include "audioclipmanager.h"
#include "../core/track.h"
namespace Audio {



class AudioTrack : public Core::BaseTrack
{
private:
    AudioClipManager m_sampler;
    // LocalSampleManager m_sampleManager;
    public:

        AudioTrack();
        virtual ~AudioTrack() = default;
        void process(size_t playheadFrame) override;
        AudioClipManager& getSampler() {return m_sampler;}


};

} // namespace Audio

#endif // AUDIOTRACK_H
