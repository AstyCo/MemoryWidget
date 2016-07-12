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
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget = 0);

    int unitId() const;
    void setUnitId(int unitId);

    Memory::MemoryStatus status() const;
    void setStatus(const Memory::MemoryStatus &status);

    long start() const;
    void setStart(long start);

    long finish() const;
    void setFinish(long finish);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    bool unitSelected() const;
    void setUnitSelected(bool unitSelected);


private:
    void rebuildPath();

    QPainterPath shapeBorder() const;
    void setShapeBorder(const QPainterPath &shapeBorder);

private:
    bool m_unitSelected;

    int m_unitId;
    Memory::MemoryStatus m_status;

    QPainterPath m_shapeBorder;
    QPen m_borderPen;

    QList<MemoryItem*> m_items;
    long m_start, m_finish;

};

#endif // MEMORYUNIT_HPP
