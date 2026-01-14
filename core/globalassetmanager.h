#ifndef GLOBALASSETMANAGER_H
#define GLOBALASSETMANAGER_H

#include "structs.h"
#include <memory>
#include <qcontainerfwd.h>
namespace CoreUtils {

class GlobalAssetManager
{
public:
    GlobalAssetManager() = default;
    virtual ~GlobalAssetManager() = default;

    virtual bool loadAsset(QString& path) = 0;
    virtual bool removeAsset(QString& path) = 0;

    std::shared_ptr<Asset> getAsset(QString& path) {
        if(m_registry.count(path.toStdString())) return m_registry[path.toStdString()];
        return nullptr;
    }
    bool assetExists(QString& path) {
        return m_registry.find(path.toStdString()) != m_registry.end();
    }



protected:
    std::unordered_map<std::string, std::shared_ptr<Asset>> m_registry;
};

} // namespace CoreUtils

#endif // GLOBALASSETMANAGER_H
