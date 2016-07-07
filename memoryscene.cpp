#include "memoryscene.h"

#include <QApplication>
#include <QDebug>


MemoryScene::MemoryScene( QObject * parent)
    :QGraphicsScene(parent)
{
    lastSize = NULL;
    lastSelected = 0;

    connect((QGraphicsScene*)this,SIGNAL(changed(QList<QRectF>)),this,SLOT(onChanged()));
    connect(this,SIGNAL(selectionChanged()),this,SLOT(onSelectionChanged()));
}

MemoryScene::~MemoryScene()
{

}

void MemoryScene::onSelectionChanged()
{
    qDebug()<<"onSelectionChanged!";
    foreach(QGraphicsItem* i_p, selectedItems())
    {
        QGraphicsItem* first;

        MemoryItem *mem_p = dynamic_cast<MemoryItem*> (i_p);
        if(!mem_p)
        {
            qDebug() << "Not MemoryItem*";
            continue;
        }

        if(QApplication::keyboardModifiers()&Qt::ShiftModifier)
        {
                qDebug() <<"itemSelected shift";

                QList<QGraphicsItem*> items = this->items(Qt::AscendingOrder);
//                first = findFirst(items,i_p,i_p/*(QGraphicsItem*)lastSelected*/);

                if(lastSelected)
                {
                    QListIterator<QGraphicsItem*> it(items);
                    it.findNext(first);
                    for(;it.hasNext() ;)
                    {
                        MemoryItem* m_p = dynamic_cast<MemoryItem*>(it.next());
                        if(!m_p)
                        {
                            qDebug()<< "not MemoryItem";
                            continue;
                        }
                        lastSelection.append(m_p);
                        if(m_p == mem_p)
                        {
                            lastSelected = mem_p;
                            break;
                        }
                    }
                    uniqueSelection();
                }
                else
                {
                    lastSelected = mem_p;
                    lastSelection.append(mem_p);
                }
        }
        else if(QApplication::keyboardModifiers()&Qt::ControlModifier)
        {
                qDebug() <<"itemSelected ctrl";

                lastSelected = mem_p;
                lastSelection.append(mem_p);

        }
        else
        {
            lastSelected =mem_p;
            lastSelection.clear();
            lastSelection.append(mem_p);
        }
    }
    foreach(MemoryItem* item, lastSelection)
    {
        item->setSelected(true);
    }
}

void MemoryScene::onChanged()
{

    if(items().size()!=lastSize)
    {
        qDebug() << "onChanged!";
        lastSize=items().size();
    }


}

void MemoryScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    return QGraphicsScene::mousePressEvent(event);
}

void MemoryScene::uniqueSelection()
{
    for(int i=0;i<lastSelection.size();++i)
    {
        for(int j = i + 1; j<lastSelection.size();++j)
        {
            if(lastSelection[i]==lastSelection[j])
            {
                qDebug() <<QString("removingAt : ")+"before : "+ QString::number(lastSelection.size());
                lastSelection.removeAt(j);
                qDebug() <<QString("removingAt : ")+"after : "+ QString::number(lastSelection.size());
            }
        }
    }
}

QGraphicsItem const *MemoryScene::findFirst(QList<QGraphicsItem*> const*list,
                                      QGraphicsItem const *first, QGraphicsItem const *second) const
{
    QListIterator<QGraphicsItem*> it(*list);
    while(it.hasNext())
    {
        QGraphicsItem * tmp = it.next();
        if(tmp == first)
            return first;
        if(tmp == second)
            return second;
    }
    return NULL;
}





