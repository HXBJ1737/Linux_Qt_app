#pragma once
#include "ui_cam.h"
#include <QMainWindow>
#include <QDir>
#include <QCameraInfo>
#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinderSettings>
#include <QImageEncoderSettings>
#include <QMultimedia>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDateTime>
#include <QUuid>
#include <QTimer>
#include <QMouseEvent>
#include <QApplication>
#include <QImageReader>
#include <QRegExp>
#include <QSet>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QVideoProbe>
#include <QElapsedTimer>
#include <QVideoFrame>
#include <QResizeEvent>
#include <QFrame>
#include <QPointF>
#include <QRectF>
#include <QBrush>
#include <QTransform>
class cam : public QMainWindow
{
    Q_OBJECT

public:
    cam(QWidget *parent = nullptr);
    ~cam() override;

public slots:

private slots:

    void save_pic(int id, const QImage &preview);

    void on_screenshotbtn_clicked();

    void on_camBackBtn_clicked();

    void on_picbtn_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void onTimeout();

    void onVideoFrameProbed(const QVideoFrame &frame);

    void resizeEvent(QResizeEvent *event) override;

private:
    Ui_cam *ui;
    QTimer *timer;
    QList<QCameraInfo> cameraList; // 相机列表
    QCamera *myCamera;             // 相机
    QCameraImageCapture *cp;       // 抓拍部件
    QVideoProbe *videoProbe = nullptr;
    QElapsedTimer fpsTimer;
    int fpsFrameCount = 0;
    double currentFps = 0.0;

    QGraphicsView *videoView = nullptr;
    QGraphicsScene *videoScene = nullptr;
    QGraphicsVideoItem *videoItem = nullptr;
    bool rotateViewfinder180 = false;

    void initCameraViewfinder();
    void updateViewfinderGeometry();
    void applyCameraRotation(bool rotate180Degrees);

    int default_index = 0;
    int maxIndex;

protected:
    void mousePressEvent(QMouseEvent *event);
};