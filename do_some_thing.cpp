#include "do_some_thing.h"
#include    <QDebug>
#include <QThread>
Do_Some_Thing::Do_Some_Thing() {}

void Do_Some_Thing::run()
{
    int counter = 10;
    while (counter) {

        qDebug() << " Current thread ID" << QThread::currentThreadId() ;
        QThread::msleep(1000);
        counter -=1;
    }

}

void Do_Some_Thing::run_independ()
{
    int counter = 10;
    while (counter) {

        qDebug() << " Current thread ID" << QThread::currentThreadId() ;
        QThread::msleep(1000);
        counter -=1;
    }
}
