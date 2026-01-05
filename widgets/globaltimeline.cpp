#include "globaltimeline.h"
#include "ui_globaltimeline.h"
#include <QVBoxLayout>
#include <QRect>

GlobalTimeLine::GlobalTimeLine(QWidget *parent, float bpm, int beatsPerBar, int beatLength, int sampleRate)
    : QWidget(parent)
    , ui(new Ui::GlobalTimeLine),
    m_audioEngine(new Audio::AudioEngine())
{
    ui->setupUi(this);
    this->m_BPM = bpm;
    this->m_beatsPerBar = beatsPerBar;
    this->m_beatLength = beatLength;
    this->m_sampleRate = sampleRate;
    setupScene();

}

void GlobalTimeLine::setupScene()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    addNewTrack(Audio::TrackType::Audio);
    addNewTrack(Audio::TrackType::Audio);




    // Start early stage testing purposes.
    QString firstKickPath = QString::fromStdString("/home/reche/samples/kick1.wav");
    std::shared_ptr<Audio::AudioAsset> sample =  m_sampler.loadSample(firstKickPath);



    Audio::AudioClip clip;
    clip.asset = sample;
    clip.globalStartFrame = 88200;
    clip.localStartFrame = 0;
    clip.localEndFrame = sample->totalSamples / sample->channels;

    if(auto audioTrack = dynamic_cast<Audio::AudioTrack*>(m_tracks.at(0).get()))   {
        audioTrack->getSampler().addClip(clip);
    }

    // End early stage testing purposes.
    m_scene = new GlobalScene(this);
    m_view = new TGraphicsView(m_scene, this);
    m_scene->setSceneRect(0,0,this->geometry().width() * 4,this->geometry().height());
    m_scene->syncWithTracks(m_tracks);
    m_view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_view->setTransformationAnchor(QGraphicsView::NoAnchor);
    m_scene->setBackgroundBrush(Qt::darkGray);
    // m_scene->addText("Hello world from the timeline!");
    // m_scene-> addRect(QRect(0,0,500, 70));
    m_view->setScene(m_scene);


    mainLayout->addWidget(m_view);
}
GlobalTimeLine::~GlobalTimeLine()
{
    delete ui;
}

void GlobalTimeLine::addNewTrack(Audio::TrackType type) {
    if(type == Audio::TrackType::Audio) {
        auto track = std::make_unique<Audio::AudioTrack>(m_tracks.size() + 1);
        m_tracks.push_back(std::move(track));
    }
    // TODO: Once we have abstracted track, this will be an else statememnt
    // And the above will be a make uniwue Audio::AudioTrack
}

void GlobalTimeLine::mixMasterBuffer(uint32_t numFrames) {
    std::vector<float> masterBuffer;
    std::vector<float> trackBuffer;
    masterBuffer.resize(numFrames * 2);
    trackBuffer.resize(numFrames * 2);
    for (auto& t : m_tracks) {
        std::fill(trackBuffer.begin(), trackBuffer.end(), 0.0f);
        // TODO: pass the current frame from this globaltimeline manager: URGENT
        t->process(trackBuffer, m_currentPlayheadFrame);


        for(int i = 0; i < masterBuffer.size(); i++) {
            masterBuffer[i] += trackBuffer[i];
        }
    }
    // Master bus and gain staging can happen here.

}
void GlobalTimeLine::addNewAudioTrack() {

    addNewTrack(Audio::TrackType::Audio);

    //
}
qreal GlobalTimeLine::getTrackHeightSum() {
    return 1;
}
