#include "memoryitem.hpp"
#include "memoryscene.hpp"
#include "globalvalues.hpp"


#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

#include <QDebug>


MemoryItem::MemoryItem(long index,QGraphicsItem *parent/* = 0*/)
    : QGraphicsLayoutItem(), QGraphicsItem(parent)
{
    setGraphicsItem(this);
    m_edgeLength = DEFAULT_EDGELENGTH;
    m_borderWidth = DEFAULT_BORDERWIDTH;

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


    QColor fillColor = (option->state & QStyle::State_Selected) ? m_color.dark(150) : m_color;
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
    MemoryScene * mem_scene = dynamic_cast<MemoryScene*>(scene());
    if(!mem_scene)
    {
        qDebug() << "not MemoryScene";
        return;
    }

    MemoryUnit* par_unit = dynamic_cast<MemoryUnit*>(parentItem());
    if(!par_unit)
    {
//        qDebug()<<"MemoryItem::hoverEnterEvent MemoryItem has no parent of MemoryUnit";
        return;
    }

    mem_scene->setItemInfo(QString::number(m_index)+" : "+par_unit->status());
}

void MemoryItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{

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

void MemoryItem::setColor(const QColor &newColor)
{
    if(newColor!=m_color)
    {
        m_color = newColor;
    }
}

long MemoryItem::index() const
{
    return m_index;
}

void MemoryItem::setIndex(long index)
{
    m_index = index;
}

QColor MemoryItem::color() const
{
    return m_color;
}

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


