#include "memoryitemgroup.hpp"
#include "memoryitem.hpp"
#include "memoryscene.hpp"


#include <QGraphicsItem>
#include <QGraphicsScene>

#include <QDebug>

MemoryItemGroup::MemoryItemGroup()
{
    setHandlesChildEvents(false);

//    setFlags(ItemIsSelectable);
//    setAcceptsHoverEvents(true);
}

int MemoryItemGroup::groupId() const
{
    return m_groupId;
}

void MemoryItemGroup::setGroupId(int groupId)
{
    m_groupId = groupId;
}

void MemoryItemGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
//    QPainterPath shapePath = shape();
}

QColor MemoryItemGroup::groupColor() const
{
    return m_groupColor;
}

void MemoryItemGroup::setGroupColor(const QColor &groupColor)
{
    m_groupColor = groupColor;
}

QPainterPath MemoryItemGroup::shape() const
{
//    qDebug() <<"MemoryItemGroup shape called";

    QList<QGraphicsItem*> items = childItems();

    if(items.isEmpty())
        return QPainterPath();

    qreal   top = boundingRect().top(),
            bottom = boundingRect().bottom(),

            utterLeft = boundingRect().right(), // using for search of utter left, right() is MAX
            utterRight = boundingRect().left(); // -||- right, left() is MAX


    MemoryItem  *utterLeftItem = NULL,
                *utterRightItem = NULL;

    foreach(QGraphicsItem* item,items)
    {
        MemoryItem *p_mem = dynamic_cast<MemoryItem*>(item);
        if(!p_mem)
        {
            qDebug() << "not MemoryItem*";
            continue;
        }
        qreal   itemTop = p_mem->geometry().top(),
                itemBottom = p_mem->geometry().bottom();

        if(itemTop == top)
        {
            // element of first row
            qreal itemLeft = p_mem->geometry().left();

            if(itemLeft < utterLeft)
            {
                utterLeft = itemLeft;
                utterLeftItem = p_mem;
            }
        }
        else if(itemBottom == bottom)
        {
            // element of first row
            qreal itemRight = p_mem->geometry().right();

            if(itemRight > utterRight)
            {
                utterRight = itemRight;
                utterRightItem = p_mem;
            }
        }
    }

    QPainterPath path;
    if(!utterLeftItem||!utterRightItem)
    {
        path.addRect(boundingRect());
        return path;
    }

    MemoryScene* p_memScene = dynamic_cast<MemoryScene*>(scene());
    if(!p_memScene)
    {
        qDebug() << "not MemoryScene";
        return QPainterPath();
    }

    qreal halfSpacing = p_memScene->spacing() / 2;

    path.moveTo(utterLeftItem->geometry().topLeft()+QPointF(-halfSpacing,-halfSpacing));
    path.lineTo(boundingRect().topRight()+QPointF(+halfSpacing,-halfSpacing));
    path.lineTo(QPointF(boundingRect().right()+halfSpacing,utterRightItem->geometry().top()-halfSpacing));
    path.lineTo(utterRightItem->geometry().topRight()+QPointF(+halfSpacing,-halfSpacing));
    path.lineTo(utterRightItem->geometry().bottomRight()+QPointF(+halfSpacing,+halfSpacing));
    path.lineTo(boundingRect().bottomLeft()+QPointF(-halfSpacing,+halfSpacing));
    path.lineTo(QPointF(boundingRect().left()-halfSpacing,utterLeftItem->geometry().bottom()+halfSpacing));
    path.lineTo(utterLeftItem->geometry().bottomLeft()+QPointF(-halfSpacing,+halfSpacing));
    path.lineTo(utterLeftItem->geometry().topLeft()+QPointF(-halfSpacing,-halfSpacing));

    return path;
}

