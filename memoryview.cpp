#include "memoryview.hpp"
#include "memoryscene.hpp"

#include <QDebug>
#include <QResizeEvent>
#include <QtCore>

MemoryView::MemoryView(QGraphicsScene * scene, QWidget * parent)
    : QGraphicsView(scene,parent)
{
    setContentsMargins(0, 0, 0, 0);

    m_memoryScene=dynamic_cast<MemoryScene*>(scene);
    m_memoryScene->setParent(this);


    resize(1000,1000);


    if(!m_memoryScene)
    {
        qWarning(QObject::tr("MemoryView should be installed on MemoryScene").toLatin1().data());
    }


    setRenderHint(QPainter::Antialiasing,true);

}

void MemoryView::resizeEvent(QResizeEvent *event)
{
    m_memoryScene->viewResized(event->size());
    if(isTransformed())
        m_memoryScene->transformChanged(transform());

    ensureVisible(m_memoryScene->sceneRect().adjusted(-5,-5,5,5),50,50);

    qDebug()<< event->size();
    qDebug()<< sceneRect();

    return QGraphicsView::resizeEvent(event);
}



