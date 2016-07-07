#include "memoryitem.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

MemoryItem::MemoryItem(QGraphicsItem *parent/* = 0*/)
    : QGraphicsLayoutItem(), QGraphicsItem(parent)
{
    setGraphicsItem(this);
    m_edgeLength = 10;
    m_borderWidth = 0;

    setFlags(ItemIsSelectable);
    setAcceptsHoverEvents(true);
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
        fillColor = fillColor.blackF();
    }

    QRectF squareItem( m_borderWidth, m_borderWidth, m_edgeLength, m_edgeLength);
    QColor squareColor = fillColor;

//    painter->fillRect(squareItem,QBrush(m_color));

//    painter->setRenderHint(QPainter::Antialiasing);

    if(m_borderWidth)
    {
        QRectF extSquareItem( 0, 0, m_edgeLength+2*m_borderWidth, m_edgeLength+2*m_borderWidth);
        QColor extSquareColor = Qt::black;
        QPainterPath externalFigure;
        externalFigure.addRect(extSquareItem);
        painter->fillPath(externalFigure, extSquareColor);
        painter->drawPath(externalFigure);
    }
    QPainterPath path;
    path.addRect(squareItem);
    QPen pen(Qt::black, 0);
    painter->setPen(Qt::NoPen);
    painter->fillPath(path, squareColor);
    painter->drawPath(path);

}

void MemoryItem::setColor(const QColor &newColor)
{
    if(newColor!=m_color)
    {
        m_color = newColor;
    }
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

QPainterPath MemoryItem::shape() const
{
    QPainterPath path;
    path.addRect(m_borderWidth,m_borderWidth,m_edgeLength,m_edgeLength);
    return path;
}

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


