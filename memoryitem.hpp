#ifndef MEMORYITEM_HPP
#define MEMORYITEM_HPP

#include "memoryitempresentation.hpp"
#include "globalvalues.hpp"

#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <QColor>

#include <QPainterPath>

class MemoryUnit;

class MemoryItem : public QGraphicsLayoutItem, public QGraphicsItem
{
public:
    MemoryItem(long index,qreal edgeLength = DEFAULT_EDGELENGTH,
               qreal borderWidth = DEFAULT_BORDERWIDTH,QGraphicsItem *parent = 0);
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

    QString toolTip() const;
    void setToolTip(const QString &toolTip);

    void enableToolTip();
    void disableToolTip();

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);


    void setParentUnitSelected(bool selected);

    Memory::MemoryState state() const;
    QColor color() const;
//    int parentUnitId() const;

//    long parentUnitStart() const;
//    long parentUnitFinish() const;


    long index() const;
    void setIndex(long index);

    int edgeLength() const;
    void setEdgeLength(int edgeLength);

    qreal borderWidth() const;
    void setBorderWidth(const qreal &borderWidth);

public slots:
    //    void setColor(const QColor& newColor);

private:
    int m_edgeLength;
    qreal m_borderWidth;

    long m_index;

    MemoryUnit* m_parentUnit;

    bool m_isActive;    ///< Используется для затемнения

    bool m_isMarked;    ///< Используется для интерактивного выбора области памяти

};

#endif // MEMORYITEM_HPP
