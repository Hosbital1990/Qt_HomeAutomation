#ifndef CAMERA_H
#define CAMERA_H

/**
 * @brief Use namsapace for camera functions!
 * @attention consider namespace instead of creating a class due to the simplicity!
 */

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

#include <QObject>
#include "imagewidget.h" // Include the header for ImageWidget
#include <queue>

#include <condition_variable>
#include <mutex>

class Camera : public QObject
{
    Q_OBJECT

public:
    explicit Camera(int index, bool& face_detection, bool& camera_record, ImageWidget *imageWidget);
    Camera(int index);
    ~Camera();

    void processFrames(/*ImageWidget *imageWidget*/) ;
    QImage MatToQImage(const cv::Mat &mat) ;
    std::string generateFileName(int index);
    void stop();

public slots:
    //capture
    bool start_camera();

    //record



protected:



private:
    // Define a static variable for the dummy reference
    bool dummy_reference = false; // This can be any static boolean variable

    cv::VideoCapture videoCapture;
    cv::CascadeClassifier face_cascade; // Haar cascade for face detection

    ImageWidget *imageWidget;
    int index;
    bool& face_detection ;
    bool& camera_record ;
    bool stop_camera ;
    //recorder
    std::queue<cv::Mat> camera_frame_queue;
    std::condition_variable condVar;
    std::mutex queue_mutex;
    QVector<cv::Mat> frameVector;

};



#endif   // CAMERA_H
