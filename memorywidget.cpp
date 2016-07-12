#include "memorywidget.hpp"
#include "memoryitemgroup.hpp"
#include "memoryscene.hpp"

#include "memoryitem.hpp"
#include "labelitem.hpp"

#include <QGraphicsGridLayout>
#include <QSizePolicy>

#include <QGraphicsSceneMouseEvent>

#include <QGraphicsProxyWidget>

#include <QPainter>
#include <QGraphicsItemGroup>


#include <QDebug>

MemoryItemGroup *it_group = new MemoryItemGroup;

MemoryWidget::MemoryWidget(QGraphicsWidget *parent) :
    QGraphicsWidget(parent)
{
    setItemPerRow(64);
    setLabels(true);
    m_spacing = DEFAULT_SPACING;

//    setMaximumSize(1920,1680);

    m_statusBar = new QStatusBar();
    m_statusBar->setSizeGripEnabled(false);
    m_statusBar->setStyleSheet(
                "QStatusBar{ border: 0.5px solid black;}");
//    m_statusBar->set

    m_info1 = new QLabel();
    m_info2 = new QLabel();
    m_info1->setText(tr("info1"));
    m_info2->setText(tr("info2"));
    m_info1->setAlignment(Qt::AlignCenter);
    m_info2->setAlignment(Qt::AlignCenter);

    QLabel* statusBarLabel = new QLabel();
    statusBarLabel->setText(tr("Info: "));
    m_statusBar->addPermanentWidget(statusBarLabel,0);
    m_statusBar->addPermanentWidget(m_info1,1);
    m_statusBar->addPermanentWidget(m_info2,1);
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

    MemoryScene* p_memScene = dynamic_cast<MemoryScene*>(scene());
    if(!p_memScene)
    {
        qDebug() << "p_memScene is null (changeColor)";
    }
    else
    {
        MemoryUnit* p_memUnit;
        if((p_memUnit=p_memScene->newUnit(2)))
        {
            p_mem->setParentItem(p_memUnit);
            p_memUnit->setUnitSelected(true);
        }
    }

//    if(parent_item)
//    {
//        parent_item->setFlag(QGraphicsItem::ItemHasNoContents);
//        p_mem->setParentItem(parent_item);
//    }

//    qDebug()<<p_mem->geometry();
//    groupReg+=p_mem->geometry().toRect();

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



void MemoryWidget::setupMatrix(QList<MemoryItem*> mem_items)
{


//    QGraphicsGridLayout * topLayout = new QGraphicsGridLayout;
    QGraphicsGridLayout * gridLayout = new QGraphicsGridLayout;

    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setSpacing(m_spacing);


//    QSizePolicy sizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    if(labels())
    {
        LabelItem* emptyLabelItem = new LabelItem(this);
        gridLayout->addItem(emptyLabelItem,0,0);

        for(int j=0;j<itemPerRow();++j)
        {
            LabelItem* labelItem = new LabelItem(this);
            labelItem->setLabel(QString::number(j));
            gridLayout->addItem(labelItem,0,j+1);
        }
    }
    for(int i=0;i<mem_items.size();++i)
    {
        if(labels()&&!(i%itemPerRow()))
        {
            LabelItem* labelItem = new LabelItem(this);
            labelItem->setLabel(QString::number(i/itemPerRow()));
            gridLayout->addItem(labelItem,i/itemPerRow()+1,0);
        }
        gridLayout->addItem(mem_items[i], toRow(i), toColumn(i));
    }
    QGraphicsProxyWidget *pWidget = new QGraphicsProxyWidget(this);

    pWidget->setWidget(m_statusBar);

    gridLayout->addItem(pWidget,toRow(mem_items.size()-1)+1,0,1,itemPerRow()+(labels()?1:0));
//    gridLayout->setRowStretchFactor(toRow(colors.size()-1)+1,1);


    setLayout(gridLayout);

    adjustSize();

    changeColors(210,500,Qt::yellow);//REMOVABLE

//    gridLayout->setSizePolicy(sizePolicy);
//    qDebug()<<rect();


}

QGraphicsLayout *MemoryWidget::layout()
{
    return QGraphicsWidget::layout();
}

qreal MemoryWidget::spacing() const
{
    return m_spacing;
}

void MemoryWidget::setSpacing(const qreal &spacing)
{
    m_spacing = spacing;
}
bool MemoryWidget::labels() const
{
    return m_labels;
}

void MemoryWidget::setLabels(bool labels)
{
    m_labels = labels;
}

void MemoryWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // empty
}

int MemoryWidget::itemPerRow() const
{
    return m_itemPerRow;
}

void MemoryWidget::setItemPerRow(int itemPerRow)
{
    m_itemPerRow = itemPerRow;
}
