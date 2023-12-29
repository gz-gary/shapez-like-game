#ifndef __TIMER_H__
#define __TIMER_H__

#include "common.h"
#include <QTimer>

class Timer : public QObject
{
    Q_OBJECT;

private:
    int timeout;
    QTimer *qtimer;

public:
    explicit Timer(QObject *parent = nullptr, int _timeout = 1000);
    void start();
    void stop();

public slots:
    void slot_internalTimeout();

signals:
    void signal_externalTimeout();
};

#endif
