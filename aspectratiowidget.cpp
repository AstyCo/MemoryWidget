#include "aspectratiowidget.h"

#include <QEvent>
#include <QDebug>

AspectRatioWidget::AspectRatioWidget(QWidget *parent) : QWidget(parent)
{

}

void AspectRatioWidget::resizeEvent(QResizeEvent *)
{

    //
}



AppEventFilter::AppEventFilter(QObject *parent): QObject(parent)
{
}

bool AppEventFilter::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::Resize)
    {
        qDebug()<<"resize!";
        event->ignore();
        return true;
    }
    else
    {
        return QObject::eventFilter(object,event);
    }
}
