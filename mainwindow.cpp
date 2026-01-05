#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "widgets/globaltimeline.h"
#include "RtAudio.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , TIME_MANAGER(&CoreUtils::MusicTimeManager::instance())
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #404040;");
    BPM = 120.0f;
    SAMPLE_RATE = 44100;
    BEATS_PER_BAR = 4;
    BEAT_LENGTH = 4;

    TIME_MANAGER->setTimeSignature(BEATS_PER_BAR, BEAT_LENGTH);
    TIME_MANAGER->setBpm(BPM);
    TIME_MANAGER->setPointsPerQuarter(960);
    TIME_MANAGER->setSampleRate(SAMPLE_RATE);

    RtAudio audio;
    unsigned int deviceCount = audio.getDeviceCount();
    for(unsigned int id=0; id< deviceCount; id++) {
        try {
            RtAudio::DeviceInfo info = audio.getDeviceInfo(id);
            if(info.probed) {
                qDebug() << "Device" << id << ":" << QString::fromStdString(info.name);
                qDebug() << "  Max Input Channels:" << info.inputChannels;
                qDebug() << "  Max Output Channels:" << info.outputChannels;
                qDebug() << " Device Sample Rates:" << info.sampleRates;
            }
        } catch (RtAudioError &e) {
            qDebug() << "Error probing device" << id << ":" << QString::fromStdString(e.getMessage());
        }
    }

    // We need to store the available sample rates and allow the user to select in a preferences window.
    // For now we will just use 48000.

    GlobalTimeLine *gt = new GlobalTimeLine(ui->timelineFrame, BPM, BEATS_PER_BAR, BEAT_LENGTH);
    QVBoxLayout *frameLayout = new QVBoxLayout(ui->timelineFrame);
    frameLayout->addWidget(gt);
    ui->mainLayout->setContentsMargins(0,0,0,0);
    frameLayout->setContentsMargins(0,0,0,0);

    ui->timelineFrame->setLayout(frameLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
