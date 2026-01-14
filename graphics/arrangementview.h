#ifndef ARRANGEMENTVIEW_H
#define ARRANGEMENTVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include "../core/gridmanager.h"
class ArrangementView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ArrangementView(QGraphicsScene *scene, QWidget *parent = nullptr, Core::GridManager& gridManagerRef = Core::GridManager::instance());
    Core::GridManager& gridManager() const {return m_gridManager;}

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    const int MajorGridSpacing = 150;
    const int MinorGridCount = 4;
    const int MinZoomDrawThreshold = 20;
    Core::GridManager& m_gridManager;

    qreal getCurrentSpacing() const;
};

#endif // ARRANGEMENTVIEW_H
