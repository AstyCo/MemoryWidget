#ifndef MEMORYITEMPRESENTATION_HPP
#define MEMORYITEMPRESENTATION_HPP


#include <QColor>


namespace Memory
{
    enum MemoryState
    {
        Empty,
        Busy,
        Read,
        Free,
        StateCount
    };
}
using namespace Memory;

QString MemoryState_to_Qstring(MemoryState state);
QColor MemoryState_to_QColor(MemoryState state);

QString operator+(const QString& qstr, MemoryState status);


struct MemoryItemPresentation
{
    MemoryItemPresentation(MemoryState status = Empty, int unitId = 0);

    MemoryState m_state;

    // extra info here
    int m_unitId;

    //

    long m_start,
         m_finish;

    QColor color() const;
};

#endif // MEMORYITEMPRESENTATION_HPP

