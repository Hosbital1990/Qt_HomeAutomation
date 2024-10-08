#ifndef DO_SOME_THING_H
#define DO_SOME_THING_H

#include    <QThread>
class Do_Some_Thing : public QThread
{
public:
    Do_Some_Thing();
    void run() override;
    void run_independ();
};

#endif // DO_SOME_THING_H
