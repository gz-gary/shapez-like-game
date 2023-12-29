#include "Timer/Timer.h"

Timer::Timer(QObject *parent, int _timeout) : QObject(parent), timeout(_timeout)
{
    qtimer = new QTimer(this);
    connect(qtimer, SIGNAL(timeout()), this, SLOT(slot_internalTimeout()));
}

void Timer::start()
{
    qtimer->start(timeout);
}

void Timer::stop() {
    qtimer->stop();
}

void Timer::slot_internalTimeout()
{
    emit signal_externalTimeout();
}
