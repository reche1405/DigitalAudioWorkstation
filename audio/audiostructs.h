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
    };

    struct ChannelPlot {
        // A vector of channels, which are in turn a vector of plot points
        // If a channel is mono there will only be one vector in the outer vector
        // If it is stereo, there will be two vectors.
        std::vector<std::vector<float>> plots;

    };
    struct AudioAsset : public CoreUtils::Asset {
        // An asset stored in the global sample manager that can be referenced locally by tracks.
        int totalSamples;
        int sampleRate;
        int channels;
        bool stereoIdentical = true;
        std::shared_ptr<AudioBuffer> audioData;
        ChannelPlot visualWavePoints;

        CoreUtils::AssetType type() const override {
            return CoreUtils::AssetType::Audio;
        }

    };


    struct AudioClip {
        // The logical structure for an audio clip in the track timeline.
        std::shared_ptr<AudioAsset> asset;
        size_t globalStartFrame;
        size_t localStartFrame;
        size_t localEndFrame;
        size_t getTotalFrames() const {return localEndFrame - localStartFrame; }

        bool operator<(AudioClip other) const {
            return globalStartFrame < other.globalStartFrame;
        }
    };

    enum class TrackType{Audio, MIDI};

    enum class OutputOption{Master, SendsOnly};
}
#endif // AUDIOSTRUCTS_H
