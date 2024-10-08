#include "HAS_main_GUI.h"
#include "has_main_backend.h"
#include <QThread>
#include <QApplication>
#include "do_some_thing.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

#include "opencv2/opencv.hpp"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HAS_Main_GUI w;
    w.show();

    try
    {
        /* code */

        HAS_Main_Backend has_main_backend ("Hosbita", "*******", 891412313);
        has_main_backend.start_point();  /*<@param some case need to find! */

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }



    return a.exec();
}





// qDebug() << "Main Thread ID is: " << QThread::currentThreadId()
//          << "\n **************************************************";
// QThread::msleep(500);

// Do_Some_Thing* do_sm = new Do_Some_Thing() ;
// QObject::connect(do_sm,  &Do_Some_Thing::finished, do_sm, &Do_Some_Thing::deleteLater);
// do_sm->start();
/******************************************************************************************************************/
// QThread* do_sm_thread = new QThread();
// Do_Some_Thing* try_thread = new Do_Some_Thing;
// try_thread->moveToThread(do_sm_thread);

// QObject::connect(do_sm_thread , &QThread::started , try_thread , &Do_Some_Thing::run_independ);
// QObject::connect(do_sm_thread , &QThread::finished , do_sm_thread , &QThread::deleteLater);
// // Connect finished signal to cleanup
// QObject::connect(do_sm_thread,  &QThread::finished, try_thread, &Do_Some_Thing::deleteLater);
// do_sm_thread->start();
/******************************************************************************************************************/

// Do_Some_Thing* do_sm_concurrent = new Do_Some_Thing() ;
// QFuture<void> future= QtConcurrent::run([&](){

//     do_sm_concurrent->run_independ();
// });
//     // Optionally use QFutureWatcher to monitor the task
// QFutureWatcher<void> watcher;
// watcher.setFuture(future);
// QObject::connect(&watcher, &QFutureWatcher<void>::finished, do_sm_concurrent, &QObject::deleteLater);
/******************************************************************************************************************/

// cv::Mat image = cv::imread("../../Media/lambo.png");
// cv::imshow("Image", image);
// cv::waitKey(30);
