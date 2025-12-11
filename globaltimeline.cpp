#include "globaltimeline.h"
#include "ui_globaltimeline.h"
#include <QVBoxLayout>
#include <QRect>
GlobalTimeLine::GlobalTimeLine(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GlobalTimeLine)
{
    ui->setupUi(this);
    setupScene();
}

void GlobalTimeLine::setupScene()
{
    m_scene = new QGraphicsScene(this);
    m_view = new QGraphicsView(this);
    m_scene->setSceneRect(0,0,500,500);
    m_scene->setBackgroundBrush(Qt::darkGray);
    m_scene->addText("Hello world from the timeline!");
    m_scene-> addRect(QRect(0,0,500, 70));
    m_view->setScene(m_scene);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_view);
}
GlobalTimeLine::~GlobalTimeLine()
{
    delete ui;
}
