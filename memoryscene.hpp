#ifndef MEMORYSCENE_HPP
#define MEMORYSCENE_HPP

#include "memoryitem.hpp"
#include "memorywidget.hpp"
#include "memoryunit.hpp"

#include <QGraphicsScene>

#include <QList>
#include <QMap>

#include <QLabel>



class MemoryScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MemoryScene( QObject * parent = 0 );
    ~MemoryScene();

    qreal spacing() const;
    void setSpacing(const qreal &spacing);

    void init(const QList<MemoryItemPresentation>& mem_it_list);

    MemoryUnit* newUnit(int unitId = -1);
    MemoryUnit *unit(int unitId) const;

    void setItemInfo(const QString& text);
    void setUnitInfo(const QString& text);

protected:
//    void onSelectionChanged();
//    void onChanged();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    void clearLastSelected();
    void setLastSelected(MemoryItem* p_mem);
    int itemIndex(QGraphicsItem* item) const;


    int m_lastSelectedIndex;
    MemoryItem* m_lastSelected;
    MemoryWidget* m_memoryWidget;

    QList<MemoryUnit*> m_units;
    QList<MemoryItem*> m_items;
    QMap<int , MemoryUnit*> m_unit_by_unitId;

};

#endif // MEMORYSCENE_HPP
