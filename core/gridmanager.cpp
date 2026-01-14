#include "gridmanager.h"
#include "musictimemanager.h"
#include "QGraphicsItem"
#include "QPainter"
#include "QDebug"
#include <algorithm>
namespace Core {

    VerticalGridLine::VerticalGridLine(QPoint ds, QPoint de, LineType type, QString label) {
        m_drawStart = ds;
        m_drawEnd = de;
        m_type = type;
        m_label = label;
    }
    QString VerticalGridLine::toString() {
        QString output;
        output.append("x:");
        output.append(QString::number(m_drawStart.x()));
        output.append(" - ");
        output.append("y:");
        output.append(QString::number(m_drawStart.y()));
        return output;
    }

    GridManager& GridManager::instance() {
        static std::unique_ptr<GridManager> gridManagerPtr =
            std::unique_ptr<GridManager>(new GridManager());
        return *gridManagerPtr;
    }

    void GridManager::setDefaultMajorIntervalPix(int px) {
        m_defaultMajorIntervalPixels = px;
    }
    void GridManager::setInterval(Interval interval) {
        m_currentMajorInterval = interval;
    }
    void GridManager::setMinorIntCount(int count) {
        m_minorIntervalCount = count;
    }

    void GridManager::setPen(QPen pen, LineType type) {
        pen.setCosmetic(true);
        if(type == LineType::MAJOR) {
            m_majorLinePen = pen;
        } else if(type == LineType::MINOR) {
            pen.setWidthF(0.5);
            m_minorLinePen = pen;

        } else {
            m_atomicLinePen = pen;
        }
    }

    void GridManager::configureSpacing(double scale) {
        // This sets the scaling of the grid.

        // scalefactor, where Interval BAR = 64, Interval HALF_BAR = 32 etc; so if current interval is a bar, then its 64 / 64
        // If current interval is two bars then its 64 / 128 = 0.5

        double scaleFactor =  ((double)(static_cast<int>(Interval::BAR) / (double)(m_currentMajorInterval)));
        // The int representation of the enum value of the current interval e.g BAR = 64
        int intervalNum = static_cast<int>(m_currentMajorInterval);
        double currentIntervalPixels = (((double)m_defaultMajorIntervalPixels) * scale / scaleFactor);
        // the values are as follows: .125, .25, .375, .5, .625, .75, .875, 1
        if(currentIntervalPixels <= m_defaultMajorIntervalPixels * (0.5)) {

            if(intervalNum < 1024) {
                Interval newInterval = static_cast<Interval>(intervalNum * 2);
                m_currentMajorInterval = newInterval;
                m_minorIntervalCount = 1;
            }
            // This will currently only allow up to a 64th beat as the smallest interval.
        }
        else if (currentIntervalPixels > m_defaultMajorIntervalPixels * (1) && currentIntervalPixels <= m_defaultMajorIntervalPixels * (1.5)) {
              m_minorIntervalCount = 3;
        }

        else if (currentIntervalPixels > m_defaultMajorIntervalPixels * (1.5) && currentIntervalPixels < m_defaultMajorIntervalPixels * (2)) {
            m_minorIntervalCount = 7;
        }
        else if(currentIntervalPixels >= m_defaultMajorIntervalPixels * 2) {
            if(intervalNum > 1) {
                Interval newInterval = static_cast<Interval>(intervalNum / 2);
                m_currentMajorInterval = newInterval;
                m_minorIntervalCount = 1;
            }
        }

        // We need the

        // if(currentIntervalPixels < m_defaultMajorIntervalPixels * 0.5 || currentIntervalPixels > m_defaultMajorIntervalPixels * 2 ) {
        //     m_minorIntervalCount = m_minorCountOptions[3];
        // }
        // else if(currentIntervalPixels < m_defaultMajorIntervalPixels * 0.625 || currentIntervalPixels > m_defaultMajorIntervalPixels * 1.625 ) {
        //     m_minorIntervalCount = m_minorCountOptions[2];
        // }
        // else if(currentIntervalPixels < m_defaultMajorIntervalPixels * 0.75 || currentIntervalPixels > m_defaultMajorIntervalPixels * 1.75) {
        //     m_minorIntervalCount = m_minorCountOptions[1];
        // }

        // We need to calculate the number of minor gridlines, and their spacing.


    }
    void GridManager::getVisibleLines(double scale, double xOffset, double width, QPainter *painter) {

        configureSpacing(scale);
        double scaleFactor =  ((double)(static_cast<int>(Interval::BAR) / (double)(m_currentMajorInterval)));
        // 64 / 32 = 2
        auto& musicManager = Core::MusicTimeManager::instance();
        int64_t firstTick = xPosToTicks(0, scale, xOffset);
        int64_t lastTick = xPosToTicks(width, scale, xOffset);
        // As in how many ticks is a major interval;
        int64_t majorTickStep = (int64_t)(musicManager.getTicksPerBar() / scaleFactor);
        int64_t minorTickStep = static_cast<int64_t>(majorTickStep / (m_minorIntervalCount + 1));

        int64_t firstGridTick = std::floor((double)firstTick / minorTickStep) * minorTickStep;
        int64_t currentTick = firstGridTick;
        while(currentTick < lastTick) {
            double xPos = ticksToXPos(currentTick,scale, xOffset);
            QPoint drawStart(xPos, 10);
            QPoint drawEnd(xPos, 700);
            MusicTime mtLabel = xPosToMusicTime(xPos, scale, xOffset);
            NotationDetail lod = NotationDetail::BAR;
            if (scaleFactor > 2) {
                lod = NotationDetail::COUNT;
            }
            else if(scaleFactor > 1) {
                lod = NotationDetail::BEAT;
            }
            QString label = mtLabel.toString(lod);
            bool isMajor = (currentTick % majorTickStep == 0);
            if(isMajor) {
                VerticalGridLine line(drawStart, drawEnd, LineType::MAJOR, label);
                painter->setPen(m_majorLinePen);
                painter->drawLine(line.drawStart(), line.drawEnd());
                QPoint labelPoint = line.drawStart();
                labelPoint.setX(labelPoint.x() + (5 / scale));
                labelPoint.setY(labelPoint.y() + 10);
                //painter->drawText(labelPoint, line.label());
                drawScaledText(painter, labelPoint.x(),labelPoint.y(),label, scale);


            } else {
                VerticalGridLine line(drawStart, drawEnd, LineType::MINOR, QString(""));
                painter->setPen(m_minorLinePen);
                painter->drawLine(line.drawStart(), line.drawEnd());
            }
            currentTick += minorTickStep;
        }

    }


