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

    setRenderHint(QPainter::Antialiasing,true);

}

void MemoryView::resizeEvent(QResizeEvent *event)
{
    qDebug() << m_viewRatio;

//    fitInView(scene()->sceneRect(),Qt::KeepAspectRatio);

    QTransform m = transform();

    QSizeF newSize = event->size();
    m_memoryScene->viewResized(newSize);
    m_memoryScene->transformChanged(transform());

    qDebug()<< newSize;
    qDebug()<< sceneRect();
    qDebug()<<m_memoryScene->m_memoryWidget->boundingRect();

    return QGraphicsView::resizeEvent(event);
}

