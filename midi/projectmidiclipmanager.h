#ifndef PROJECTMIDICLIPMANAGER_H
#define PROJECTMIDICLIPMANAGER_H

#include "../core/projectassetmanager.h"
#include "midiparser.h"

namespace Midi {

class ProjectMidiClipManager : public Core::ProjectAssetManager
{
public:
    virtual ~ProjectMidiClipManager() = default;

    bool loadAsset(QString& path) override {
        std::string strPath = path.toStdString();
        if(assetExists(path)) return true;

        return m_parser.loadFile(path);
    }
    bool removeAsset(QString& path) override {
        if (!assetExists(path)) return true;
        m_registry.erase(path.toStdString());
        return true;
    }
private:
    MidiParser m_parser;
};

} // namespace Midi

#endif // PROJECTMIDICLIPMANAGER_H
