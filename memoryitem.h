#ifndef MEMORYITEM_H
#define MEMORYITEM_H

#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <QColor>

#include <QPainterPath>


class MemoryItem : public QGraphicsLayoutItem, public QGraphicsItem
{
public:
    MemoryItem(QGraphicsItem *parent = 0);
    virtual ~MemoryItem();

    // Inherited from QGraphicsLayoutItem
    void setGeometry(const QRectF &geom);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

    // Inherited from QGraphicsItem
    QRectF boundingRect() const;
//    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget = 0);

    virtual QPainterPath opaqueArea() const;


//    void setToolTip(const QString &toolTip);
//    QString toolTip() const;

    QColor color() const;


public slots:
    void setColor(const QColor& newColor);

private:
    int m_edgeLength;
    qreal m_borderWidth;
    QColor m_color;

};

#endif // MEMORYITEM_H
