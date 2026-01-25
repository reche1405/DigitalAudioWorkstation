#ifndef SETTINGS_H
#define SETTINGS_H
#include "audiosettings.h"
#include "themes.h"
#include "timesettings.h"
namespace Core {

class Settings
{
private:
    AudioSettings m_audio;
    Theme m_visual;
    TimeSettings m_time;

public:
    Settings();
    TimeSettings& time() {return m_time;}
    AudioSettings& audio() {return m_audio;}
    Theme& visual() {return m_visual;}
};

} // namespace Core

#endif // SETTINGS_H
