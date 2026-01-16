#include "projectsamplemanager.h"

#include <QFileInfo>


namespace Audio {

    //GlobalSampleManager::GlobalSampleManager() {}


    void ProjectSampleManager::plotVisualisation(std::shared_ptr<AudioAsset> asset) {
        int desiredRes = 200;
        int channels = asset->channels;
        asset->visualWavePoints.plots.resize(channels);
        std::vector<float>& samples = asset->audioData->samples;
        size_t totalFrames = samples.size() / channels;

        // size_t framesPerPx = totalFrames / desiredRes;
        for(int chan=0; chan < channels; ++chan) {
            asset->visualWavePoints.plots[chan].resize(desiredRes);
            for(int x = 0; x < desiredRes; x++) {
                float max = 0;
                size_t startFrame = (x * totalFrames) / desiredRes;
                size_t endFrame = ((x + 1) * totalFrames) / desiredRes;
                for(size_t f =startFrame; f< endFrame; ++f) {
                    size_t sampleIdx = (f * channels) + chan;
                    if (sampleIdx < samples.size()) {
                        float val = std::abs(samples[sampleIdx]);
                        if (val > max) {
                            max = val;
                        }
                    }
                }
                asset->visualWavePoints.plots[chan].at(x) = max;
            }   
        }
        if(asset->stereoIdentical && channels > 1) {
            for(int i =0; i< asset->visualWavePoints.plots[0].size(); ++i ) {
                float plotOneSample = asset->visualWavePoints.plots.at(0).at(i);
                float plotTwoSample = asset->visualWavePoints.plots.at(1).at(i);
                if(std::abs(plotOneSample - plotTwoSample) > 0.01) {
                    asset->stereoIdentical  = false;
                    break;
                }
            }
        }
    }
}
