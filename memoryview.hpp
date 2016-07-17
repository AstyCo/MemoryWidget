#ifndef MEMORYVIEW_HPP
#define MEMORYVIEW_HPP

#include <QGraphicsView>
#include <QtCore>

class MemoryScene;

class MemoryView : public QGraphicsView
{
public:
    MemoryView(QGraphicsScene * scene, QWidget * parent = 0);

    void resizeEvent(QResizeEvent *);



private:

    MemoryScene *m_memoryScene;

};

#endif // MEMORYVIEW_HPP
