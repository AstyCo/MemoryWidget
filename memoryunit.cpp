#include "memoryunit.hpp"
#include "memoryscene.hpp"

#include "memoryitempresentation.hpp"

#include "globalvalues.hpp"

#include <QPainterPath>
#include <QPainter>

#include <QDebug>

extern MemoryScene* mem_scene;

MemoryUnit::MemoryUnit(QGraphicsItem *parent /*= 0*/)
    : QGraphicsItem(parent)
{
//    setFlag(QGraphicsItem::ItemHasNoContents);

    rand = qrand()%2;

    m_scene = dynamic_cast<MemoryScene*>(scene());
    if(!m_scene)
        qDebug() << "Not MemoryScene*";

    setUnitSelected(false);
    setAcceptsHoverEvents(true);

    setZValue(1);

    m_borderPen=QPen(QBrush(QColor(rand?Qt::red:Qt::blue)/*.lighter()*/), extraSize()*2 ,Qt::SolidLine,Qt::SquareCap,Qt::MiterJoin);

}

QRectF MemoryUnit::boundingRect() const
{
    return m_shapeBorder.boundingRect().adjusted(-extraSize(),-extraSize(),extraSize(),extraSize());
}

QPainterPath MemoryUnit::shape() const
{
    return m_shapeBorder;
}

void MemoryUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(!unitSelected())
        // Don't draw
        return;

//    QPen pen(QBrush(Qt::blue),DEFAULT_SPACING ,Qt::SolidLine,Qt::SquareCap,Qt::MiterJoin);

    painter->setCompositionMode(QPainter::CompositionMode_Multiply);

    painter->setPen(m_borderPen);
    painter->setOpacity(1);
    painter->drawPath(m_shapeBorder);
//    qDebug() << m_shapeBorder;

}

int MemoryUnit::unitId() const
{
    return m_unitId;
}

void MemoryUnit::setUnitId(int unitId)
{
    m_unitId = unitId;
}

Memory::MemoryState MemoryUnit::state() const
{
    return m_state;
}

void MemoryUnit::setState(const Memory::MemoryState &status)
{
    m_state = status;
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

long MemoryUnit::size() const
{
    return m_finish-m_start + 1;
}

void MemoryUnit::setSize(long newSize)
{
    setFinish(start()+newSize-1);
}

qreal MemoryUnit::spacing() const
{
    MemoryScene* p_memScene = dynamic_cast<MemoryScene*>(scene());
    if(!p_memScene)
        return DEFAULT_SPACING;
    return p_memScene->spacing();
}

QVariant MemoryUnit::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
//    MemoryItem* p_mem = dynamic_cast<MemoryItem*>(value.value<QGraphicsItem*>());
//    if(!p_mem)
//    {
//        return QGraphicsItem::itemChange(change,value);
//    }

//    if(change == QGraphicsItem::ItemChildAddedChange)
//    {
//        if(m_unitId)
//        {
////            qDebug() << "append to "+QString::number(m_unitId);
//        }
//        m_items.append(p_mem);
//        update();
//    }
//    else if (change == QGraphicsItem::ItemChildRemovedChange)
//    {
//        if(m_unitId)
//        {
////            qDebug() << "remove from "+QString::number(m_unitId);
//        }
//        m_items.removeOne(p_mem);
//        update();
//    }

//    rebuildShape();

    return QGraphicsItem::itemChange(change,value); // MAYBE change to QVariant()
}

void MemoryUnit::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    MemoryScene* p_scene = dynamic_cast<MemoryScene*>(scene());
    if(!p_scene)
        return;
    setUnitSelected(true);

    p_scene->setUnitInfo(QString(   QObject::tr("Unit Group Id: ")
                                    +QString::number(unitId())
                                    +QString(QObject::tr("  Unit State: "))
                                    +state()
                                    +QObject::tr(" Unit Memory: ")
                                    +"0x"+fixedNumPresentation(start(),16,2047)
                                    +" - 0x"+fixedNumPresentation(finish(),16,2047)
                         ));

    setZValue(100);

    update();

    return QGraphicsItem::hoverEnterEvent(event);
}

