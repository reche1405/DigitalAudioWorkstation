#ifndef AUDIOSTRUCTS_H
#define AUDIOSTRUCTS_H

#include <vector>
#include "QString"
#include "../core/structs.h"
namespace Audio {

    struct AudioBuffer {
        // A buffer of samples
        std::vector<float> samples;
        int sampleRate;
        int frames(int numChannels) {
            return samples.size() / numChannels;
        }
        int size() const {
            return samples.size();
        }
        void init(int size, float defValue) {
            setSize(size);
            setDefault(defValue);
        }
        void setSize(int size) {
            samples.resize(size);
        }
        void setDefault(float value) {
            std::fill(samples.begin(), samples.end(), 0.0f);
        }
        float* data() {
            return samples.data();
        }

    };

    struct ChannelPlot {
        // A vector of channels, which are in turn a vector of plot points
        // If a channel is mono there will only be one vector in the outer vector
        // If it is stereo, there will be two vectors.
        std::vector<std::vector<float>> plots;

    };
    struct AudioAsset : public Core::Asset {
        // An asset stored in the global sample manager that can be referenced locally by tracks.
        int totalSamples;
        int sampleRate;
        int channels;
        bool stereoIdentical = true;
        std::shared_ptr<AudioBuffer> audioData;
        ChannelPlot visualWavePoints;

        Core::AssetType type() const override {
            return Core::AssetType::Audio;
        }

    };


    struct AudioClip : public Core::Clip {
        // The logical structure for an audio clip in the track timeline.
        std::shared_ptr<AudioAsset> asset;
        float gain = 1.0f;
        int64_t fadeInTicks = 0;
        int64_t fadeOutTicks = 0;

    };


}
#endif // AUDIOSTRUCTS_H
