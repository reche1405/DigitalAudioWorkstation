#ifndef TGRAPHICSVIEW_H
#define TGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include "../core/gridmanager.h"
class TGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr, CoreUtils::GridManager& gridManagerRef = CoreUtils::GridManager::instance());
protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    const int MajorGridSpacing = 150;
    const int MinorGridCount = 4;
    const int MinZoomDrawThreshold = 20;
    CoreUtils::GridManager& m_gridManager;

    qreal getCurrentSpacing() const;
};

#endif // TGRAPHICSVIEW_H
