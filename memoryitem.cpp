#include "memoryitem.hpp"
#include "memoryscene.hpp"
#include "globalvalues.hpp"


#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

MemoryItem::MemoryItem(long index,qreal edgeLength,qreal borderWidth,QGraphicsItem *parent/* = 0*/)
    : QGraphicsLayoutItem(), QGraphicsItem(parent)
{
    setGraphicsItem(this);
    setIndex(index);

    m_parentUnit = dynamic_cast<MemoryUnit*>(parent);
        // NULL if not MemoryUnit*
    setEdgeLength(edgeLength);
    setBorderWidth(borderWidth);

    setFlags(ItemIsSelectable);
    setAcceptsHoverEvents(true);

    enableToolTip();


}

MemoryItem::~MemoryItem()
{

}


void MemoryItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? color().dark(150) : color();
    if (option->state & QStyle::State_MouseOver)
    {
        //fillColor = fillColor.light(150);
        fillColor = fillColor.blackF();
    }

    QRectF squareItem( m_borderWidth, m_borderWidth, m_edgeLength, m_edgeLength);
    QColor squareColor = fillColor;

    painter->setPen(Qt::NoPen);

    if(m_borderWidth)
    {
        QRectF extSquareItem( 0, 0, m_edgeLength+2*m_borderWidth, m_edgeLength+2*m_borderWidth);
        QColor extSquareColor = GLOBAL_BORDER_COLOR;
        QPainterPath externalFigure;
        externalFigure.addRect(extSquareItem);
        painter->fillPath(externalFigure, extSquareColor);
        painter->drawPath(externalFigure);
    }
    QPainterPath path;
    path.addRect(squareItem);
    painter->fillPath(path, squareColor);
    painter->drawPath(path);

}

void MemoryItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    MemoryScene* p_scene = dynamic_cast<MemoryScene*>(scene());
    if(!p_scene)
        return QGraphicsItem::hoverEnterEvent(event);

//    if(parentUnitId())
//        setParentUnitSelected(true);

    p_scene->setItemInfo(QString::number(index()));
//    p_scene->setUnitInfo(QString(   QObject::tr("Unit Group Id: ")
//                                    +QString::number(parentUnitId())
//                                    +QString(QObject::tr("  Unit State: "))
//                                    +state()
//                                    +QObject::tr(" Unit Memory: ")
//                                    +"0x"+fixedNumPresentation(parentUnitStart(),16,2047)
//                                    +" - 0x"+fixedNumPresentation(parentUnitFinish(),16,2047)
//                         ));
    p_scene->showInteractiveRange(index(),index()+100);

    return QGraphicsItem::hoverEnterEvent(event);
}

void MemoryItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
//    setParentUnitSelected(false);
    MemoryScene* p_scene = dynamic_cast<MemoryScene*>(scene());
    if(!p_scene)
        return QGraphicsItem::hoverLeaveEvent(event);

    p_scene->hideInteractiveRange();
    p_scene->update();
    return QGraphicsItem::hoverLeaveEvent(event);
}

QString MemoryItem::toolTip() const
{
    return QGraphicsItem::toolTip();
}

void MemoryItem::setToolTip(const QString &toolTip)
{
    return QGraphicsItem::setToolTip(toolTip);
}

void MemoryItem::enableToolTip()
{
    setToolTip(QString("Dec: ")+fixedNumPresentation(index(),10,2047)+'\n'
               +QString("Hex: 0x")+fixedNumPresentation(index(),16,2047)+'\n'
               +QString("Bin:  ")+fixedNumPresentation(index(),2,2047));
}

void MemoryItem::disableToolTip()
{
    setToolTip(QString());
}

QVariant MemoryItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemParentHasChanged)
    {

        QGraphicsItem * newParentItem = value.value<QGraphicsItem*>();
        if(!newParentItem)
        {
            m_parentUnit = NULL;
            return QGraphicsItem::itemChange(change,value);
        }

        MemoryUnit* newParent = dynamic_cast<MemoryUnit*>(newParentItem);
        if(!newParent)
        {
            return QGraphicsItem::itemChange(change,value);
        }
        m_parentUnit = newParent;
        return QGraphicsItem::itemChange(change,value);
    }

    return QGraphicsItem::itemChange(change,value);
}

void MemoryItem::setParentUnitSelected(bool selected)
{
    if(!m_parentUnit)
    {
        return;
    }

    m_parentUnit->setUnitSelected(selected);
    m_parentUnit->update();
}

MemoryState MemoryItem::state() const
{
    if(m_parentUnit)
    {
        return m_parentUnit->state();
    }

    return Memory::Freed;
}

QColor MemoryItem::color() const
{
    if(m_parentUnit)
    {
        return m_parentUnit->color();
    }

    return MemoryState_to_QColor(Memory::Freed);
}

//int MemoryItem::parentUnitId() const
//{
//    if(m_parentUnit)
//    {
//        return m_parentUnit->unitId();
//    }

//    return 0;
//}

//long MemoryItem::parentUnitStart() const
//{
//    if(!m_parentUnit)
//        return -1;
//    return m_parentUnit->start();
//}

//long MemoryItem::parentUnitFinish() const
//{
//    if(!m_parentUnit)
//        return -1;
//    return m_parentUnit->finish();
//}


long MemoryItem::index() const
{
    return m_index;
}

void MemoryItem::setIndex(long index)
{
    m_index = index;
}
int MemoryItem::edgeLength() const
{
    return m_edgeLength;
}

void MemoryItem::setEdgeLength(int edgeLength)
{
    m_edgeLength = edgeLength;
}
qreal MemoryItem::borderWidth() const
{
    return m_borderWidth;
}

void MemoryItem::setBorderWidth(const qreal &borderWidth)
{
    m_borderWidth = borderWidth;
}



//QColor MemoryItem::color() const
//{
//    return m_color;
//}

QRectF MemoryItem::boundingRect() const
{
    return QRectF( 0, 0, m_edgeLength + 2*m_borderWidth, m_edgeLength + 2*m_borderWidth);
    //    return QRectF(QPointF(0,0), geometry().size());
}

//QPainterPath MemoryItem::shape() const
//{
//    QPainterPath path;
//    path.addRect(boundingRect());
// //    path.addRect(m_borderWidth,m_borderWidth,m_edgeLength,m_edgeLength);
//    return path;
//}

void MemoryItem::setGeometry(const QRectF &geom)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.topLeft());
}

QSizeF MemoryItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    switch (which) {
    case Qt::MinimumSize:
    case Qt::PreferredSize:
    case Qt::MaximumSize:
        return QSizeF(m_edgeLength + 2*m_borderWidth,m_edgeLength + 2*m_borderWidth);
    default:
        break;
    }
    return constraint;
}


