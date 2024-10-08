#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter> // Include QPainter here

class ImageWidget : public QWidget {
    QImage image;

public:
    ImageWidget(QWidget *parent) : QWidget(parent) {
      //  setAttribute(Qt::WA_OpaquePaintEvent);
    }

    void setImage(const QImage &img) {
        image = img;
        update(); // Schedule a repaint
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        if (!image.isNull()) {
            painter.drawImage(0, 0, image);
        }
    }
};

#endif // IMAGEWIDGET_H
