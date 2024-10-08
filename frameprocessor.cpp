#include "frameprocessor.h"
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <QVector>
#include <qdebug.h>

FrameProcessor::FrameProcessor(int ThreadID, bool& face_detection, bool& camera_record, cv::Mat* frame, QMutex& displayMutex, QWaitCondition& displayCondition, bool& stop_camera )
    :QThread(nullptr),
    ThreadID(ThreadID),
    face_detection(face_detection),
    camera_record(camera_record),
    frame(frame),
    displayMutex(displayMutex),
    displayCondition(displayCondition),
    stop_camera(stop_camera)
{

        // Load the pre-trained Haar Cascade XML classifier
    if (!face_cascade.load("../../haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading face cascade file!" << std::endl;
        //  return; // Return early on failure to load cascade
    }
}

void FrameProcessor::run()
{
    cv::Mat frameTemp = cv::imread("../../test.jpg"); // Use imread to load the image
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;
    cv::cvtColor(frameTemp, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);
    QElapsedTimer consumerTimer;

    while(!stop_camera){
    // Processing the frame
    // Face detection logic (same as before)
    // QMutexLocker locker(&displayMutex);

    // if(frame->empty())
    // {
    //     displayCondition.wait(&displayMutex)  ;
    // }
    // locker.unlock();

    if (face_detection) {
        consumerTimer.start(); // per frame timer


       face_cascade.detectMultiScale(frame_gray, faces);

        // for (const auto &face : faces) {
        //     cv::rectangle(frameTemp, face, cv::Scalar(255, 0, 0), 2);
        // }
       // QThread::msleep(200);
        qint64 consumerElapsed = consumerTimer.elapsed();
        qDebug()<< "Consumer Elaps Time: " << consumerElapsed << "   " << QThread::currentThreadId()  << "  " << ThreadID  ;
        consumerTimer.restart();

    }
    }
   // frame->release();
}




// // Handle camera recording
// if (camera_record) {
//     if (!writer.isOpened()) {
//         int frameWidth = static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_WIDTH));
//         int frameHeight = static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT));
//         writer = cv::VideoWriter(generateFileName(index), cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, cv::Size(frameWidth, frameHeight));

//         if (!writer.isOpened()) {
//             qWarning() << "Failed to open VideoWriter!";
//         }
//     }

//     // Use QtConcurrent::run with mutex protection
//     QtConcurrent::run([this, frame]() {
//         QMutexLocker locker(&writerMutex);
//         writer.write(frame);
//     });
// } else {
//     if (writer.isOpened()) {
//         QMutexLocker locker(&writerMutex);
//         writer.release();
//     }
// }
