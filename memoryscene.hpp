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
    void setItemBorder(qreal itemBorder);

    long memorySize() const;
    void setMemorySize(long memorySize);

    void viewResized(QSizeF viewSize);

    void showInteractiveRange(long start, long finish);
    void hideInteractiveRange();

    qreal itemSize() const;

    void updateParenthesis();

    friend bool MemoryItem::isHighlighted() const;
    friend void MemoryItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    bool highlightMode() const;
    void setHighlightMode(bool highlightMode);

    void setLengthHighlight(long lengthHighlight);

    void setStartHighlight(long startHighlight);

public slots:
    void transformChanged(const QTransform& transform);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void drawForeground(QPainter *painter, const QRectF &rect);

private:
    void clearEnabledUnits();

    void clearLastSelected();
    void setLastSelected(MemoryItem* p_mem);
    int  itemIndex(QGraphicsItem* item) const;
    void memoryStatusUpdate(const QRectF& rect = QRectF());
    bool inHighlightRange(long index) const;

private:
    int m_lastSelectedIndex;
    MemoryItem* m_lastSelected;
    MemoryWidget* m_memoryWidget;

    MemoryInteractiveUnit* m_interactiveUnit;


    QList<MemoryUnit*> m_units;
    QList<MemoryItem*> m_items;

    QMap<int , MemoryUnit*> m_unit_by_unitId;

    long m_memorySize;

    bool m_highlightMode;
    long m_startHighlight;
    long m_lengthHighlight;

    friend class MemoryInteractiveUnit;
};

#endif // MEMORYSCENE_HPP
