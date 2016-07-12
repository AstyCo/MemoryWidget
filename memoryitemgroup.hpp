#ifndef MEMORYITEMGROUP_HPP
#define MEMORYITEMGROUP_HPP


#include <QGraphicsItemGroup>
#include <QColor>

#include <QPainterPath>

class MemoryItemGroup : public QGraphicsItemGroup
{
public:
    MemoryItemGroup();


    int groupId() const;
    void setGroupId(int groupId);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QColor groupColor() const;
    void setGroupColor(const QColor &groupColor);

    QPainterPath shape() const;

private:

    int m_groupId;
    QColor m_groupColor;
};

#endif // MEMORYITEMGROUP_HPP
