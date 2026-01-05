#ifndef GLOBALTIMELINE_H
#define GLOBALTIMELINE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include "../graphics/tgraphicsview.h"
#include "../audio/track.h"
#include "../audio/audiostructs.h"
#include "../audio/globalsamplemanager.h"
#include "../audio/audioengine.h"
#include "../graphics/globalscene.h"
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
    TGraphicsView* view() const {return m_view; }
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
    Audio::GlobalSampleManager m_sampler;
    void addNewAudioTrack();
    // void addNewMidiTrack();
    qreal getTrackHeightSum();
private:
    Ui::GlobalTimeLine *ui;
    TGraphicsView *m_view;
    GlobalScene *m_scene;
    void setupScene();
    float m_BPM;
    int m_beatsPerBar;
    int m_beatLength;
    int m_sampleRate;
    Audio::AudioEngine *m_audioEngine;
    size_t m_currentPlayheadFrame = 0;

    std::vector<std::unique_ptr<Audio::BaseTrack>> m_tracks;
};

#endif // GLOBALTIMELINE_H
