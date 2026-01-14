#ifndef GLOBALTIMELINE_H
#define GLOBALTIMELINE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include "../graphics/arrangementview.h"
#include "../audio/track.h"
#include "../audio/audiostructs.h"
#include "../audio/projectsamplemanager.h"
#include "../audio/audioengine.h"
#include "../graphics/globalscene.h"
#include "../graphics/playhead.h"
namespace Ui {
class GlobalTimeLine;
}

class GlobalTimeLine : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalTimeLine (
        QWidget *parent = nullptr, float bpm = 120.0,
        int beatsPerBar = 4, int beatLength = 4, int sampleRate = 48000
        );

    virtual ~GlobalTimeLine();
    ArrangementView* view() const {return m_view; }
    QGraphicsScene* scene() const {return m_scene; }
    void setBPM(float bpm);
    void setTimeSignature(int beatsPerBar, int beatLength);
    float bpm() const {return m_BPM;}
    int beatsPerBar() const {return m_beatsPerBar; }
    int beatLength() const {return m_beatLength;}
    int sampleRate() const {return m_sampleRate; }

    void addNewTrack(Audio::TrackType type = Audio::TrackType::Audio);
    void mixMasterBuffer(uint32_t numFrames);
    size_t getCurrentPlayheadFrame() const {return m_currentPlayheadFrame;}
    Audio::ProjectSampleManager m_sampler;
    void addNewAudioTrack();
    // void addNewMidiTrack();
    qreal getTrackHeightSum();
    void setupScene();
    void play();
    void initAudio();
    void update();

    Audio::AudioEngine& audioEngine() const {return *m_audioEngine; }
    void updatePlayheadPosition();


private:
    Ui::GlobalTimeLine *ui;
    ArrangementView *m_view;
    GlobalScene *m_scene;
    float m_BPM;
    int m_beatsPerBar;
    int m_beatLength;
    int m_sampleRate;
    int64_t m_ppq = 960;
    Audio::AudioEngine *m_audioEngine;
    size_t m_currentPlayheadFrame = 0;
    double m_visualX = 0.0;
    std::vector<float> m_masterBuffer;
    std::vector<float> m_trackBuffer;
    Graphics::Playhead *m_playhead;
    std::vector<std::unique_ptr<Audio::BaseTrack>> m_tracks;
};

#endif // GLOBALTIMELINE_H
