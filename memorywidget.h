#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

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

    bool labels() const;
    void setLabels(bool labels);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int toColumn(int index) const;
    int toRow(int index) const;

    int fromPos(int row,int column) const;
    int toMemoryAdress(int row,int column) const;
    int toMemoryAdress(int pos) const;

    void setupMatrix(MemoryColorsList records);
private:

    QGraphicsLayout *layout();

    int m_itemPerRow;
    bool m_labels;
    qreal m_spacing;
public:
    QStatusBar* m_statusBar;
    QLabel * m_info1, *m_info2;


};

#endif // MEMORYWIDGET_H
