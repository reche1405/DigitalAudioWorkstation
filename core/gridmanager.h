#ifndef GRIDMANAGER_H
#define GRIDMANAGER_H

#include "musictimemanager.h"
#include "QPoint"
#include "QList"
#include "QString"
#include "QPen"

namespace Core {
    // The type of vertical grid line
    enum LineType : int {
        MAJOR  = 1,
        MINOR = 2,
        ATOMIC = 3
    };
    // The representation of a grid line
    struct VerticalGridLine{
    public:

        explicit VerticalGridLine(QPoint ds, QPoint de, LineType type, QString label);
        QPoint drawStart() const {return m_drawStart; }
        QPoint drawEnd() const {return m_drawEnd; }
        LineType type() const {return m_type; }
        QString label() const {return m_label; }
        QString toString();

    private:
        QPoint m_drawStart;
        QPoint m_drawEnd;
        LineType m_type;
        QString m_label;

    };

    class GridManager
    {
    public:
        // Core functionality to convert a coordinate point to musical notation.
        //QPoint notationToPoint(MusicTime time, float scale, float offset);
        // Core functionality to
        //MusicTime pointToNotation(QPoint point, float scale);
        void getVisibleLines(double scale = 1.0 , double xOffset = 0.0, double width = 800, QPainter *painter = nullptr);
        // Set the current interval of the
        void configureSpacing(double scale);
        void draw(QPainter *painter, double scale, double xOffset, double width);
        void debug();
        static GridManager& instance();
        virtual ~GridManager();

        void setInterval(Interval interval = Interval::BAR);
        void setDefaultMajorIntervalPix(int px = 128);
        void setMinorIntCount(int = 0);
        void setPen(QPen pen, LineType type);

        MusicTime xPosToMusicTime(double x, double scale, double xOffset);
        int64_t xPosToTicks(double x, double scale, double xOffset);
        double ticksToXPos(int64_t tick, double scale, double xOffset);
        double framesToXPos(int64_t frames, double scale, double xOffset);
        void drawScaledText(QPainter* painter, double x, double y, const QString& text, double scaleX);

    private:
        GridManager() = default;
        GridManager(const GridManager&) = delete;
        GridManager& operator=(const GridManager&) = delete;

        Interval m_currentMajorInterval;
        int m_defaultMajorIntervalPixels;
        int m_minorIntervalCount;
        //explicit GridManager(Interval currentInterval = Interval::BAR, int defMajIntPx = 128, int minorIntCount = 0 );
        QList<int> m_minorCountOptions{0, 1, 3, 7};
        QPen m_majorLinePen;
        QPen m_minorLinePen;
        QPen m_atomicLinePen;

    };
}

#endif // GRIDMANAGER_H
