#include "projectcontroller.h"
#include "./widgets/ui_projectcontroller.h"
#include <QVBoxLayout>
#include <QRect>
#include <QTimer>
#include "../core/math.h"
#include "widgets/ui_projectcontroller.h"
ProjectController::ProjectController(QWidget *parent, float bpm, int beatsPerBar, int beatLength, int sampleRate)
    : QWidget(parent)
    , ui(new Ui::ProjectController),
    m_audioEngine(new Audio::AudioEngine()),
    m_IdManager(&Core::IdManager::instance())
{
    ui->setupUi(this);
    this->m_BPM = bpm;
    this->m_beatsPerBar = beatsPerBar;
    this->m_beatLength = beatLength;
    this->m_sampleRate = sampleRate;
    setupScene();


    // In GlobalTimeline Constructor
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        if(!m_audioEngine->transport().isPlaying()) {
            return;
        }


        // Try to keep the buffer filled up to a certain point
        size_t targetLevel = 8192; // 2048 stereo frames
        size_t currentLevel = m_audioEngine->ringBuffer().availableSamples() / 2;
        updatePlayheadPosition();

        if (currentLevel < targetLevel) {
            update();
        }
    });
    timer->start(10);

}

void ProjectController::setupScene()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    addNewTrack(Core::TrackType::Audio);
    addNewTrack(Core::TrackType::Audio);




    // Start early stage testing purposes.
    QString firstKickPath = QString::fromStdString("/home/reche/samples/vocal.wav");
    if(!m_sampler.loadAsset(firstKickPath)) {
        qDebug() << "Error loading sample";
    }
    std::shared_ptr<Audio::AudioAsset> sample = m_sampler.getSample(firstKickPath);

    Audio::AudioClip clip;
    clip.asset = sample;
    clip.globalStartTick = 0;
    clip.localStartTick = 0;
    double durationSeconds = clip.asset->durationSeconds;

    clip.localEndTick = static_cast<int64_t>(durationSeconds * (m_BPM / 60.0f) * m_ppq);

    if(auto audioTrack = dynamic_cast<Audio::AudioTrack*>(m_mixer.tracks().at(0).get()))   {
        audioTrack->getSampler().addClip(clip);

    }

    // End early stage testing purposes.


    m_scene = new GlobalScene(this);
    m_view = new ArrangementView(m_scene, this);

    m_scene->setSceneRect(0,0,this->geometry().width() * 4,this->geometry().height());
    m_playhead = new Graphics::Playhead(m_scene->height(), nullptr);
    m_scene->syncWithTracks(m_mixer.tracks());
    m_view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_view->setTransformationAnchor(QGraphicsView::NoAnchor);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(24,24,24, 255));
    m_view->setBackgroundBrush(brush);
    m_scene->addItem(m_playhead);
    // m_scene->addText("Hello world from the timeline!");
    // m_scene-> addRect(QRect(0,0,500, 70));
    m_view->setScene(m_scene);


    mainLayout->addWidget(m_view);

}
void ProjectController::play() {
    m_audioEngine->play();

}
void ProjectController::initAudio() {

    if(!(m_audioEngine->openDevice(1, m_sampleRate, 1024))) {
        qWarning() << "Error opening device";
    } else {
        qDebug() << "Device opened: 1" ;
    }
    ;
}
ProjectController::~ProjectController()
{
    delete ui;
}

void ProjectController::addNewTrack(Core::TrackType type) {
    m_mixer.addNewTrack(type);
    // TODO: Once we have abstracted track, this will be an else statememnt
    // And the above will be a make uniwue Audio::AudioTrack
}

void ProjectController::mixMasterBuffer(uint32_t numFrames) {
    if(!m_audioEngine->transport().isPlaying()) {
        return;
    }
    int64_t playhead = m_audioEngine->transport().getCurrentFrame();
    int64_t waiting = m_audioEngine->ringBuffer().availableSamples() / 2;
    int64_t writePos = playhead + waiting;
    size_t samplesToProcess = numFrames * 2;


    m_mixer.mixMasterBuffer(samplesToProcess, writePos, numFrames);



    // 4. Push to Ring Buffer
    // We try to push the entire block. If it returns less than numFrames*2,
    // it means the ring buffer is full (the audio engine is falling behind).
    size_t pushed = m_audioEngine->ringBuffer().pushBlock(m_mixer.masterBuffer().data(), numFrames * 2);

}

void ProjectController::update() {
    size_t safetyMargin = 8192; // How many frames we want waiting in the pipe
    int safetyCounter = 0;
    while ((m_audioEngine->ringBuffer().availableSamples() / 2) < safetyMargin && safetyCounter < 20) {
        mixMasterBuffer(512); // Process in blocks of 512
        safetyCounter++;
    }
}

void ProjectController::updatePlayheadPosition()
{
    int64_t currentFrame = m_audioEngine->transport().getCurrentFrame();
    double xPos = m_view->gridManager().framesToXPos(currentFrame,1.0,0.0);
    double t = 0.5;
    m_visualX = Core::Math::lerp(xPos, m_visualX, t);
    m_playhead->setPos(m_visualX, 0);
    m_view->update();
}
void ProjectController::addNewAudioTrack() {

    addNewTrack(Core::TrackType::Audio);

    //
}
qreal ProjectController::getTrackHeightSum() {
    return 1;
}


