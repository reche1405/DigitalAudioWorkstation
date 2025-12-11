#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H
#include <QGraphicsView>
#include <QGraphicsScene>

#include <QWidget>

namespace Ui {
class TimelineWidget;
}

class TimelineWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit TimelineWidget(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~TimelineWidget();



private:
    Ui::TimelineWidget *ui;
};

#endif // TIMELINEWIDGET_H
