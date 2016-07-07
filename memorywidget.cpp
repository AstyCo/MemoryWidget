#include "memorywidget.h"

#include "memoryitem.h"
#include <QGraphicsGridLayout>
#include <QSizePolicy>

#include <QDebug>

MemoryWidget::MemoryWidget(QGraphicsWidget *parent) :
    QGraphicsWidget(parent)
{
    setItemPerRow(64);

    MemoryColorsList records;

    for(int i = 0; i < 32; ++i)
    {
        for(int j = 0; j < itemPerRow(); ++j)
        {
            records.push_back(QColor((j?(i?Qt::red:Qt::green):Qt::blue)));
        }
    }

    setupMatrix(records);
}

MemoryWidget::~MemoryWidget()
{
}

void MemoryWidget::changeColor(int x, int y, const QColor &newColor)
{
    if(!layout())
    {
        qDebug()<<"layout is 0";
        return;
    }
    MemoryItem* p_mem = dynamic_cast<MemoryItem*>(layout()->itemAt(fromPos(x,y)));
    if(!p_mem)
    {
        qDebug() << "not MemoryItem";
        return;
    }
    p_mem->setColor(newColor);
}

void MemoryWidget::changeColor(int pos,const QColor &newColor)
{
    changeColor(toRow(pos),toColumn(pos),newColor);
}

void MemoryWidget::changeColors(int fromPos, int toPos, const QColor &newColor)
{
    for(int i=fromPos;i<toPos;++i)
        changeColor(i,newColor);
}

void MemoryWidget::changeColors(int fromRow, int fromCol, int toRow, int toCol, const QColor &newColor)
{
    changeColors(fromPos(fromRow,fromCol),fromPos(toRow,toCol),newColor);
}

void MemoryWidget::changeColors(const MemoryRecordsList &records)
{
    foreach(const MemoryRecord& record, records)
    {
        changeColor(record.x,record.y,record.color);
    }
}

int MemoryWidget::toColumn(int index) const
{
    return index % itemPerRow();
}

int MemoryWidget::toRow(int index) const
{
    return index / itemPerRow();
}

int MemoryWidget::fromPos(int row, int column) const
{
    return row*itemPerRow()+column;
}



void MemoryWidget::setupMatrix(MemoryColorsList colors)
{
    QGraphicsGridLayout * gridLayout = new QGraphicsGridLayout;

    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setSpacing(1);

    QSizePolicy sizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    for(int i=0;i<colors.size();++i)
    {
        MemoryItem * memoryItem = new MemoryItem(this);
        memoryItem->setColor(colors[i]);
        gridLayout->addItem(memoryItem, toRow(i), toColumn(i));
    }

    setLayout(gridLayout);

    changeColor(1,1,Qt::white);//REMOVABLE
    changeColors(200,500,Qt::yellow);//REMOVABLE

    adjustSize();
    gridLayout->setSizePolicy(sizePolicy);
    qDebug()<<rect();
}

QGraphicsLayout *MemoryWidget::layout()
{
    return QGraphicsWidget::layout();
}
int MemoryWidget::itemPerRow() const
{
    return m_itemPerRow;
}

void MemoryWidget::setItemPerRow(int itemPerRow)
{
    m_itemPerRow = itemPerRow;
}
