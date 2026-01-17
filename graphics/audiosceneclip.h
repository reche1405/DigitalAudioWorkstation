#ifndef AUDIOSCENECLIP_H
#define AUDIOSCENECLIP_H

#include <QObject>
#include "basesceneclip.h"
#include "../audio/audiostructs.h"
namespace Graphics {

class AudioSceneClip : public BaseSceneClip
{
    Q_OBJECT
public:
    AudioSceneClip(qreal x, qreal y, qreal width, qreal height, QColor color, std::shared_ptr<const Audio::AudioClip> data, QGraphicsItem* parent);
    ~AudioSceneClip() override = default;
private:
    std::shared_ptr<const Audio::AudioClip> m_data;
    void drawContent(QPainter* painter) override;
};
}

#endif // AUDIOSCENECLIP_H
