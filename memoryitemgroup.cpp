#include "memoryitemgroup.h"

MemoryItemGroup::MemoryItemGroup()
{

}

int MemoryItemGroup::groupId() const
{
    return m_groupId;
}

void MemoryItemGroup::setGroupId(int groupId)
{
    m_groupId = groupId;
}

void MemoryItemGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

