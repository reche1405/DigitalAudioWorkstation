#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include "../graphics/arrangementview.h"
#include "../core/mixer.h"
#include "../audio/track.h"
#include "../audio/audiostructs.h"
#include "../audio/projectsamplemanager.h"
#include "../audio/audioengine.h"
#include "../graphics/globalscene.h"
#include "../graphics/playhead.h"
#include "../midi/midiplaybackengine.h"
namespace Ui {
class ProjectController;
}

class ProjectController : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectController (
        QWidget *parent = nullptr, float bpm = 120.0,
        int beatsPerBar = 4, int beatLength = 4, int sampleRate = 48000
        );

    virtual ~ProjectController();
    ArrangementView* view() const {return m_view; }
    QGraphicsScene* scene() const {return m_scene; }
    void setBPM(float bpm);
    void setTimeSignature(int beatsPerBar, int beatLength);
    float bpm() const {return m_BPM;}
    int beatsPerBar() const {return m_beatsPerBar; }
    int beatLength() const {return m_beatLength;}
    int sampleRate() const {return m_sampleRate; }

    void addNewTrack(Core::TrackType type = Core::TrackType::Audio);
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
    Midi::MidiPlaybackEngine& playbackEngine() const {return *m_playBackEngine; }

    void updatePlayheadPosition();


private:
    Ui::ProjectController *ui;
    ArrangementView *m_view;
    GlobalScene *m_scene;
    float m_BPM;
    int m_beatsPerBar;
    int m_beatLength;
    int m_sampleRate;
    int64_t m_ppq = 960;
    Audio::AudioEngine *m_audioEngine;
    Midi::MidiPlaybackEngine *m_playBackEngine;
    size_t m_currentPlayheadFrame = 0;
    double m_visualX = 0.0;
    Graphics::Playhead *m_playhead;
    Core::Mixer m_mixer;

    // std::vector<float> m_masterBuffer;
    // std::vector<float> m_trackBuffer;
    // std::vector<std::unique_ptr<Audio::BaseTrack>> m_tracks;
};

#endif // PROJECTCONTROLLER_H
