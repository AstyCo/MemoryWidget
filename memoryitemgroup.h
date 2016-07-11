#ifndef MEMORYITEMGROUP_H
#define MEMORYITEMGROUP_H


#include <QGraphicsItemGroup>

class MemoryItemGroup : public QGraphicsItemGroup
{
public:
    MemoryItemGroup();


    int groupId() const;
    void setGroupId(int groupId);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    int m_groupId;
};

#endif // MEMORYITEMGROUP_H
