#ifndef MEMORYSCENE_HPP
#define MEMORYSCENE_HPP

#include "memoryitem.hpp"
#include "memorywidget.hpp"
#include "memoryunit.hpp"

#include <QGraphicsScene>

#include <QList>
#include <QMap>

#include <QLabel>

QT_FORWARD_DECLARE_CLASS(QStatusBar);

class MemoryInteractiveUnit;


class MemoryScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MemoryScene( QObject * parent = 0 );
    ~MemoryScene();

    qreal spacing() const;
    void setSpacing(const qreal &spacing);

    void init(const QList<MemoryItemPresentation>& mem_it_list,long memorySize);

    MemoryUnit* newUnit(int unitId = -1);
    MemoryUnit* unit(int unitId) const;

    void setItemInfo(const QString& text);
    void setUnitInfo(const QString& text);

    int itemPerRow() const;
    void setItemPerRow(int newItemPerRow);

    qreal itemEdge() const;
    void setItemEdge(qreal newEdgeLength);


    qreal itemBorder() const;
    void setItemBorder(const qreal &itemBorder);

    long memorySize() const;
    void setMemorySize(long memorySize);

    void viewResized(QSizeF viewSize);

    void showInteractiveRange(long start, long finish);
    void hideInteractiveRange();

    void updateParenthesis();

public slots:
    void transformChanged(const QTransform& transform);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    void clearLastSelected();
    void setLastSelected(MemoryItem* p_mem);
    int  itemIndex(QGraphicsItem* item) const;
    void memoryStatusUpdate(const QRectF& rect = QRectF());

public:
    int m_lastSelectedIndex;
    MemoryItem* m_lastSelected;
    MemoryWidget* m_memoryWidget;
    MemoryInteractiveUnit* m_interactiveUnit;

    QList<MemoryUnit*> m_units;
    QList<MemoryItem*> m_items;
    QList<MemoryUnit*> m_itemsParents;
    QMap<int , MemoryUnit*> m_unit_by_unitId;

    qreal m_itemEdge;
    qreal m_itemBorder;

    long m_memorySize;

    friend class MemoryInteractiveUnit;
};

#endif // MEMORYSCENE_HPP
