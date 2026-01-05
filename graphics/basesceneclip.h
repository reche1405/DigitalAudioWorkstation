#ifndef BASESCENECLIP_H
#define BASESCENECLIP_H

#include <QGraphicsRectItem>
#include <QObject>
#include <qpainter.h>

namespace Graphics {
class BaseSceneClip : public QGraphicsRectItem, public QObject
{
public:
    BaseSceneClip(qreal x, qreal y, qreal width, qreal height, QColor color, QGraphicsItem* parent = nullptr);
    void drawBackground(QPainter* painter);
    virtual void drawContent(QPainter* painter) = 0;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {

        painter->save();
        drawBackground(painter);
        painter->restore();


        painter->save();
        QPainterPath clipPath;
        clipPath.addRoundedRect(QRect(0,0,rect().width(), rect().height()), 5, 5);
        painter->setClipPath(clipPath);
        drawContent(painter);
        painter->restore();
    }

    virtual ~BaseSceneClip();
protected:
    QColor m_color;
};

} // namespace Graphics

#endif // BASESCENECLIP_H
