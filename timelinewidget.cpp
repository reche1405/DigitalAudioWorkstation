#include "timelinewidget.h"
#include "ui_timelinewidget.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGui>
TimelineWidget::TimelineWidget(QWidget *parent)
    : QGraphicsView(parent)
    , ui(new Ui::TimelineWidget)
{
    ui->setupUi(this);
;

}

TimelineWidget::~TimelineWidget()
{
    delete ui;
}
