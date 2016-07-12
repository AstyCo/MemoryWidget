#include "memoryunit.hpp"
#include "memoryscene.hpp"

#include "globalvalues.hpp"

#include <QPainterPath>
#include <QPainter>

#include <QDebug>

MemoryUnit::MemoryUnit(QGraphicsItem *parent /*= 0*/)
    : QGraphicsItem(parent), m_borderPen(QBrush(Qt::blue),DEFAULT_SPACING ,Qt::SolidLine,Qt::SquareCap,Qt::MiterJoin)
{
//    setFlag(QGraphicsItem::ItemHasNoContents);
    setUnitSelected(false);
    setAcceptsHoverEvents(true);

    setZValue(1000);
}

QRectF MemoryUnit::boundingRect() const
{
    return childrenBoundingRect().adjusted(-DEFAULT_SPACING,-DEFAULT_SPACING,DEFAULT_SPACING,DEFAULT_SPACING);
}

void MemoryUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


//    qDebug()<<childItems().size();

    if(!unitSelected())
        // Don't draw
        return;

//    QPen pen(QBrush(Qt::blue),DEFAULT_SPACING ,Qt::SolidLine,Qt::SquareCap,Qt::MiterJoin);
    painter->setPen(m_borderPen);
    painter->setOpacity(0.8);
    painter->drawPath(m_shapeBorder);
}

int MemoryUnit::unitId() const
{
    return m_unitId;
}

void MemoryUnit::setUnitId(int unitId)
{
    m_unitId = unitId;
}

Memory::MemoryStatus MemoryUnit::status() const
{
    return m_status;
}

void MemoryUnit::setStatus(const Memory::MemoryStatus &status)
{
    m_status = status;
}

long MemoryUnit::start() const
{
    return m_start;
}

void MemoryUnit::setStart(long start)
{
    m_start = start;
}

long MemoryUnit::finish() const
{
    return m_finish;
}

void MemoryUnit::setFinish(long finish)
{
    m_finish = finish;
}

QVariant MemoryUnit::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
//    if(!value.canConvert<QGraphicsItem*>())
//    {
//        qDebug() << "can't convert to QGraphicsItem*";
//        qDebug() << value;
//        qDebug() << '-';
//        return QVariant();
//    }
    MemoryItem* p_mem = dynamic_cast<MemoryItem*>(value.value<QGraphicsItem*>());
    if(!p_mem)
    {
//        qDebug() << "MemoryUnit::itemChange p_mem is NULL";
        return QVariant();
    }
    else
    {
//        qDebug() << "MemoryUnit::itemChange p_mem is not NULL";
    }
    if(change == QGraphicsItem::ItemChildAddedChange)
    {
        m_items.append(p_mem);
    }
    else if (change == QGraphicsItem::ItemChildRemovedChange)
    {
        m_items.removeOne(p_mem);
    }

    rebuildPath();

    return QGraphicsItem::itemChange(change,value); // MAYBE change to QVariant()
}

void MemoryUnit::rebuildPath()
{

    if(m_items.isEmpty())
    {
        setShapeBorder(QPainterPath());
        return ;
    }


    qreal   top = childrenBoundingRect().top(),
            bottom = childrenBoundingRect().bottom(),

            utterLeft = childrenBoundingRect().right(), // using for search of utter left, right() is MAX
            utterRight = childrenBoundingRect().left(); // -||- right, left() is MAX


    MemoryItem  *utterLeftItem = NULL,
                *utterRightItem = NULL;

    foreach(MemoryItem* item,m_items)
    {
        qreal   itemTop = item->geometry().top(),
                itemBottom = item->geometry().bottom();

        if(itemTop == top)
        {
            // element of first row
            qreal itemLeft = item->geometry().left();

            if(itemLeft < utterLeft)
            {
                utterLeft = itemLeft;
                utterLeftItem = item;
            }
        }
        else if(itemBottom == bottom)
        {
            // element of first row
            qreal itemRight = item->geometry().right();

            if(itemRight > utterRight)
            {
                utterRight = itemRight;
                utterRightItem = item;
            }
        }
    }

    QPainterPath path;
    if(!utterLeftItem||!utterRightItem)
    {
        setShapeBorder(QPainterPath());
        return;
    }

    MemoryScene* p_memScene = dynamic_cast<MemoryScene*>(scene());
    if(!p_memScene)
    {
        qDebug() << "not MemoryScene";
        return ;
    }

    qreal halfSpacing = p_memScene->spacing() / 2;

    path.moveTo(utterLeftItem->geometry().topLeft()+QPointF(-halfSpacing,-halfSpacing));
    path.lineTo(childrenBoundingRect().topRight()+QPointF(+halfSpacing,-halfSpacing));
    path.lineTo(QPointF(childrenBoundingRect().right()+halfSpacing,utterRightItem->geometry().top()-halfSpacing));
    path.lineTo(utterRightItem->geometry().topRight()+QPointF(+halfSpacing,-halfSpacing));
    path.lineTo(utterRightItem->geometry().bottomRight()+QPointF(+halfSpacing,+halfSpacing));
    path.lineTo(childrenBoundingRect().bottomLeft()+QPointF(-halfSpacing,+halfSpacing));
    path.lineTo(QPointF(childrenBoundingRect().left()-halfSpacing,utterLeftItem->geometry().bottom()+halfSpacing));
    path.lineTo(utterLeftItem->geometry().bottomLeft()+QPointF(-halfSpacing,+halfSpacing));
    path.lineTo(utterLeftItem->geometry().topLeft()+QPointF(-halfSpacing,-halfSpacing));

    setShapeBorder(path);
}

QPainterPath MemoryUnit::shapeBorder() const
{
    return m_shapeBorder;
}

void MemoryUnit::setShapeBorder(const QPainterPath &shapeBorder)
{
    m_shapeBorder = shapeBorder;
}

bool MemoryUnit::unitSelected() const
{
    return m_unitSelected;
}

void MemoryUnit::setUnitSelected(bool unitSelected)
{
    m_unitSelected = unitSelected;
}


