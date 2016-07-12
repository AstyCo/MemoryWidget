#include "memoryitem.hpp"
#include "memoryscene.hpp"
#include "globalvalues.hpp"


#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

#include <QDebug>


extern MemoryScene* mem_scene;

MemoryItem::MemoryItem(long index,qreal edgeLength,qreal borderWidth,QGraphicsItem *parent/* = 0*/)
    : QGraphicsLayoutItem(), QGraphicsItem(parent)
{
    setGraphicsItem(this);

    m_parentUnit = dynamic_cast<MemoryUnit*>(parent);
        // NULL if not MemoryUnit*
    m_edgeLength = edgeLength;
    m_borderWidth = borderWidth;

    setFlags(ItemIsSelectable);
    setAcceptsHoverEvents(true);

    setIndex(index);
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
    if(!mem_scene)
        return;

    if(parentUnitId())
        setParentUnitSelected(true);

    mem_scene->setItemInfo(QString::number(index()));
    mem_scene->setUnitInfo(QString(QObject::tr("Unit Group Id: ")+
                                   QString::number(parentUnitId())
                                   +QString(QObject::tr("  Unit State: "))
                                   +state()));

    return QGraphicsItem::hoverEnterEvent(event);
}

void MemoryItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setParentUnitSelected(false);

    return QGraphicsItem::hoverLeaveEvent(event);
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

    return Memory::Empty;
}

QColor MemoryItem::color() const
{
    if(m_parentUnit)
    {
        return m_parentUnit->color();
    }

    return MemoryState_to_QColor(Memory::Empty);
}

int MemoryItem::parentUnitId() const
{
    if(m_parentUnit)
    {
        return m_parentUnit->unitId();
    }

    return 0;
}

//QPainterPath MemoryItem::opaqueArea() const
//{
//    QPainterPath path;
//    path.addRect(boundingRect());
//    return path;
//}

//void MemoryItem::setToolTip(const QString &toolTip)
//{
//    return QGraphicsItem::setToolTip(toolTip);
//}

//QString MemoryItem::toolTip() const
//{
//    return QGraphicsItem::toolTip();
//}

//void MemoryItem::setColor(const QColor &newColor)
//{
//    if(newColor!=m_color)
//    {
//        m_color = newColor;
//    }
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


