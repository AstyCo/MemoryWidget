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
    void onSelectionChanged();
    void onChanged();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


signals:


private:
    void uniqueSelection();
    QGraphicsItem const *findFirst(QList<QGraphicsItem*> const*list,
                             QGraphicsItem const *first, QGraphicsItem const *second) const;

    int lastSize;

    MemoryItem* lastSelected;
    QList<MemoryItem*> lastSelection;

};

#endif // MEMORYSCENE_H
