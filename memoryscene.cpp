#include "memoryscene.hpp"

#include "memoryinteractiveunit.hpp"

#include <QGraphicsSceneMouseEvent>

#include <QApplication>
#include <QDebug>


MemoryScene::MemoryScene( QObject * parent)
    :QGraphicsScene(parent)
{
    clearLastSelected();

    setItemEdge(DEFAULT_EDGELENGTH);
    setItemBorder(DEFAULT_BORDERWIDTH);

    m_items.clear();
    m_units.clear();
    m_lastSelected=NULL;

    m_memoryWidget = new MemoryWidget;

    m_memoryWidget->setLabels(true);

    addItem(m_memoryWidget);

    m_memoryWidget->setSpacing(0);
    m_memoryWidget->setItemPerRow(64);

    QList<MemoryItemPresentation> records;

    int memoryPeaceLength,spaceBetweenUnits;

    int vacantPos = 0;
    int id = 1;

    for(;;)
    {
        memoryPeaceLength = qrand()%100;
        spaceBetweenUnits = qrand()%15;

        MemoryItemPresentation newPeace;
        vacantPos+=spaceBetweenUnits;
        newPeace.m_start=vacantPos;
        vacantPos+=memoryPeaceLength;

        if(vacantPos>2047)
            break;

        newPeace.m_finish=vacantPos;
        vacantPos+=1;

        newPeace.m_state=static_cast<MemoryState>(qrand()%Memory::StateCount);
        if(newPeace.m_state==Memory::Freed)
            newPeace.m_unitId=0;
        else
        {
            newPeace.m_unitId=id++;
            records.push_back(newPeace);
        }
    }


    init(records,2048);
}

MemoryScene::~MemoryScene()
{
}

void MemoryScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> itemsAtPos = items(event->scenePos());


    MemoryItem* p_mem = NULL;

    foreach(QGraphicsItem* itemAtPos,itemsAtPos)
    {
        if((p_mem=dynamic_cast<MemoryItem*>(itemAtPos)))
            break;
    }
    if(!p_mem)
    {
        return;
    }

    setLastSelected(p_mem);
    return QGraphicsScene::mousePressEvent(event);

}

void MemoryScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_lastSelected
//       && (QApplication::keyboardModifiers()&Qt::ShiftModifier)
            )
    {

        QList<QGraphicsItem*> itemsAtPos = items(event->scenePos());
        MemoryItem * p_mem = NULL;

        foreach(QGraphicsItem* itemAtPos,itemsAtPos)
        {
            if((p_mem=dynamic_cast<MemoryItem*>(itemAtPos)))
                break;
        }

        if(!p_mem)
            return;

        clearSelection();

        int newSelectedIndex = p_mem->index();

        QList<QGraphicsItem*> sceneItems = items();

        int min = qMin(m_lastSelectedIndex,newSelectedIndex),
            max = qMax(m_lastSelectedIndex,newSelectedIndex);

        for(int i = 0; i < sceneItems.size(); ++i)
        {
            MemoryItem* p_itemAt = dynamic_cast<MemoryItem*>(sceneItems[i]);
            if(!p_itemAt)
            {
                continue;
            }

            if(p_itemAt->index()>= min && p_itemAt->index()<= max)
                p_itemAt->setSelected(true);
        }
    }

    return QGraphicsScene::mouseMoveEvent(event);
}

void MemoryScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    clearLastSelected();

    return QGraphicsScene::mouseReleaseEvent(event);
}

void MemoryScene::keyPressEvent(QKeyEvent *event)
{
    return QGraphicsScene::keyPressEvent(event);
}

void MemoryScene::keyReleaseEvent(QKeyEvent *event)
{
    return QGraphicsScene::keyReleaseEvent(event);
}

void MemoryScene::init(const QList<MemoryItemPresentation> &mem_it_list,long memSize)
{
    MemoryUnit * p_memUnit = NULL;

    setMemorySize(memSize);

    for(int i = 0; i<memorySize(); ++i)
    {
        m_items.append(new MemoryItem(i,itemEdge(),itemBorder(),m_memoryWidget));
        m_itemsParents.append(NULL);
    }


    for(int i = 0; i < mem_it_list.size(); ++i)
    {
        p_memUnit = new MemoryUnit(m_memoryWidget);
        p_memUnit->setState(mem_it_list[i].m_state);
        p_memUnit->setUnitId(mem_it_list[i].m_unitId);
        p_memUnit->addItems(mem_it_list[i].m_start,mem_it_list[i].m_finish,m_items);

        m_unit_by_unitId.insert(mem_it_list[i].m_unitId,p_memUnit);
        m_units.append(p_memUnit);
    }

    m_memoryWidget->setupMatrix(m_items);

    updateParenthesis();

    m_interactiveUnit = new MemoryInteractiveUnit(this,m_memoryWidget);

}

