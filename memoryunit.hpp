#ifndef MEMORYUNIT_HPP
#define MEMORYUNIT_HPP

#include "memoryitempresentation.hpp"

#include <QGraphicsItem>
#include <QVariant>
#include <QPen>

class MemoryItem;

class MemoryUnit : public QGraphicsItem
{
public:
    MemoryUnit(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget = 0);

    int unitId() const;
    void setUnitId(int unitId);

    Memory::MemoryState state() const;
    void setState(const Memory::MemoryState &state);

    long start() const;
    void setStart(long start);

    long finish() const;
    void setFinish(long finish);

    long size() const;

    qreal spacing() const;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    bool unitSelected() const;
    void setUnitSelected(bool unitSelected);

    QColor color() const;


private:
    void rebuildPath();

    QPainterPath shapeBorder() const;
    void setShapeBorder(const QPainterPath &shapeBorder);

private:
    bool m_unitSelected;

    int m_unitId;
    Memory::MemoryState m_state;

    QPainterPath m_shapeBorder;
    QPen m_borderPen;

    QList<MemoryItem*> m_items;
    long m_start, m_finish;

};

#endif // MEMORYUNIT_HPP
