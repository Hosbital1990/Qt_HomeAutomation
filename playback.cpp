#include "playback.h"
#include <opencv2/videoio.hpp>
#include    "sharedArgumant.h"
#include <QThread>

 PlayBack::PlayBack(QString *filePath, ImageWidget *imageWidget, QObject *parent)

    : QObject{parent},
    filePath(filePath) ,
    imageWidget (imageWidget),
    playBackStop(false)
{}


 void PlayBack::startPlayBack()
 {
     cv::VideoCapture videoCap(filePath->toStdString());
     if(!videoCap.isOpened())
     {
         qDebug() << "Couldnt Open Vidoe file";
     }
     cv::Mat frame;

     sharedImgWidgMtx.lock();

     while (videoCap.read(frame) && !playBackStop)
     {

         if(frame.empty())
         {
             qWarning() << "Empty frame!";
         continue;
         }

         // Convert OpenCV Mat to QImage
         QImage processedImage = MatToQImage(frame);
         imageWidget->setImage(processedImage);
         QThread::msleep(30);
     }
     sharedImgWidgMtx.unlock();

     videoCap.release();  // Release video file when done
     playBackStop=false;

 }

 QImage PlayBack::MatToQImage(const cv::Mat &mat) {
     switch (mat.type()) {
     case CV_8UC3: // RGB
         return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
     case CV_8UC4: // RGBA
         return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGBA8888);
     case CV_8UC1: // Grayscale
         return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
     default:
         qWarning() << "Unsupported cv::Mat format! Type:" << mat.type();
         return QImage(); // Return an empty QImage on unsupported type
     }
 }
 void PlayBack::stopPlayBack()
 {
     playBackStop =true;

 }

 PlayBack::~PlayBack()
 {
     delete filePath;
     delete imageWidget;
 }
