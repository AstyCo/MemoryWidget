#include "appeventfilter.h"

#include <QEvent>
#include <QAbstractSpinBox>
#include <QComboBox>

#include <QDebug>
#include <QMetaEnum>

AppEventFilter::AppEventFilter(QObject *parent) : QObject(parent)
{

}

QDebug operator<<(QDebug str, const QEvent * ev) {
   static int eventEnumIndex = QEvent::staticMetaObject
         .indexOfEnumerator("Type");
   str << "QEvent";
   if (ev) {
      QString name = QEvent::staticMetaObject
            .enumerator(eventEnumIndex).valueToKey(ev->type());
      if (!name.isEmpty()) str << name; else str << ev->type();
   } else {
      str << (void*)ev;
   }
   return str.maybeSpace();
}

bool AppEventFilter::eventFilter(QObject *object, QEvent *event)
{
    static int eventNum = 0;
    qDebug()<<QString::number(eventNum)
              +QString(":Object: \n\t")
              +QString(object->metaObject()->className())
              +QString("\n")
              +QString::number(eventNum)
              +QString("called event: \n")
           <<event;

    eventNum+=1;
    return QObject::eventFilter(object,event);
}

