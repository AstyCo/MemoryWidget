#ifndef MEMORYWIDGET_HPP
#define MEMORYWIDGET_HPP

//#include "memoryitempresentation.hpp"
#include "memoryitem.hpp"

#include <QGraphicsWidget>

#include <QPoint>
#include <QColor>
#include <QList>

#include <QStatusBar>
#include <QLabel>


struct MemoryRecord
{
    int x,y;
    QColor color;
};
typedef QList<MemoryRecord> MemoryRecordsList;


typedef QList<QColor> MemoryColorsList;


class MemoryWidget : public QGraphicsWidget
{
    Q_OBJECT

public:
    explicit MemoryWidget(QGraphicsWidget *parent = 0);
    ~MemoryWidget();

    int itemPerRow() const;
    void setItemPerRow(int itemPerRow);
    void changeColor(int x,int y,const QColor& newColor);
    void changeColor(int pos,const QColor& newColor);
    void changeColors(const MemoryRecordsList& records);
    void changeColors(int fromPos, int toPos,   const QColor& newColor);
    void changeColors(int fromRow, int fromCol,
                      int toRow, int toCol,     const QColor& newColor);
    void setupMatrix(QList<MemoryItem*> records);

    bool labels() const;
    void setLabels(bool labels);

    qreal spacing() const;
    void setSpacing(const qreal &spacing);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int toColumn(int index) const;
    int toRow(int index) const;

    int fromPos(int row,int column) const;
    int toMemoryAdress(int row,int column) const;
    int toMemoryAdress(int pos) const;

private:

    QGraphicsLayout *layout();

    int m_itemPerRow;
    bool m_labels;
    qreal m_spacing;
public:
    QStatusBar* m_statusBar;
    QLabel * m_info1, *m_info2;
};

#endif // MEMORYWIDGET_HPP
