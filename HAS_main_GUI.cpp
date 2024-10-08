#include "HAS_main_GUI.h"
#include "./ui_HAS_main_GUI.h"
#include "imagewidget.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QComboBox>
#include <QElapsedTimer>
#include <QThread>
#include <QDir>
#include <QtConcurrent/QtConcurrent>
#include <QPixmap>
#include <QFileDialog>

HAS_Main_GUI::HAS_Main_GUI(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::HAS_Main_GUI),
    toggle_counter(0),
    face_detection(false),
    camera_record(false),
    cameraThread(nullptr),
    cameraTimer(nullptr),
    camera(nullptr),
    blinkTimer(new QTimer),
    iconVisible(false),
    playBackThread(nullptr),
    playBack(nullptr)

{
    ui->setupUi(this);
    // Timer for blinking effect


    // Setup UI components
    QPushButton *button = new QPushButton("Toggle Light", this);
    button->setMinimumHeight(40);
    connect(button, &QPushButton::clicked, this, &HAS_Main_GUI::toggle_light);

    cameraComboBox = new QComboBox(this);
    cameraComboBox->setMinimumHeight(40);
    // Initialize available cameras
    cameraIdentifiers << "Camera 0" << "Camera 2";
    cameraComboBox->addItems(cameraIdentifiers);
    cameraComboBox->setCurrentIndex(1);
    connect(cameraComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HAS_Main_GUI::onCameraSelected);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addSpacerItem(new QSpacerItem(100, 20));
    topLayout->addWidget(button);
    topLayout->addSpacerItem(new QSpacerItem(100, 20));
    topLayout->addWidget(cameraComboBox);
    topLayout->addSpacerItem(new QSpacerItem(100, 20));

    QPushButton *face_detectionButton = new QPushButton(QIcon("../../Media/Icon/face_recog_icon.png"),"Face Detection", this);
    face_detectionButton->setMinimumWidth(130);
    // Align the text to the right
    face_detectionButton->setStyleSheet("text-align: right;");

    connect(face_detectionButton, &QPushButton::clicked, this, [face_detectionButton, this](){
        this->face_detection^=true;
        qDebug()<< "Face detection boolean is: " <<face_detection ;
        qDebug()<< "camera record boolean is: " <<camera_record ;

        if (face_detection) {
            blinkTimer->start(500);  // Start blinking every 1 second
        } else {
            if(!camera_record)
            {
                blinkTimer->stop();  // Stop blinking
            }            // Ensure the icon is fully visible when stopping

            face_detectionButton->setIcon(QIcon("../../Media/Icon/face_recog_icon.png"));
        }
    });

    // Create the button and set its fixed size
    QPushButton *recordButton = new QPushButton("", nullptr);
    recordButton->setFixedSize(130, 30);  // Set desired button size

    // Load the original icon and scale it to cover the button's width
    QPixmap originalPixmap("../../Media/Icon/rec-Icon-croped.png");
    QPixmap scaledPixmap = originalPixmap.scaled(80, 22, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    recordButton->setIcon(QIcon(scaledPixmap));
    recordButton->setIconSize(scaledPixmap.size());


    // Connect button click to toggle recording and start/stop blinking
    connect(recordButton, &QPushButton::clicked, this, [recordButton,scaledPixmap, this]() {
        this->camera_record ^= true;  // Toggle recording state
        qDebug() << "Recording boolean is: " << camera_record;

        if (camera_record) {
          blinkTimer->start(500);  // Start blinking every 1 second
        } else {
            if(!face_detection)
            {
                blinkTimer->stop();  // Stop blinking
            }
            // Ensure the icon is fully visible when stopping
            recordButton->setIcon(QIcon(scaledPixmap));
            recordButton->setIconSize(scaledPixmap.size());
        }
    });





    QPushButton *snapshot_Button = new QPushButton("Snapshot", this);

    QPushButton *video_playback = new QPushButton("Playback", this);
    connect(video_playback, &QPushButton::clicked, this , &HAS_Main_GUI::openFileDialog);


    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(face_detectionButton);
    rightLayout->addWidget(recordButton);
    rightLayout->addWidget(snapshot_Button);
    rightLayout->addWidget(video_playback);

    imageWidget = new ImageWidget(this);
    imageWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *downsideLayout = new QHBoxLayout();
    downsideLayout->addWidget(imageWidget, 10);
    downsideLayout->addLayout(rightLayout, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(downsideLayout);

    ui->centralwidget->setLayout(mainLayout);

//Set Ickon Blinky Timer
    connect(blinkTimer, &QTimer::timeout, this, [recordButton,face_detectionButton,scaledPixmap,this]() {
        if (iconVisible) {
            if(camera_record)
            {
                recordButton->setIcon(QIcon(scaledPixmap));
                recordButton->setIconSize(scaledPixmap.size());
            }
            if(face_detection)
            {
                face_detectionButton->setIcon(QIcon("../../Media/Icon/face_recog_icon.png"));

            }

        } else {
            if(camera_record){
                recordButton->setIcon(QIcon());
                recordButton->setIconSize(scaledPixmap.size());
            }
            if(face_detection)
            {
                face_detectionButton->setIcon(QIcon());

            }
        }
        iconVisible ^= true;  // Toggle visibility
       // qDebug() << camera_record << "  " << face_detection ;
    });

    // Create and start a new camera thread
    camera = new Camera(cameraComboBox->currentIndex(), face_detection, camera_record, imageWidget);
    cameraThread = new QThread();
    // Move camera to the new thread
    camera->moveToThread(cameraThread);
    connect(cameraThread, &QThread::started, camera, &Camera::start_camera);
    // connect(cameraThread, &QThread::finished, cameraThread, &QObject::deleteLater);
    cameraThread->start();

}

void HAS_Main_GUI::toggle_light() {
    // Toggle light functionality
}

void HAS_Main_GUI::onCameraSelected(int index) {
    if (cameraThread) {
        // Gracefully stop the camera and thread
        camera->stop();
        cameraThread->quit();  // Gracefully request thread termination
        cameraThread->wait();  // Wait for the thread to finish

        // Clean up camera and thread using deleteLater()
       camera->deleteLater();  // Use deleteLater to ensure it is deleted after the event loop finishes
       cameraThread->deleteLater();

       cameraThread = nullptr;
        camera = nullptr;
    }
    // Create and start a new camera thread
    camera = new Camera(index, face_detection, camera_record, imageWidget);
    cameraThread = new QThread();
    // Move camera to the new thread
    camera->moveToThread(cameraThread);
    connect(cameraThread, &QThread::started, camera, &Camera::start_camera);
    cameraThread->start();

}

void HAS_Main_GUI::openFileDialog() {
    // Set the starting directory for the file dialog
    QString initialDir = "../../Media"; // Set the initial directory to your recordings folder

    // Open a file dialog to select a video file
    QString selectedFile = QFileDialog::getOpenFileName(this,
                                                        "Select Recorded Video",
                                                        initialDir,
                                                        "Video Files (*.avi *.mp4 *.mkv);;All Files (*)");

    // If the user selected a file, play it
    if (selectedFile.isEmpty()) {
        qDebug() << "Could not select file" ;
      return;
    }

          qDebug() << "File address: "<< selectedFile ;
          if (playBackThread) {
          // Gracefully stop the camera and thread
          playBack->stopPlayBack();
          playBackThread->quit();  // Gracefully request thread termination
          playBackThread->wait();  // Wait for the thread to finish

          // Clean up camera and thread using deleteLater()
          playBack->deleteLater();  // Use deleteLater to ensure it is deleted after the event loop finishes
          playBackThread->deleteLater();

          playBackThread = nullptr;
          playBack = nullptr;
      }
      // Create and start a new camera thread
      playBack = new PlayBack(&selectedFile,imageWidget);
      playBackThread = new QThread();
      // Move camera to the new thread
      playBack->moveToThread(playBackThread);
      connect(playBackThread, &QThread::started, playBack, &PlayBack::startPlayBack);
      playBackThread->start();



    }



HAS_Main_GUI::~HAS_Main_GUI() {


    if (camera) {
        camera->stop();
        delete camera;
    }

    if (cameraThread) {
        cameraThread->quit();
        cameraThread->wait();
        delete cameraThread;
    }

    // Clean up UI
    delete ui;
}
