#ifndef MEMORYSTATUS_HPP
#define MEMORYSTATUS_HPP

#include <QGraphicsItem>
#include <QGraphicsLayoutItem>

#include <QString>




class MemoryStatus : public QGraphicsItem, public QGraphicsLayoutItem
{
public:
    MemoryStatus(QGraphicsItem* parent = 0);
    virtual ~MemoryStatus();

    // Inherited from QGraphicsLayoutItem
    void setGeometry(const QRectF &geom);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

    // Inherited from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget = 0);

    QString statusLabel() const;
    void setStatusLabel(const QString &statusLabel);

    QString itemInfo() const;
    void setItemInfo(const QString &itemInfo);

    QString unitInfo() const;
    void setUnitInfo(const QString &unitInfo);

private:
    QString m_statusLabel;
    QString m_itemInfo;
    QString m_unitInfo;

    QRect   m_statusLabelRect,
            m_itemInfoRect,
            m_unitInfoRect;
};

#endif // MEMORYSTATUS_HPP
