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
    if(!m_memoryScene)
    {
        qWarning(QObject::tr("MemoryView should be installed on MemoryScene").toLatin1().data());
    }

    qreal height = scene->sceneRect().height(),
          width = scene->sceneRect().width();

    if(height)
    {
        m_viewRatio = width/height;
    }
    else m_viewRatio = 1.0;
}

void MemoryView::resizeEvent(QResizeEvent *event)
{
    QSizeF newSize = event->size();
    m_memoryScene->viewResized(newSize);

//    fitInView(scene()->sceneRect(),Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}

