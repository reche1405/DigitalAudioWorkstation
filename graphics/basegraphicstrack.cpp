#include "basegraphicstrack.h"
#include <qpainter.h>

BaseGraphicsTrack::BaseGraphicsTrack(int index, qreal x, qreal y, qreal width, qreal height,
                                     QPen& pen, QBrush& brush, Audio::BaseTrack* trackData, QGraphicsItem* parent)
    : QObject(),
    QGraphicsRectItem(x, y, width, height, parent),
    m_pen(pen),
    m_brush(brush),
    m_data(trackData)
{
    setPen(m_pen);
    setBrush(m_brush);
    m_trackHeight = height;
    this->setFlags(QGraphicsItem::ItemDoesntPropagateOpacityToChildren);
    setTitle(QString::fromStdString("Track " + QString::number(index).toStdString() ));
    m_index = index;
}
void BaseGraphicsTrack::drawBackground(QPainter* painter) {
    QRectF rect = this->rect();
    QColor bgColor = QColor(80,80,80,100);
    // Seperates the colors of the tracks based on their index.
    if(m_index % 2) {
        bgColor = QColor(70,70,70,100);
    }
    painter->setBrush(bgColor);
    painter->setPen(Qt::NoPen);
    painter->drawRect(rect);

    painter->setPen(QPen(QColor(150,150,150,100),1));
    painter->drawLine(rect.bottomLeft(), rect.bottomRight());

    //TODO implement some kind of selection highlight logic.
}
void BaseGraphicsTrack::drawContent(QPainter* painter) {

}
void BaseGraphicsTrack::syncWithTrack() {};
BaseGraphicsTrack::~BaseGraphicsTrack() {};
