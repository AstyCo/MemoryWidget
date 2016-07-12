#ifndef APPEVENTFILTER_HPP
#define APPEVENTFILTER_HPP

#include <QObject>

class AppEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit AppEventFilter(QObject *parent = 0);
    bool eventFilter(QObject* object,QEvent* event);
signals:

public slots:
};

#endif // APPEVENTFILTER_HPP

