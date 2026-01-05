#ifndef AUDIOGRAPHICSTRACK_H
#define AUDIOGRAPHICSTRACK_H

#include "basegraphicstrack.h"
#include "basesceneclip.h"
class AudioGraphicsTrack : public BaseGraphicsTrack
{
    Q_OBJECT
public:
    AudioGraphicsTrack(int index, qreal x, qreal y, qreal width, qreal height,
                       QPen& pen, QBrush& brush, Audio::BaseTrack* trackData, QGraphicsItem *parent);
    ~AudioGraphicsTrack() override = default;
    void drawContent(QPainter* painter) override;
    void syncWithTrack() override;

private:
    std::vector<Graphics::BaseSceneClip*>m_clips;
};

#endif // AUDIOGRAPHICSTRACK_H
