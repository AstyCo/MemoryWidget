#ifndef MEMORYSCENE_H
#define MEMORYSCENE_H

#include "memoryitem.h"

#include <QGraphicsScene>
#include <QList>



class MemoryScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MemoryScene( QObject * parent = 0 );
    ~MemoryScene();

public slots:
//    void onSelectionChanged();
    void onChanged();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);


signals:


private:

    void clearLastSelected();
    void setLastSelected(MemoryItem* p_mem);

    int itemIndex(QGraphicsItem* item) const;

//    void uniqueSelection();
//    QGraphicsItem const *findFirst(QList<QGraphicsItem*> const*list,
//                             QGraphicsItem const *first, QGraphicsItem const *second) const;

    int m_lastSize;

    int m_lastSelectedIndex;
    MemoryItem* m_lastSelected;
};

#endif // MEMORYSCENE_H
