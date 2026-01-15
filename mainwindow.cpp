#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "widgets/projectcontroller.h"
#include "QTimer"
#include <QAction>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , TIME_MANAGER(&Core::MusicTimeManager::instance())
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #303030;");
    BPM = 120.0f;
    SAMPLE_RATE = 44100;
    BEATS_PER_BAR = 4;
    BEAT_LENGTH = 4;

    TIME_MANAGER->setTimeSignature(BEATS_PER_BAR, BEAT_LENGTH);
    TIME_MANAGER->setBpm(BPM);
    TIME_MANAGER->setTicksPerQuarter(960);
    TIME_MANAGER->setSampleRate(SAMPLE_RATE);


    // We need to store the available sample rates and allow the user to select in a preferences window.
    // For now we will just use 48000.

    m_controller = new ProjectController(ui->timelineFrame, BPM, BEATS_PER_BAR, BEAT_LENGTH);
    QVBoxLayout *frameLayout = new QVBoxLayout(ui->timelineFrame);
    frameLayout->addWidget(m_controller);
    ui->mainLayout->setContentsMargins(0,0,0,0);
    frameLayout->setContentsMargins(0,0,0,0);


    ui->timelineFrame->setLayout(frameLayout);



    m_controller->initAudio();
        //gt->play();

    setupTransportControls();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTransportControls() {
    QAction* playAction = new QAction("Play/Pause", this);
    playAction->setShortcut(QKeySequence(Qt::Key_Space));
    connect(playAction,&QAction::triggered,this, &MainWindow::handleTogglePlay);
    qDebug() << "Space bar action should be linked";

    this->addAction(playAction);
}

void MainWindow::handleTogglePlay()
{
    if(m_controller->audioEngine().transport().isPlaying()) {
        m_controller->audioEngine().pause();
    } else {
        // Insure there is a healthy buffer beore playing.
        m_controller->update();
        m_controller->audioEngine().play();
    }
}
