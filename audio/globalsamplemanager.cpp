#include "globalsamplemanager.h"

#include "sndfile.h"
#include <QFileInfo>

namespace Audio {

    GlobalSampleManager::GlobalSampleManager() {}

    bool GlobalSampleManager::assetExists(QString& path) {
        return !(m_assetCache.find(path) == m_assetCache.end());
    }

    std::shared_ptr<AudioAsset> GlobalSampleManager::loadAsset(QString& path) {

        // Load a sample when passed an audio file into the cache.


        if (assetExists(path)) {

            // If the asset exists, return a pointer to the asset from the cache.

            return m_assetCache[path];
        } else {

            // open the file with sndfile.

            SF_INFO sfInfo;
            SNDFILE* file = sf_open(path.toStdString().c_str(), SFM_READ, &sfInfo);
            if(!file) {
                qDebug() << "Unable to locate asset";
                return nullptr;
            }

            // looad the asset.
            auto asset = std::make_shared<AudioAsset>();
            asset->path = path;
            QFileInfo info(path);


            asset->fileName = info.fileName();
            asset->totalSamples = static_cast<int>(sfInfo.frames * sfInfo.channels);
            asset->sampleRate = sfInfo.samplerate;
            qDebug() << "Asset sample rate: " << sfInfo.samplerate;
            asset->channels = sfInfo.channels;
            asset->online = true;
            asset->durationSeconds = static_cast<double>(sfInfo.frames) / sfInfo.samplerate;

            // Create and resize the audio buffer for the asset.
            asset->audioData = std::make_shared<AudioBuffer>();
            asset->audioData->samples.resize(asset->totalSamples);

            // Use soundfile to copy the audio data from the open file to the audio buffer.
            sf_count_t readCount = sf_readf_float(file, asset->audioData->samples.data(), sfInfo.frames);
            if(readCount != sfInfo.frames) {
                qDebug() << "Warning, did not get expected number of frames. ";
            }

            sf_close(file);


            // create the plot point data here
            plotVisualisation(asset);

            m_assetCache[path] = asset;
            return asset;

        }
    }

    void GlobalSampleManager::plotVisualisation(std::shared_ptr<AudioAsset> asset) {
        int desiredRes = 100;
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
