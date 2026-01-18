#ifndef BASEGRAPHICSTRACK_H
#define BASEGRAPHICSTRACK_H
#include "../audio/audiotrack.h"
#include <QGraphicsItem>
#include <QObject>

class BaseGraphicsTrack : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    BaseGraphicsTrack(int index, qreal x, qreal y, qreal width, qreal height,
                      QPen& pen, QBrush& brush, Core::BaseTrack* trackData , QGraphicsItem *parent = nullptr);
    virtual ~BaseGraphicsTrack();
    qreal trackHeight()  const {return m_trackHeight; }
    QColor color() const { return m_color; }
    void setColor(QColor newColor) {m_color = newColor;}
    void setTitle(QString newTitle)  {m_title = newTitle;}
    QString title() const {return m_title; }
    // virtual void drawContent(QPainter* painter) = 0;
    void drawBackground(QPainter* painter);
    virtual void drawContent(QPainter* painter);
    virtual void syncWithTrack();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
        drawBackground(painter);
       drawContent(painter);
    }
    Core::ID& id() const {return m_data->id(); }

protected:
    Core::BaseTrack* m_data;
    QColor m_color;
    qreal m_trackHeight;
    QString m_title;
    QPen& m_pen;
    QBrush& m_brush;
    int m_index;
};

#endif // BASEGRAPHICSTRACK_H
