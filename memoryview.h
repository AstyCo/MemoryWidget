#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

#include <QGraphicsView>
#include <QtCore>

class MemoryView : public QGraphicsView
{
public:
    MemoryView(QGraphicsScene * scene, QWidget * parent = 0);

    void resizeEvent(QResizeEvent *);
private:

    qreal m_viewRatio;
};

#endif // MEMORYVIEW_H
