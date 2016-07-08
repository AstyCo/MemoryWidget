#include "memorywidget.h"

#include "memoryitem.h"
#include <QGraphicsGridLayout>
#include <QSizePolicy>

#include <QGraphicsSceneMouseEvent>

#include <QDebug>

MemoryWidget::MemoryWidget(QGraphicsWidget *parent) :
    QGraphicsWidget(parent)
{
    setItemPerRow(64);
    setLabels(true);

//    setMaximumSize(1920,1680);

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
    return (labels()?1:0)+index % itemPerRow();
}

int MemoryWidget::toRow(int index) const
{
    return (labels()?1:0)+index / itemPerRow();
}

int MemoryWidget::fromPos(int row, int column) const
{
    return row*(itemPerRow()+(labels()?1:0))+column;
}

int MemoryWidget::toMemoryAdress(int row, int column) const
{
    return (row-(labels()?1:0))*itemPerRow()+(column-(labels()?1:0));
}

int MemoryWidget::toMemoryAdress(int pos) const
{
    return toMemoryAdress(toRow(pos),toColumn(pos));
}



void MemoryWidget::setupMatrix(MemoryColorsList colors)
{

    setLabels(true);

    QGraphicsGridLayout * gridLayout = new QGraphicsGridLayout;

    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setSpacing(0);

//    QSizePolicy sizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    LabelItem* emptyLabelItem = new LabelItem(this);
    gridLayout->addItem(emptyLabelItem,0,0);

    for(int j=0;j<itemPerRow();++j)
    {
        LabelItem* labelItem = new LabelItem(this);
        labelItem->setLabel(QString::number(j));
        gridLayout->addItem(labelItem,0,j+1);
    }

    for(int i=0;i<colors.size();++i)
    {
        if(!(i%itemPerRow()))
        {
            LabelItem* labelItem = new LabelItem(this);
            labelItem->setLabel(QString::number(i/itemPerRow()));
            gridLayout->addItem(labelItem,i/itemPerRow()+1,0);
        }
        MemoryItem * memoryItem = new MemoryItem(this);
        memoryItem->setColor(colors[i]);
        memoryItem->setToolTip(QString::number(i));
        gridLayout->addItem(memoryItem, toRow(i), toColumn(i));
    }

    setLayout(gridLayout);

    changeColors(210,500,Qt::yellow);//REMOVABLE

//    gridLayout->setSizePolicy(sizePolicy);
    qDebug()<<rect();

    adjustSize();
}

QGraphicsLayout *MemoryWidget::layout()
{
    return QGraphicsWidget::layout();
}
bool MemoryWidget::labels() const
{
    return m_labels;
}

void MemoryWidget::setLabels(bool labels)
{
    m_labels = labels;
}

int MemoryWidget::itemPerRow() const
{
    return m_itemPerRow;
}

void MemoryWidget::setItemPerRow(int itemPerRow)
{
    m_itemPerRow = itemPerRow;
}