    GridManager::~GridManager() {

    }
    void GridManager::draw(QPainter *painter, double scale, double xOffset, double width) {
        getVisibleLines(scale, xOffset, width, painter);

            //QPoint labelPoint = list.at(i).drawStart();
            //labelPoint.setX(labelPoint.x() + 5);
            //labelPoint.setY(labelPoint.y() + 50);
            //painter->drawText(labelPoint, list.at(i).label());
        }

    void GridManager::debug() {
        // THe function gets called!
        //qWarning() << "We are debuging the grid manager";
        QList<VerticalGridLine> list;
        for(int i =0; i< list.size(); i++) {
            qWarning() << list[i].toString();
        }
    }
    MusicTime GridManager::xPosToMusicTime(double x, double scale, double xOffset) {
        auto& musicManager = Core::MusicTimeManager::instance();
        int64_t totalTicks = xPosToTicks(x, scale, xOffset);
        return musicManager.ticksToNotation(totalTicks);

    }
    int64_t GridManager::xPosToTicks(double x, double scale, double xOffset) {
        auto& musicManager = Core::MusicTimeManager::instance();

        double ticksPerBar = static_cast<float>(musicManager.getTicksPerBar());
        double pxPerBarAtScale = m_defaultMajorIntervalPixels;
        if (pxPerBarAtScale <= 0) return 0;
        double totalTicksDouble = (x  / pxPerBarAtScale) * ticksPerBar;
        int64_t totalTicks = static_cast<int64_t>(totalTicksDouble + 0.5f);
        return totalTicks;
    }
    double  GridManager::framesToXPos(int64_t totalFrames, double scale, double xOffset) {
        auto& musicManager = Core::MusicTimeManager::instance();
        int64_t totalTicks = musicManager.framesToTicks(totalFrames);
        return ticksToXPos(totalTicks, scale, xOffset);
    }

    double GridManager::ticksToXPos(int64_t tick, double scale, double xOffset) {
        auto& musicManager = Core::MusicTimeManager::instance();
        double ticksDouble = static_cast<double>(tick);
        double ticksPerBar = static_cast<float>(musicManager.getTicksPerBar());
        double pxPerBarAtScale = m_defaultMajorIntervalPixels * scale;
        double pxPerTick = m_defaultMajorIntervalPixels / ticksPerBar;
        double absoluteX = static_cast<double>(tick) * pxPerTick;
        return absoluteX;
    }
    void GridManager::drawScaledText(QPainter* painter, double x, double y, const QString& text, double scaleX) {
        painter->save();
        painter->translate(x, y);
        painter->scale(1.0f/ scaleX, 1.0);
        QFont font = painter->font();
        font.setPointSizeF(font.pointSizeF() * .75f);
        painter->setFont(font);
        painter->drawText(0,0,text);
        painter->restore();
    }

}
