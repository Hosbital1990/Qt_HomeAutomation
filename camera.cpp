#include <opencv2/opencv.hpp>
#include "camera.h"

#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <opencv2/objdetect.hpp> // For face detection
#include "sharedArgumant.h"
#include <QThreadPool>


Camera::Camera(int index, bool& face_detection, bool& camera_record, ImageWidget *imageWidget)
    : index(index),
    face_detection(face_detection),
    camera_record(camera_record),
    imageWidget(imageWidget),
    stop_camera(false)
{

    // Load the pre-trained Haar Cascade XML classifier
    if (!face_cascade.load("../../haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading face cascade file!" << std::endl;
        return; // Return early on failure to load cascade
    }

}

Camera::Camera(int index)
    :index(index),
    face_detection(dummy_reference), // Use a dummy reference
    camera_record(dummy_reference), // Use a dummy reference
    imageWidget(nullptr),
    stop_camera(false)
{

}

bool Camera::start_camera()
{
    if (videoCapture.isOpened()) {
        // Optionally release the previous camera if already opened
        videoCapture.release();
    }

    if (index >= 0) {
        int cameraIndex = 2 * index; // Adjust this as per your camera setup
        videoCapture.open(cameraIndex);
        if (!videoCapture.isOpened()) {
            qWarning() << "Failed to open camera!";
            return false; // Ensure the function returns false on failure
        }

        this->processFrames();
        return true; // Return true after successful camera start
    } else {
        qWarning() << "Invalid camera index.";
        return false; // Return false for an invalid camera index
    }
}

void Camera::processFrames() {


    cv::VideoWriter writer;
    QFuture<void> concurrentFuture;
    int readSequenceNumber=0;
    int nextFrameToDisplay=0;
    int sameFrameCounter = 0;
    cv::Mat previousFrame;
    const int scale = 3;  // Scale down factor

    while (videoCapture.isOpened() && !stop_camera) {
        cv::Mat frame;
        videoCapture.read(frame);

        if (frame.empty()) {
            qWarning() << "Empty frame!";
            continue;
        }


        if (face_detection) {
            // Face detection
            std::vector<cv::Rect> faces;
            cv::Mat frame_gray;

            // Convert frame to grayscale
            cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
            cv::equalizeHist(frame_gray, frame_gray);

            // Scale factor for resizing the image
            const int scale = 3;

            // Create a resized grayscale image
            cv::Mat resized_frame_gray(cvRound(frame_gray.rows / scale), cvRound(frame_gray.cols / scale), CV_8UC1);

            // Resize the grayscale image to reduce its size by the scale factor
            cv::resize(frame_gray, resized_frame_gray, resized_frame_gray.size());

            // Start a timer for performance measurement
            QElapsedTimer timer;
            timer.start();

            // Perform face detection on the scaled-down image
            face_cascade.detectMultiScale(resized_frame_gray, faces, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(20, 20));

            // Measure the frame processing time
            qint64 elapsed = timer.elapsed();
            qDebug() << "Frame processing time: " << elapsed << " ms";

            // Merge conversion and drawing into a single loop
            for (const auto &face : faces) {
                // Convert detected face positions back to original scale and draw rectangles
                cv::Rect scaled_face(face.x * scale, face.y * scale, face.width * scale, face.height * scale);
                cv::rectangle(frame, scaled_face, cv::Scalar(255, 0, 0), 2);
            }
        }



        if(camera_record){
            if(writer.isOpened())
            {            //record camera
                QtConcurrent::run([&frame, &writer](){

                    writer.write(frame);
                });
            } else if(!writer.isOpened())
            {
                QtConcurrent::run([&frame, &writer, this](){
                    int frameWidth = static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_WIDTH));
                    int frameHeight = static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT));
                    writer = cv::VideoWriter(generateFileName(index), cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, cv::Size(frameWidth, frameHeight));
                    qDebug()<< "cv::VideoWriter writer is: " << writer.isOpened();
                    //Write to file
                    writer.write(frame);
                });
            }
        } else if (writer.isOpened())
        {
            writer.release();
        }


        // Update the image on the widget
        if (sharedImgWidgMtx.tryLock() )
        {
            // Convert OpenCV Mat to QImage
            QImage processedImage = MatToQImage(frame);

            // Display the processed image in the Qt widget
            imageWidget->setImage(processedImage);


            sharedImgWidgMtx.unlock();
        }

        // Update previousFrame for the next iteration
        previousFrame = frame.clone();


      //  QThread::msleep(100);  // Sleep briefly to avoid busy-waiting


    }
    stop_camera = false;
    qDebug() << "--------------------------------->>>Leave ProcessFrames";

}

QImage Camera::MatToQImage(const cv::Mat &mat) {
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


//This function create a name for saving video based on the system time and date
std::string Camera::generateFileName(int index){

    std::time_t now = std::time(nullptr);
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d_%H-%M-%S", std::localtime(&now));
    std::string filename = "";
    // Create the filename

    if(index == 0){

        filename = "../../Media/camera00_record/"+ std::string(buffer) + ".avi";

    }
    else if(index == 1){

        filename = "../../Media/camera02_record/"+ std::string(buffer) + ".avi";

    }

    return filename;
}

void Camera::stop()
{
    stop_camera = true;
    if (videoCapture.isOpened()) {
        videoCapture.release(); // Release the camera properly
    }
}



Camera::~Camera() {
    if (videoCapture.isOpened()) {
        videoCapture.release();
    }
    if (imageWidget) {
        delete imageWidget;
    }
}




// void Camera::saveCameraFrame()
// {

//     int frameWidth = static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_WIDTH));
//     int frameHeight = static_cast<int>(videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT));

//     cv::VideoWriter writer(generateFileName(index), cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, cv::Size(frameWidth, frameHeight));
//     qDebug()<< "VideoCapture is Open: " << videoCapture.isOpened();
//     cv::Mat frame ;
//     while (!stop_camera) {

//         std::unique_lock<std::mutex> lock(queue_mutex);
//         // Wait for a new frame to be produced or stop flag to be set
//         qDebug()<< "Camera Frame Queue Empty: " << this->camera_frame_queue.empty();

//         condVar.wait(lock, [this]() {
//             return !this->camera_frame_queue.empty() ;
//         });

//         if (!camera_frame_queue.empty()) {
//             frame = camera_frame_queue.front();
//             camera_frame_queue.pop();
//             lock.unlock();

//             writer.write(frame);

//             std::cout << "camera 0" <<index << " saved a frame.\n";
//             // cv::imwrite("output.jpg", frame);  // Save frame to disk, if needed

//         } else if (stop_camera) {
//             break;  // Exit if the stop flag is set
//         }

//     }

// }
