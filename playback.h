#ifndef PLAYBACK_H
#define PLAYBACK_H

#include <QObject>
#include <QImage>
#include "imagewidget.h" // Include the header for ImageWidget

#include <opencv2/opencv.hpp>
class PlayBack : public QObject
{
    Q_OBJECT
public:
    explicit PlayBack(QString* filePath, ImageWidget *imageWidget, QObject *parent = nullptr);
    ~PlayBack();

    QImage MatToQImage(const cv::Mat &mat);
    void stopPlayBack();

public slots:
    void startPlayBack();

signals:

private:
    QString* filePath;
    ImageWidget *imageWidget;
    bool playBackStop;

};

#endif // PLAYBACK_H
