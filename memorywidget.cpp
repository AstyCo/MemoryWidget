#include "memorywidget.hpp"
#include "memoryscene.hpp"

#include "memorystatus.hpp"

#include "memoryitem.hpp"
#include "labelitem.hpp"

#include <QGraphicsGridLayout>
#include <QSizePolicy>

#include <QGraphicsSceneMouseEvent>

#include <QGraphicsProxyWidget>

#include <QPainter>
#include <QGraphicsItemGroup>


#include <QDebug>


MemoryWidget::MemoryWidget(QGraphicsWidget *parent) :
    QGraphicsWidget(parent)
{
    setItemPerRow(64);
    setLabels(false);
    m_spacing = DEFAULT_SPACING;

    m_memoryStatus = NULL;
}

MemoryWidget::~MemoryWidget()
{
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
    QGraphicsGridLayout * gridLayout = new QGraphicsGridLayout;

    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setSpacing(m_spacing);

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
    {
        // MemoryStatus
        m_memoryStatus = new MemoryStatus(this);
        m_memoryStatus->setStatusLabel(tr("Info:"));
        m_memoryStatus->setItemInfo(tr("Item Info"));
        m_memoryStatus->setUnitInfo(tr("Unit Info"));

        gridLayout->addItem(m_memoryStatus,toRow(mem_items.size()-1)+1,0,1,itemPerRow()+(labels()?1:0));

    }

    setLayout(gridLayout);

    adjustSize();
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

void MemoryWidget::setStatusLabel(const QString &text)
{
    m_memoryStatus->setStatusLabel(text);
}

QString MemoryWidget::statusLabel() const
{
    return m_memoryStatus->statusLabel();
}

void MemoryWidget::setItemInfo(const QString &text)
{
    m_memoryStatus->setItemInfo(text);
}

QString MemoryWidget::itemInfo() const
{
    return m_memoryStatus->itemInfo();
}

void MemoryWidget::setUnitInfo(const QString &text)
{
    m_memoryStatus->setUnitInfo(text);
}

QString MemoryWidget::unitInfo() const
{
    return m_memoryStatus->unitInfo();
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

void MemoryWidget::memoryStatusUpdate(const QRectF &rect)
{
    m_memoryStatus->update(rect);
}

int MemoryWidget::itemPerRow() const
{
    return m_itemPerRow;
}

void MemoryWidget::setItemPerRow(int itemPerRow)
{
    m_itemPerRow = itemPerRow;

}
