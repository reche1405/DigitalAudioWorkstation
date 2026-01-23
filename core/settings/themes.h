#ifndef THEMES_H
#define THEMES_H
#include <qcolor.h>
namespace Core {

struct Theme {
    std::string title;
    QColor windowBg;

    QColor widgetBg;
    QColor widgetText;

    QColor sceneBg;
    QColor sceneText;

    QColor accent;
};

static const Theme Dark {
    "Dark",
    QColor(24,24,24), // Window Color

    QColor(36,36,36), // Widget Background
    QColor(240,240,240), // Widget Text

    QColor(48,48,48), // Scene Background
    QColor(230,230,230), // Scene Text

    QColor(70,190, 250) // Accent color

};

static const Theme Light {
    "Light",
    QColor(130,130,130), // Window Color

    QColor(150,150,150), // Widget Background
    QColor(36,36,36), // Widget Text

    QColor(48,48,48), // Scene Background
    QColor(36,36,36), // Scene Text

    QColor(70,190, 250) // Accent Color

};

class Themes
{
private:
    int activeIndex = 0;
    std::vector<Theme> availableThemes{Dark, Light};
public:
    Themes() {};
    Theme& theme()  {return availableThemes[activeIndex]; }
    std::vector<Theme>& getAvailableThemes() {
        return availableThemes;
    }
    void setActiveTheme(int index) {
        if (availableThemes.size() >= index) {
            return;
        }
        activeIndex = index;

        //TODO:: Implement a function that alerts all widgets and windows that there has been a theme update.

        // TODO: Store the theme information somewhere globally as it can be stored for all projects or just for
        // The current project.
    }
};

} // namespace Core

#endif // THEMES_H
