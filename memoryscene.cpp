#include "memoryscene.hpp"

#include <QGraphicsSceneMouseEvent>

#include <QApplication>
#include <QDebug>


MemoryScene::MemoryScene( QObject * parent)
    :QGraphicsScene(parent)
{
    clearLastSelected();

    m_memoryWidget = new MemoryWidget;

    addItem(m_memoryWidget);
//    m_memoryWidget->setSpacing(5);
    m_memoryWidget->setItemPerRow(64);

    QList<MemoryItemPresentation> records;

    for(int i = 0; i < 32; ++i)
    {
        for(int j = 0; j < m_memoryWidget->itemPerRow(); ++j)
        {
            records.push_back(MemoryItemPresentation((j==i)?(Memory::Active):(Memory::Empty),(j==i)?1:0));
        }
    }

    init(records);

}

MemoryScene::~MemoryScene()
{
}

void MemoryScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem*> itemsAtPos = items(event->scenePos());


    MemoryItem* p_mem ;

    foreach(QGraphicsItem* itemAtPos,itemsAtPos)
    {
        if((p_mem=dynamic_cast<MemoryItem*>(itemAtPos)))
            break;
    }
    if(!p_mem)
    {
        qDebug() <<"p_mem is NULL";
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
        clearSelection();

        QList<QGraphicsItem*> itemsAtPos = items(event->scenePos());
        MemoryItem * p_mem;

        foreach(QGraphicsItem* itemAtPos,itemsAtPos)
        {
            if((p_mem=dynamic_cast<MemoryItem*>(itemAtPos)))
                break;
        }

        if(!p_mem)
            return;

//        qDebug() << "MemoryScene::mouseMoveEvent not NULL p_mem";

        int newSelectedIndex = p_mem->index();

        QList<QGraphicsItem*> sceneItems = items();

        int min = qMin(m_lastSelectedIndex,newSelectedIndex),
            max = qMax(m_lastSelectedIndex,newSelectedIndex);

        for(int i = 0; i < sceneItems.size(); ++i)
        {
            MemoryItem* p_itemAt = dynamic_cast<MemoryItem*>(sceneItems[i]);
            if(!p_itemAt)
            {
//                qDebug() << "not MemoryItem : MemoryScene::mouseMoveEvent";
                continue;
            }

//            qDebug() << "MemoryScene::mouseMoveEvent settingSelected";
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
    Q_UNUSED(event);
}

void MemoryScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift)
    {
        clearLastSelected();
    }
}

void MemoryScene::init(const QList<MemoryItemPresentation> &mem_it_list)
{
    MemoryUnit * p_memUnit;
    for(int i = 0; i < mem_it_list.size(); ++i)
    {
        if(!m_unit_by_unitId.contains(mem_it_list[i].m_unitId))
        {
            p_memUnit = new MemoryUnit(m_memoryWidget);
            p_memUnit->setStatus(Memory::Empty);
            p_memUnit->setUnitId(mem_it_list[i].m_unitId);
            m_unit_by_unitId.insert(mem_it_list[i].m_unitId,p_memUnit);
            m_units.append(p_memUnit);
        }
        else
            p_memUnit = m_unit_by_unitId[mem_it_list[i].m_unitId];

        MemoryItem* p_mem = new MemoryItem(i,p_memUnit);
        p_mem->setColor(mem_it_list[i].color());
        m_items.append(p_mem);
    }

    m_memoryWidget->setupMatrix(m_items);
}

MemoryUnit* MemoryScene::newUnit(int unitId)
{
    MemoryUnit* p_memUnit;
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
    p_memUnit->setStatus(Memory::Empty);
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
    m_memoryWidget->m_info1->setText(text);
}

void MemoryScene::setUnitInfo(const QString &text)
{
    m_memoryWidget->m_info2->setText(text);
}

void MemoryScene::clearLastSelected()
{
//    qDebug() << "clearLastSelected";
    m_lastSelected = NULL;
    m_lastSelectedIndex = -1;
}

void MemoryScene::setLastSelected(MemoryItem *p_mem)
{
//    qDebug() << "setLastSelected";
    m_lastSelected = p_mem;
    m_lastSelectedIndex = p_mem->index();
}

int MemoryScene::itemIndex(QGraphicsItem *item) const
{
    return items().indexOf(item);
}

qreal MemoryScene::spacing() const
{
    return m_memoryWidget->spacing();
}

void MemoryScene::setSpacing(const qreal &spacing)
{
    m_memoryWidget->setSpacing(spacing);
}

//void MemoryScene::uniqueSelection()
//{
//    for(int i=0;i<lastSelection.size();++i)
//    {
//        for(int j = i + 1; j<lastSelection.size();++j)
//        {
//            if(lastSelection[i]==lastSelection[j])
//            {
//                qDebug() <<QString("removingAt : ")+"before : "+ QString::number(lastSelection.size());
//                lastSelection.removeAt(j);
//                qDebug() <<QString("removingAt : ")+"after : "+ QString::number(lastSelection.size());
//            }
//        }
//    }
//}

//QGraphicsItem const *MemoryScene::findFirst(QList<QGraphicsItem*> const*list,
//                                      QGraphicsItem const *first, QGraphicsItem const *second) const
//{
//    QListIterator<QGraphicsItem*> it(*list);
//    while(it.hasNext())
//    {
//        QGraphicsItem * tmp = it.next();
//        if(tmp == first)
//            return first;
//        if(tmp == second)
//            return second;
//    }
//    return NULL;
//}





