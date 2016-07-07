#include "memorywidget.h"
#include "memoryview.h"
#include "memoryscene.h"

#include "aspectratiowidget.h"

#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QEvent>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MemoryWidget *memoryWidget = new MemoryWidget;

    MemoryScene scene;

    scene.setBackgroundBrush(QBrush(Qt::gray));
    scene.addItem(memoryWidget);

    MemoryView view(&scene);

    view.setFrameStyle(0);
    view.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

#if defined(Q_WS_S60) || defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR)
    view.showMaximized();
#else
    view.show();
#endif


    return a.exec();
}
