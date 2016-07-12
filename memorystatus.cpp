#include "memorystatus.hpp"

#include "memoryscene.hpp"

#include <QPainter>

#include <QFontMetrics>

#include <QDebug>

extern MemoryScene* mem_scene;

MemoryStatus::MemoryStatus(QGraphicsItem* parent)
    : QGraphicsItem(parent), QGraphicsLayoutItem()
{
    setGraphicsItem(this);

}

MemoryStatus::~MemoryStatus()
{
}

void MemoryStatus::setGeometry(const QRectF &geom)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.topLeft());
}

QSizeF MemoryStatus::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    if(mem_scene)
    {
        switch (which) {
        case Qt::MinimumSize:
        case Qt::PreferredSize:
        case Qt::MaximumSize:
            return boundingRect().size();
        default:
            break;
        }
    }
    return constraint;
}

QRectF MemoryStatus::boundingRect() const
{
    return QRectF( 0, 0, parentItem()->boundingRect().width(), 20);
}

void MemoryStatus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

//    qDebug() << "MemoryStatus::paint";
//    qDebug() << boundingRect();

    QFontMetrics fm(painter->font());
    m_statusLabelRect = fm.tightBoundingRect(statusLabel());
    m_statusLabelRect.setHeight(boundingRect().height());
//    qDebug() << m_statusLabelRect;

    qreal tmpVal = (boundingRect().width()-m_statusLabelRect.width())/2;
    m_itemInfoRect = QRect(m_statusLabelRect.width()+5,0,tmpVal,boundingRect().height());
    m_unitInfoRect = QRect(m_statusLabelRect.width()+5+tmpVal,0,tmpVal,boundingRect().height());

//    qDebug() << m_itemInfoRect;
//    qDebug() << m_unitInfoRect;


    QPen textPen(Qt::black);
    painter->fillRect(boundingRect(),QBrush(Qt::white));
    painter->setPen(textPen);
//    qDebug()<<geometry();
    painter->drawText(QRectF(QPoint(5,0),m_statusLabelRect.size()),Qt::AlignLeft|Qt::AlignVCenter,statusLabel());

    painter->drawText(m_itemInfoRect,Qt::AlignCenter,itemInfo());
    painter->drawText(m_unitInfoRect,Qt::AlignCenter,unitInfo());

}
QString MemoryStatus::statusLabel() const
{
    return m_statusLabel;
}

void MemoryStatus::setStatusLabel(const QString &statusLabel)
{
    m_statusLabel = statusLabel;
}
QString MemoryStatus::itemInfo() const
{
    return m_itemInfo;
}

void MemoryStatus::setItemInfo(const QString &itemInfo)
{
    m_itemInfo = itemInfo;
}
QString MemoryStatus::unitInfo() const
{
    return m_unitInfo;
}

void MemoryStatus::setUnitInfo(const QString &unitInfo)
{
    m_unitInfo = unitInfo;
}




