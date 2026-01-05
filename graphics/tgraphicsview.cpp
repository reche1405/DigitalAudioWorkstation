#include "tgraphicsview.h"
#include <qevent.h>
#include <QGraphicsItem>
#include <QDebug>

TGraphicsView::TGraphicsView(QGraphicsScene *scene, QWidget *parent, CoreUtils::GridManager& gridManagerRef)
    : QGraphicsView(scene, parent),
    m_gridManager(gridManagerRef)
{
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    m_gridManager.setInterval();
    m_gridManager.setDefaultMajorIntervalPix();
    m_gridManager.setMinorIntCount();
    m_gridManager.setPen(QPen(QColor(170, 170, 170), 1.0 ), CoreUtils::LineType::MAJOR);
    m_gridManager.setPen(QPen(QColor(140, 140, 140), 0.25 ), CoreUtils::LineType::MINOR);

}

qreal TGraphicsView::getCurrentSpacing() const {
    qreal scaleX = transform().m11();
    qreal idealSpacing = 100.0;
    qreal currentSpacing = MajorGridSpacing;
    if (scaleX * currentSpacing < idealSpacing) {
        while (scaleX * currentSpacing < idealSpacing * 0.5) {
            currentSpacing *= 1.15; // Zoomed out, so make the scene spacing larger
        }
    } else if (scaleX * currentSpacing > idealSpacing * 2) {
        while (scaleX * currentSpacing > idealSpacing * 2) {
            currentSpacing /= 1.15; // Zoomed in, so make the scene spacing smaller
        }
    }

    return currentSpacing;
}

void TGraphicsView::wheelEvent(QWheelEvent *event)
{
    // Check if Ctrl key is pressed for zooming
    if (event->modifiers() & Qt::ControlModifier) {
        // Use a fixed zoom factor change
        qreal scaleFactor = 1.15;

        if (event->angleDelta().y() > 0) {
            // Zoom In (Scale up)
            scale(scaleFactor, 1.0);
        } else {
            // Zoom Out (Scale down)
            scale(1.0 / scaleFactor, 1.0);
        }

        // Horizontal zoom only (for a timeline)
        event->accept();
    } else {
        // If Ctrl is not pressed, use default behavior (vertical scroll)
        QGraphicsView::wheelEvent(event);
    }

    // Request a redraw to update the grid display immediately
    viewport()->update();
}

void TGraphicsView::drawBackground(QPainter *painter, const QRectF &rect) {
    //QTransform originalTransform = painter->worldTransform();
    //painter->setWorldTransform(transform());
    m_gridManager.draw(painter, transform().m11(),rect.left(), rect.width());

    return;
}
