#include "basesceneclip.h"
#include "tgraphicsview.h"
#include <qgraphicsscene.h>
#include <qpainter.h>
namespace Graphics {

BaseSceneClip::BaseSceneClip(qreal x, qreal y, qreal width, qreal height, QColor color, QGraphicsItem* parent)
    :  QGraphicsRectItem(x,y,width,height, parent),
    QObject(){
    this->setFlags({QGraphicsItem::ItemClipsChildrenToShape,QGraphicsItem::ItemIsMovable} );
    m_color = color;
    this->setPos(x, y);
    this->setRect(0,0,width, height);
}
void BaseSceneClip::drawBackground(QPainter* painter) {
    QRectF rect = this->rect();
    QBrush brush = painter->brush();
    painter->setBrush(m_color);
    painter->setPen(Qt::NoPen);
    QGraphicsView* view = this->scene()->views().first();

    painter->drawRoundedRect(rect,5 / view->transform().m11() ,5);
}

BaseSceneClip::~BaseSceneClip() {};
} // namespace Graphics
