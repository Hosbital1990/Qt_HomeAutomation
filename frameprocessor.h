#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H
#include <QThread>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <QMutex>
#include <QWaitCondition>
class FrameProcessor : public QThread
{
    Q_OBJECT;
public:
    FrameProcessor(int ThreadID, bool& face_detection, bool& camera_record, cv::Mat* frame, QMutex& displayMutex, QWaitCondition& displayCondition, bool& stop_camera );

    void run() override;

private:
    cv::CascadeClassifier face_cascade; // Haar cascade for face detection


    bool& face_detection ;
    bool& camera_record ;
    bool& stop_camera ;
    QMutex writerMutex;
    cv::VideoWriter writer;

    QQueue<cv::Mat>* tempProducerQueue ;

    //frame proces timer
    QElapsedTimer timer;
    qint64 elapsed;
    cv::Mat* frame ;
    int ThreadID;
    QMutex& displayMutex;
    QWaitCondition& displayCondition;
};

#endif // FRAMEPROCESSOR_H
