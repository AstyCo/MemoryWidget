#include "memoryitem.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

#include <QGraphicsScene>
#include <QFont>

#include <QDebug>

qreal global_edgeLength = 16;
qreal global_borderWidth = 0.5;

#define GLOBAL_BORDER_COLOR (Qt::black)   //(scene()->backgroundBrush().color())
#define GLOBAL_EMPTY_LABEL_COLOR (Qt::gray)


LabelItem::LabelItem(QGraphicsItem *parent/* = 0*/)
    : QGraphicsLayoutItem(), QGraphicsItem(parent)
{
    setGraphicsItem(this);
    m_edgeLength = global_edgeLength;
    m_borderWidth = global_borderWidth;


}

LabelItem::~LabelItem()
{

}


void LabelItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/)
{
    Q_UNUSED(widget);

//    qDebug()<<"paint LabelItem";


    QRectF squareItem( m_borderWidth, m_borderWidth, m_edgeLength, m_edgeLength);
    QColor squareColor = Qt::white;//scene()->backgroundBrush().color();
    if(getLabel().isEmpty())
        squareColor = GLOBAL_EMPTY_LABEL_COLOR;

//    painter->setRenderHint(QPainter::Antialiasing);
    if(m_borderWidth)
    {
        QRectF extSquareItem( 0, 0, m_edgeLength+2*m_borderWidth, m_edgeLength+2*m_borderWidth);
        QColor extSquareColor = GLOBAL_BORDER_COLOR;
        QPainterPath externalFigure;
        externalFigure.addRect(extSquareItem);
        painter->setPen(Qt::NoPen);
        painter->fillPath(externalFigure, extSquareColor);
        painter->drawPath(externalFigure);
    }
    QPainterPath path;
    path.addRect(squareItem);
    painter->setPen(Qt::NoPen);
    painter->fillPath(path, squareColor);
    painter->drawPath(path);

//DRAW TEXT



    if(!m_label.isEmpty())
    {
//        painter->setRenderHint(QPainter::TextAntialiasing,false);
//        QFont font = painter->font();
//        font.setPixelSize(5);
//        painter->setFont(font);
        QPen textPen(Qt::black);
        painter->setPen(textPen);
        painter->drawText(QRectF(QPoint(0,0),geometry().size()),Qt::AlignCenter,m_label);
    }
}
QString LabelItem::getLabel() const
{
    return m_label;
}

void LabelItem::setLabel(const QString &value)
{
    m_label = value;
}


QRectF LabelItem::boundingRect() const
{
    return QRectF( 0, 0, m_edgeLength + 2*m_borderWidth, m_edgeLength + 2*m_borderWidth);
}

//QPainterPath LabelItem::shape() const
//{
//    QPainterPath path;
//    path.addRect(boundingRect());
// //    path.addRect(m_borderWidth,m_borderWidth,m_edgeLength,m_edgeLength);
//    return path;
//}

void LabelItem::setGeometry(const QRectF &geom)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.topLeft());
}

QSizeF LabelItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
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






MemoryItem::MemoryItem(QGraphicsItem *parent/* = 0*/)
    : QGraphicsLayoutItem(), QGraphicsItem(parent)
{
    setGraphicsItem(this);
    m_edgeLength = global_edgeLength;
    m_borderWidth = global_borderWidth;

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


