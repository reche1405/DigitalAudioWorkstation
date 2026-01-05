#ifndef GLOBALSCENE_H
#define GLOBALSCENE_H
#include <vector>
#include <map>
#include <memory>
#include "../audio/track.h"
#include <QGraphicsScene>
#include "basegraphicstrack.h"

class GlobalScene : public QGraphicsScene
{
public:
    explicit GlobalScene(QObject *parent = nullptr);
    void syncWithTracks(const std::vector<std::unique_ptr<Audio::BaseTrack>>& tracks);
    qreal trackHeightSum();



signals:
    // When the user requests to add a new track.
    // This will be passed to globaltimeline.
    // This can then update it's own m_tracks.
    // And send a signal back here to add new track.
    void requestAddTrack(Audio::TrackType type  = Audio::TrackType::Audio);
    void requestDeleteTrack(int trackId);

public slots:
    // This will be the function that is called from the global timeline
    // It will tell the scene to implement a new graphics track.
    void onTrackAdded(Audio::TrackType type, std::unique_ptr<Audio::BaseTrack>& track);
    void onTrackDeleted(int trackId);

private:
    std::map<int ,BaseGraphicsTrack&> m_guiTracks;
};

#endif // GLOBALSCENE_H
