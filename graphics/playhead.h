#ifndef PLAYHEAD_H
#define PLAYHEAD_H

#include <QGraphicsItem>
#include <qpainter.h>

namespace Graphics {

class Playhead : public QGraphicsItem
{
public:
    Playhead(int height, QGraphicsItem *parent = nullptr) : QGraphicsItem(parent), m_height(height) {
        setZValue(199);
        m_pen.setCosmetic(true);
        QColor playheadColor(175, 170, 255);
        m_pen.setColor(playheadColor);
        m_brush.setColor(playheadColor);
        m_pen.setWidthF(1.5f);
        m_brush.setStyle(Qt::SolidPattern);
    };

    QRectF boundingRect() const override {
        return QRectF(-5, 0, 10, m_height);
    };

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        double invScaleX = 1.0 / painter->transform().m11();
        painter->save();
        painter->scale(invScaleX, 1.0);
        painter->setTransform(painter->worldTransform());
        // Anti-aliasing makes the line look smooth
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(m_pen);
        painter->setBrush(m_brush);

        QPolygonF rTriangle;
        rTriangle << QPointF(-5, 13) << QPointF(-4, 10)  << QPointF(4, 10) << QPointF(5, 13)  << QPointF(0, 20);

        painter->drawLine(0, 20, 0, m_height);
        painter->drawPolygon(rTriangle);
        painter->restore();
    }

    void updateHeight(int newHeight);

private:
    int m_height;
    QPen m_pen;
    QBrush m_brush;
};

} // namespace Graphics

#endif // PLAYHEAD_H
