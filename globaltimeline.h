#ifndef GLOBALTIMELINE_H
#define GLOBALTIMELINE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsWidget>
namespace Ui {
class GlobalTimeLine;
}

class GlobalTimeLine : public QWidget
{
    Q_OBJECT

public:
    explicit GlobalTimeLine(QWidget *parent = nullptr);

    ~GlobalTimeLine();
    QGraphicsView* view() const {return m_view; }
    QGraphicsScene* scene() const {return m_scene; }

private:
    Ui::GlobalTimeLine *ui;
    QGraphicsView *m_view;
    QGraphicsScene *m_scene;
    void setupScene();
};

#endif // GLOBALTIMELINE_H
