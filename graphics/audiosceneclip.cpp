#include "audiosceneclip.h"
#include <qpainter.h>
#include "../core/gridmanager.h"
namespace Graphics {

AudioSceneClip::AudioSceneClip(qreal x, qreal y, qreal width, qreal height, QColor color,std::shared_ptr<const Audio::AudioClip> data, QGraphicsItem* parent)
    : BaseSceneClip(x, y, width, height, color, parent)
    , m_data(std::move(data))

{

    m_color = color;
}

void AudioSceneClip::drawContent(QPainter* painter) {

    const int lanes = m_data->asset->stereoIdentical ? 1 : m_data->asset->channels;
    Core::GridManager& gridManager = Core::GridManager::instance();
    QRectF rect = QRectF(0,0,this->rect().width(),this->rect().height());
    QFont font = painter->font();
    gridManager.drawScaledText(painter, rect.left() + 5 /painter->transform().m11() , rect.top() + 9, m_data->asset->fileName, painter->transform().m11());
    rect.setTop(rect.top() + 15);
    //rect.setHeight(rect.height());
    QPen pen = painter->pen();
    pen.setCosmetic(true);
    pen.setColor(QColor(255,255,255,255));
    pen.setWidthF(2.5);
    painter->setPen(pen);
    qreal laneHeight = rect.height() / lanes;
    painter->setRenderHint(QPainter::Antialiasing, true);
    int plotCounter = 0;
    for (const auto& plot : m_data->asset->visualWavePoints.plots) {
        QPolygonF poly;

        qreal top = rect.top() + (laneHeight * plotCounter);
        qreal bottom = top + laneHeight;
        qreal midY = (top + bottom) / 2.0 ;
        // Then normalise the plot point data, so that
        // It is converted from a range of 0.0 - 1.0
        // To the confines of the top and bottom y values;

        // I can do this by multiplying the value by laneheight
        // And adding it to the bottom y value.
        qreal pointX;
        qreal pointY;
        for(int i=0; i < plot.size(); ++i) {
           pointX = rect.left() + (static_cast<qreal>(i) / (plot.size() - 1)) * rect.width();
            pointY = bottom - (plot.at(i) * laneHeight);
            qreal offset = plot.at(i) * (laneHeight / 2.0);
            //poly << QPointF(pointX, pointY);
            if(offset > 0.05)
            painter->drawLine(QPointF(pointX, midY - offset), QPointF(pointX, midY + offset));
        }

        // painter->drawPolyline(poly);
        plotCounter++;
    }
}
}
