
#include "labelitem.hpp"
#include "globalvalues.hpp"

#include <QPainter>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

#include <QGraphicsScene>
#include <QFont>

#include <QDebug>

LabelItem::LabelItem(QGraphicsItem *parent/* = 0*/)
    : QGraphicsLayoutItem(), QGraphicsItem(parent)
{
    setGraphicsItem(this);
    m_edgeLength = DEFAULT_EDGELENGTH;
    m_borderWidth = DEFAULT_BORDERWIDTH;
    setColor(DEFAULT_LABELCOLOR);
    setLabel(DEFAULT_LABEL);

}

LabelItem::LabelItem(const QString& label, int edgeLength, QColor color, qreal borderWidth, QGraphicsItem *parent)
    : QGraphicsLayoutItem(), QGraphicsItem(parent)
{
    m_edgeLength = edgeLength;
    m_borderWidth = borderWidth;
    setColor(color);
    setLabel(label);
}

LabelItem::~LabelItem()
{

}


void LabelItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/)
{
//    Q_UNUSED(widget);

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

QColor LabelItem::getColor() const
{
    return m_color;
}

void LabelItem::setColor(const QColor &color)
{
    m_color = color;
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
