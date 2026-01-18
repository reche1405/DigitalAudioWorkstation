#include "globalscene.h"
#include "audiographicstrack.h"
GlobalScene::GlobalScene(QObject *parent)
    : QGraphicsScene(parent)


{


}

void GlobalScene::syncWithTracks(const std::vector<std::unique_ptr<Core::BaseTrack>>& tracks) {
    qreal x = 0;
    qreal defaultTrackHeight = 70;
    qreal y = 25;
    QPen pen= QPen(QColor(20,20,20,255));
    QBrush brush = QBrush(QColor(255,100,100,255));
    for (auto& track: tracks) {
        auto it =  find(tracks.begin(),tracks.end(), track);
        int index = it - tracks.begin();
        if(!(trackExists(track->id()))) {
            BaseGraphicsTrack* newItem = nullptr;
            switch(track->type()) {
            case Core::TrackType::Audio:
                newItem = new AudioGraphicsTrack(
                    index,x,y,sceneRect().width(),defaultTrackHeight,
                    pen, brush, track.get(), nullptr);
                break;
            case Core::TrackType::MIDI:
                newItem = new AudioGraphicsTrack(
                    index,x,y,this->sceneRect().width(),defaultTrackHeight,
                    pen, brush, track.get(), nullptr);
                break;
            default:
                newItem = new AudioGraphicsTrack(
                    index,x,y,this->sceneRect().width(),defaultTrackHeight,
                    pen, brush, track.get(), nullptr);
                break;
            }
            const int id = index;
            m_guiTracks.emplace(id, *newItem);
            addItem(newItem);
            newItem->setColor(QColor(70,130,255,255));
            newItem->syncWithTrack();
            y += defaultTrackHeight;
        }
    }
}

qreal GlobalScene::trackHeightSum() {
    qreal heightSum = 0;
    std::map<int, BaseGraphicsTrack&>::iterator it;
    for(auto const& [key, value] : m_guiTracks) {
        heightSum += value.rect().height();
    }
    return heightSum;
}

bool GlobalScene::trackExists(Core::ID &searchId)
{
    std::map<int, BaseGraphicsTrack&>::iterator it;
    for(auto const& [key, value] : m_guiTracks) {
        if(value.id().value == searchId.value) {
            return true;
        }
    }
    return false;

}

