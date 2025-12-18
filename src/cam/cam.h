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
#include <QVideoWidget>
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
class cam : public QMainWindow
{
    Q_OBJECT

public:
    cam(QWidget *parent = nullptr);
    ~cam() override;

public slots:
    // void on_openbtn_clicked();
private slots:

    void save_pic(int id, const QImage &preview);

    void on_screenshotbtn_clicked();

    void on_camBackBtn_clicked();

    void on_picbtn_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void onTimeout();

    void onVideoFrameProbed(const QVideoFrame &frame);

private:
    Ui_cam *ui;
    QTimer *timer;
    QList<QCameraInfo> cameraList; // 相机列表
    QCamera *myCamera;             // 相机
    QCameraImageCapture *cp;       // 抓拍部件
    QVideoWidget *w;
    QVideoProbe *videoProbe = nullptr;
    QElapsedTimer fpsTimer;
    int fpsFrameCount = 0;
    double currentFps = 0.0;

    int default_index = 0;
    int maxIndex;

    // QWidget interface
protected:
    void sim_click(int x, int y);
    void mousePressEvent(QMouseEvent *event);
};