MemoryUnit* MemoryScene::newUnit(int unitId)
{
    MemoryUnit* p_memUnit = NULL;
    if(unitId == -1)
    {
        int vacantUnitId = 0;
        for(;;++vacantUnitId)
        {
            if(!m_unit_by_unitId.contains(vacantUnitId))
                break;
        }
        unitId = vacantUnitId;
    }
    else if(m_unit_by_unitId.contains(unitId))
        return m_unit_by_unitId[unitId];

    p_memUnit = new MemoryUnit(m_memoryWidget);
    p_memUnit->setState(Memory::Freed);
    p_memUnit->setUnitId(unitId);
    m_unit_by_unitId.insert(unitId,p_memUnit);
    m_units.append(p_memUnit);

    return p_memUnit;
}

MemoryUnit *MemoryScene::unit(int unitId) const
{
    return m_unit_by_unitId.value(unitId);
}

void MemoryScene::setItemInfo(const QString &text)
{
    m_memoryWidget->setItemInfo(text);
    memoryStatusUpdate();
}

void MemoryScene::setUnitInfo(const QString &text)
{
    m_memoryWidget->setUnitInfo(text);
    memoryStatusUpdate();
}

//QStatusBar *MemoryScene::statusBar()
//{
//    return m_memoryWidget->m_statusBar;
//}

int MemoryScene::itemPerRow() const
{
    return m_memoryWidget->itemPerRow();
}

void MemoryScene::setItemPerRow(int newItemPerRow)
{
    if(newItemPerRow==itemPerRow())
        return;

    m_memoryWidget->setItemPerRow(newItemPerRow);
    m_memoryWidget->setupMatrix(m_items);
    updateParenthesis();

}

qreal MemoryScene::itemEdge() const
{
    return m_itemEdge;
}

void MemoryScene::setItemEdge(qreal newEdgeLength)
{
    m_itemEdge = newEdgeLength;
    foreach(MemoryItem* item, m_items)
    {
        item->setEdgeLength(m_itemEdge);
    }
}

void MemoryScene::clearLastSelected()
{
    m_lastSelected = NULL;
    m_lastSelectedIndex = -1;
}

void MemoryScene::setLastSelected(MemoryItem *p_mem)
{
    m_lastSelected = p_mem;
    if(!p_mem)
    {
        m_lastSelectedIndex = -1;
    }
    else
    {
        m_lastSelectedIndex = p_mem->index();
    }
}

int MemoryScene::itemIndex(QGraphicsItem *item) const
{
    return items().indexOf(item);
}

void MemoryScene::memoryStatusUpdate(const QRectF &rect)
{
    m_memoryWidget->memoryStatusUpdate(rect);
}

void MemoryScene::transformChanged(const QTransform &transform)
{
    m_memoryWidget->transformChanged(transform);
}
long MemoryScene::memorySize() const
{
    return m_memorySize;
}

void MemoryScene::setMemorySize(long memorySize)
{
    m_memorySize = memorySize;
}

void MemoryScene::viewResized(QSizeF viewSize)
{
    qreal viewWidth = viewSize.width();

    int newItemPerRow = (viewWidth-spacing())
                              /(spacing()+itemEdge()+2*itemBorder())
                        - ((m_memoryWidget->labels())?1:0);




    if(itemPerRow()!=newItemPerRow)
        setItemPerRow(newItemPerRow);

    setSceneRect(m_memoryWidget->geometry());

}

void MemoryScene::showInteractiveRange(long start, long finish)
{
    m_interactiveUnit->setRange(start,finish);
}

void MemoryScene::hideInteractiveRange()
{
    m_interactiveUnit->setEnable(false);
}

void MemoryScene::updateParenthesis()
{
    for(int i=0;i<m_units.size();++i)
    {
        m_units[i]->updateParenthesis();
    }
}

qreal MemoryScene::itemBorder() const
{
    return m_itemBorder;
}

void MemoryScene::setItemBorder(const qreal &itemBorder)
{
    m_itemBorder = itemBorder;
    foreach(MemoryItem* item,m_items)
        item->setBorderWidth(itemBorder);
}


qreal MemoryScene::spacing() const
{
    return m_memoryWidget->spacing();
}

void MemoryScene::setSpacing(const qreal &spacing)
{
    m_memoryWidget->setSpacing(spacing);
}





