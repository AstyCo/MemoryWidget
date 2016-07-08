#include "memorywidget.h"
#include "memoryview.h"
#include "memoryscene.h"

#include "appeventfilter.h"

#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QEvent>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    a.installEventFilter(new AppEventFilter);

    MemoryWidget *memoryWidget = new MemoryWidget;
    QGraphicsScene scene;

    scene.setBackgroundBrush(QBrush(Qt::gray));
    scene.addItem(memoryWidget);

    MemoryView view(&scene);
    view.setMaximumSize(1920,1680);
    view.move(0,0);

    memoryWidget->adjustSize();
    view.adjustSize();
    qDebug()<<view.size();
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
