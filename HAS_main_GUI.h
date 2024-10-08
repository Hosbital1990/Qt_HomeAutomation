#ifndef HAS_MAIN_GUI_H
#define HAS_MAIN_GUI_H

#include <QMainWindow>
#include <QMutex>
#include <QImage>
#include <QComboBox>
#include <opencv2/opencv.hpp>
#include "imagewidget.h" // Include the header for ImageWidget
#include <QMutex>
#include "camera.h"
#include "playback.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class HAS_Main_GUI;
}
QT_END_NAMESPACE

class HAS_Main_GUI : public QMainWindow
{
    Q_OBJECT

public:
    HAS_Main_GUI(QWidget *parent = nullptr);
    ~HAS_Main_GUI();

public slots:
    void toggle_light();
    void onCameraSelected(int index);
    void openFileDialog();

private:
    Ui::HAS_Main_GUI *ui;
    int toggle_counter;

    QMutex mutex;


    QComboBox *cameraComboBox;          // Camera selection combo box

    QImage processedImage;              // Store the processed image
    ImageWidget *imageWidget;           // Custom widget for displaying images


    // Store the available camera device identifiers or names
    QStringList cameraIdentifiers;      // List of camera identifiers
    QTimer* cameraTimer;
   // QMutex mutex; // Mutex for controlling access to processFrames

    // Function to start OpenCV camera
    void startOpenCVCamera();           // Kept this in case you want to initialize OpenCV camera setup

    // Camera
    Camera* camera;
    QThread* cameraThread;
    bool face_detection ;
    bool camera_record  ;


    //recorder
    Camera* camera_recorder;
    QThread* recorderThread;

    //playBack
    PlayBack* playBack;
    QThread* playBackThread;

    //Ikcon
    QTimer* blinkTimer ;
    bool iconVisible ;  // Use a pointer to persist the state

};

#endif // HAS_MAIN_GUI_H
