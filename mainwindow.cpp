#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "globaltimeline.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BPM = 120;
    SAMPLE_RATE = 44100;
    BEATS_PER_BAR = 4;
    BEAT_LENGTH = 4;

    GlobalTimeLine *gt = new GlobalTimeLine(ui->timelineFrame);
    QVBoxLayout *frameLayout = new QVBoxLayout(ui->timelineFrame);
    frameLayout->addWidget(gt);
    ui->timelineFrame->setLayout(frameLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
