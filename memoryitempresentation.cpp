#include "memoryitempresentation.hpp"

#include <QDebug>

using namespace Memory;

MemoryItemPresentation::MemoryItemPresentation(MemoryState status, int unitId)
{
    m_state = status;
    m_unitId = unitId;
}


QColor MemoryItemPresentation::color() const
{
    return MemoryState_to_QColor(m_state);
}


QString operator+(const QString &qstr, MemoryState status)
{
    return qstr+MemoryState_to_Qstring(status);
}

QString MemoryState_to_Qstring(MemoryState status)
{
    switch(status)
    {
    case Empty:
        return "Empty";
    case Busy:
        return "Busy";
    case Read:
        return "Read";
    case Free:
        return "Free";
    default:
        return "MemoryState::Undefined";
    }
}


QColor MemoryState_to_QColor(MemoryState state)
{
    switch(state)
    {
    case Memory::Empty:
        return QColor::fromRgb(0xCC,0xFF,0xCC);
    case Memory::Busy:
        return QColor::fromRgb(0xFF,0x7C,0x80);
    case Memory::Read:
        return QColor::fromRgb(0xFF,0xF2,0xCC);
    case Memory::Free:
        return QColor::fromRgb(0xCC,0xEC,0xFF);

    default:
        qDebug() << "MemoryState_to_QColor() default case";
        return Qt::black;
    }
}
