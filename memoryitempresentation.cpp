#include "memoryitempresentation.hpp"

#include <QDebug>

using namespace Memory;

MemoryItemPresentation::MemoryItemPresentation(MemoryStatus status, int unitId)
{
    m_status = status;
    m_unitId = unitId;
}

MemoryItemPresentation::MemoryItemPresentation(int unitId, MemoryStatus status)
{
    m_status = status;
    m_unitId = unitId;
}

QColor MemoryItemPresentation::color() const
{
    switch(m_status)
    {
    case Memory::Empty:
        return Qt::white;
    case Memory::Active:
        return Qt::black;

    default:
        qDebug() << "MemoryItemPresentation::color() default case";
        return Qt::red;
    }
}


QString operator+(const QString &qstr, MemoryStatus status)
{
    return qstr+MemoryStatus_to_Qstring(status);
}

QString MemoryStatus_to_Qstring(MemoryStatus status)
{
    switch(status)
    {
    case Empty:
        return "Empty";
    case Active:
        return "Active";
    default:
        return "UNDEFINED";
    }
}