void MemoryUnit::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setZValue(0);
    setUnitSelected(false);
    return QGraphicsItem::hoverLeaveEvent(event);
}

void MemoryUnit::rebuildShape()
{
    if(m_items.isEmpty())
    {
        setShapeBorder(QPainterPath());
        return ;
    }

    QPainterPath itemsPath;

    foreach(MemoryItem* item, m_items)
    {
        itemsPath.addRect(item->geometry());
    }

    qreal   top = itemsPath.boundingRect().top(),
            bottom = itemsPath.boundingRect().bottom(),

            utterLeft = itemsPath.boundingRect().right(), // using for search of utter left, right() is MAX
            utterRight = itemsPath.boundingRect().left(); // -||- right, left() is MAX


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
        if(itemBottom == bottom)
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
//        qDebug() << "not MemoryScene";
        return ;
    }

    qreal halfSpacing = p_memScene->spacing() / 2;

    bool shapingTop = false,
         shapingBottom = false,
         shapingSeparate = false;
    if(utterLeftItem->geometry().left()!=itemsPath.boundingRect().left())
        shapingTop = true;
    if(utterRightItem->geometry().right()!=itemsPath.boundingRect().right())
        shapingBottom = true;
    if(size()<p_memScene->itemPerRow()
            && utterLeft>utterRight)
        shapingSeparate = true;

    path.moveTo(utterLeftItem->geometry().topLeft()+QPointF(-halfSpacing,-halfSpacing));
    path.lineTo(itemsPath.boundingRect().topRight()+QPointF(+halfSpacing,-halfSpacing));

    if(shapingBottom)
    {
        path.lineTo(QPointF(itemsPath.boundingRect().right()+halfSpacing,utterRightItem->geometry().top()-halfSpacing));
        if(shapingSeparate)
        {
            path.lineTo(utterLeftItem->geometry().bottomLeft()+QPointF(-halfSpacing,+halfSpacing));
            path.moveTo(utterRightItem->geometry().topRight()+QPointF(+halfSpacing,-halfSpacing));
        }
        else
            path.lineTo(utterRightItem->geometry().topRight()+QPointF(+halfSpacing,-halfSpacing));
    }

    path.lineTo(utterRightItem->geometry().bottomRight()+QPointF(+halfSpacing,+halfSpacing));
    path.lineTo(itemsPath.boundingRect().bottomLeft()+QPointF(-halfSpacing,+halfSpacing));

    if(shapingTop)
    {
        path.lineTo(QPointF(itemsPath.boundingRect().left()-halfSpacing,utterLeftItem->geometry().bottom()+halfSpacing));
        if(shapingSeparate)
        {
            path.lineTo(utterRightItem->geometry().topRight()+QPointF(+halfSpacing,-halfSpacing));
            path.moveTo(utterLeftItem->geometry().bottomLeft()+QPointF(-halfSpacing,+halfSpacing));
        }
        else
            path.lineTo(utterLeftItem->geometry().bottomLeft()+QPointF(-halfSpacing,+halfSpacing));
    }

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

QColor MemoryUnit::color() const
{
    return MemoryState_to_QColor(m_state);
}

void MemoryUnit::addItems(long start, long finish, const QList<MemoryItem *>& items)
{
    setStart(start);
    setFinish(finish);

    for(int i = start; i<=finish; ++i)
    {
        m_items.append(items[i]);
        items[i]->setParentItem(this);
    }
    rebuildShape();
}

void MemoryUnit::removeTheFirst(long until)
{

}

void MemoryUnit::removeTheLast(long until)
{

}

void MemoryUnit::updateParenthesis()
{
    for(int i = 0; i < m_items.size(); ++i)
    {
        m_items[i]->setParentItem(this);
    }
    rebuildShape();
}

qreal MemoryUnit::extraSize() const
{
    return spacing()/2 + m_scene->itemBorder();
}


