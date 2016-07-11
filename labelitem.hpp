#ifndef LABELITEM_HPP
#define LABELITEM_HPP

#include "globalvalues.hpp"

#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <QColor>

#include <QString>


class LabelItem : public QGraphicsLayoutItem, public QGraphicsItem
{
public:
    LabelItem(QGraphicsItem *parent = 0);
    LabelItem(  const QString& label = DEFAULT_LABEL,
                int edgeLength = DEFAULT_EDGELENGTH,
                QColor color = DEFAULT_LABELCOLOR,
                qreal borderWidth = DEFAULT_BORDERWIDTH,
                QGraphicsItem *parent = 0);
    virtual ~LabelItem();

    // Inherited from QGraphicsLayoutItem
    void setGeometry(const QRectF &geom);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

    // Inherited from QGraphicsItem
    QRectF boundingRect() const;
//    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget = 0);


    QString getLabel() const;
    void setLabel(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &color);

public slots:

private:

    int m_edgeLength;
    qreal m_borderWidth;
    QString m_label;
    QColor m_color;

};

#endif // LABELITEM_HPP

