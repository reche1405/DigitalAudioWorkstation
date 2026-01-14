#ifndef PROJECTMIDICLIPMANAGER_H
#define PROJECTMIDICLIPMANAGER_H

#include "../core/projectassetmanager.h"

namespace Midi {

class ProjectMidiClipManager : public Core::ProjectAssetManager
{
public:
    virtual ~ProjectMidiClipManager() = default;
    bool loadAsset(QString& path) override {
        std::string strPath = path.toStdString();
        return true;
    }
};

} // namespace Midi

#endif // PROJECTMIDICLIPMANAGER_H
