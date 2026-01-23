#ifndef AUDIOASSETMANAGER_H
#define AUDIOASSETMANAGER_H
#include "sndfile.h"
#include <QFileInfo>

#include "audiostructs.h"
#include "../core/projectassetmanager.h"
namespace Audio {

        /**
        *  Global storage for all audio assets in the project.
        *  Handles reading from and writing to storage.
        *
        */
class AudioAssetManager : public Core::ProjectAssetManager
    {
    private:

    public:
        virtual ~AudioAssetManager() = default;

        /**
        *  Parses an audio asset and stores the data on the heap
        *  Adds to the newly created asset data structure to the asset registry.
        * @param path QString,  the global path to access the file.
        * @return loaded, bool, whether the asset was loaded or not.
        *
        */
        bool loadAsset(QString& path) override {

            if (assetExists(path)) {

                // If the asset exists, return true as loaded.

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

                // Store asset metadata.
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


                // Create the plot visualisation
                plotVisualisation(asset);

                // Add the asset to the registry.
                m_registry[path.toStdString()] = asset;
                return true;

            }
        }

        /**
        *  Checks if an asset is currently loaded in the registry
        *  And removes it if located.
        *
        * @param path QString,  the global path to access the file.
        * @return loaded, bool, whether the asset was removed.
        *
        */
        bool removeAsset(QString& path) override {
            if(m_registry.find(path.toStdString()) == m_registry.end()) {
                return true;
            }
            m_registry.erase(path.toStdString());
            return true;
        }

        /**
        *  Makes a copy of the audio data and decimates the data
        *  for use in a waveform visualisation.
        *
        *  Stores the visualisation data in the asset structure.
        *
        * @param asset shared pointer to AudioAsset structure
        * @return void
        *
        */
        void plotVisualisation(std::shared_ptr<AudioAsset> asset);

        /**
        * Returns the asset that is associated with the provided path
        *
        * @param path QString,  the global path to access the file.
        * @return asset, shared pointer to AudioAsset sreucture.
        *
        */

        std::shared_ptr<AudioAsset> getSample(QString& path) {
            return std::static_pointer_cast<AudioAsset>(getAsset(path));
        }

    };

}
#endif // AUDIOASSETMANAGER_H
