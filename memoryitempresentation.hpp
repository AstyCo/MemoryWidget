#ifndef MEMORYITEMPRESENTATION_HPP
#define MEMORYITEMPRESENTATION_HPP


#include <QColor>


namespace Memory
{
    enum MemoryStatus
    {
        Empty,
        Active
    };
}
using namespace Memory;

QString MemoryStatus_to_Qstring(MemoryStatus status);

QString operator+(const QString& qstr, MemoryStatus status);


struct MemoryItemPresentation
{
    MemoryItemPresentation(MemoryStatus status = Empty, int unitId = 0);
    MemoryItemPresentation(int unitId = 0, MemoryStatus status = Empty);

    MemoryStatus m_status;
    int m_unitId;

    QColor color() const;
};

#endif // MEMORYITEMPRESENTATION_HPP

