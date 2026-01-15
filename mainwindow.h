#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "core/musictimemanager.h"
#include <memory.h>
#include "widgets/projectcontroller.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupTransportControls();
    void handleTogglePlay();
private:
    Ui::MainWindow *ui;
    ProjectController* m_controller;
    float BPM;
    int SAMPLE_RATE;
    int BEATS_PER_BAR;
    int BEAT_LENGTH;
    Core::MusicTimeManager* TIME_MANAGER;

};
#endif // MAINWINDOW_H
