#ifndef ASPECTRATIOWIDGET_H
#define ASPECTRATIOWIDGET_H

#include <QWidget>

class AspectRatioWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AspectRatioWidget(QWidget *parent = 0);

    void resizeEvent(QResizeEvent *);

signals:

public slots:
};

class AppEventFilter : public QObject
{
    Q_OBJECT
public:
    AppEventFilter(QObject *parent = 0);
    bool eventFilter(QObject* object,QEvent* event);
signals:

public slots:
};

#endif // ASPECTRATIOWIDGET_H
