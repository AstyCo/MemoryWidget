#ifndef MEMORYITEM_HPP
#define MEMORYITEM_HPP

#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <QColor>

#include <QPainterPath>


class MemoryItem : public QGraphicsLayoutItem, public QGraphicsItem
{
public:
    MemoryItem(long index,QGraphicsItem *parent = 0);
    virtual ~MemoryItem();

    // Inherited from QGraphicsLayoutItem
    void setGeometry(const QRectF &geom);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

    // Inherited from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget = 0);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);


    QColor color() const;
    long index() const;
    void setIndex(long index);

public slots:
    void setColor(const QColor& newColor);

private:
    int m_edgeLength;
    qreal m_borderWidth;
    QColor m_color;

    long m_index;

};

#endif // MEMORYITEM_HPP
