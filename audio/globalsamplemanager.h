#ifndef GLOBALSAMPLEMANAGER_H
#define GLOBALSAMPLEMANAGER_H
#include "audiostructs.h"
#include <map>
namespace Audio {

    class GlobalSampleManager
    {
    private:
        // The a cache of entries: filename alongside a shared pointer to the audio asset
        std::map<QString, std::shared_ptr<AudioAsset>> m_assetCache;
    public:
        GlobalSampleManager();

        std::shared_ptr<AudioAsset> loadSample(QString& path);
        bool assetExists(QString& path);
        void plotWaveForm(std::shared_ptr<AudioAsset> asset);

    };

}
#endif // GLOBALSAMPLEMANAGER_H
