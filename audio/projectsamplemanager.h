#ifndef PROJECTSAMPLEMANAGER_H
#define PROJECTSAMPLEMANAGER_H
#include "sndfile.h"
#include <QFileInfo>

#include "audiostructs.h"
#include "../core/projectassetmanager.h"
namespace Audio {

class ProjectSampleManager : public Core::ProjectAssetManager
    {
    private:
        // The a cache of entries: filename alongside a shared pointer to the audio asset
        //std::map<QString, std::shared_ptr<AudioAsset>> m_assetCache;
    public:
        virtual ~ProjectSampleManager() = default;


        bool loadAsset(QString& path) override {

            // Load a sample when passed an audio file into the cache.


            if (assetExists(path)) {

                // If the asset exists, return a pointer to the asset from the cache.

                return true;
            } else {

                // open the file with sndfile.

                SF_INFO sfInfo;
                SNDFILE* file = sf_open(path.toStdString().c_str(), SFM_READ, &sfInfo);
                if(!file) {
                    qDebug() << "Unable to locate asset";
                    return false;
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

                m_registry[path.toStdString()] = asset;
                return true;

            }
        }
        bool removeAsset(QString& path) override {
            if(m_registry.find(path.toStdString()) == m_registry.end()) {
                return true;
            }
            m_registry.erase(path.toStdString());
            return true;
        }
        void plotVisualisation(std::shared_ptr<AudioAsset> asset);


        std::shared_ptr<AudioAsset> getSample(QString& path) {
            return std::static_pointer_cast<AudioAsset>(getAsset(path));
        }

    };

}
#endif // PROJECTSAMPLEMANAGER_H
