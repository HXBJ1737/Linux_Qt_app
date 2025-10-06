#pragma once
#include "ui_cam.h"
#include <QMainWindow>

#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
class cam : public QMainWindow
{
    Q_OBJECT

public:
    cam(QWidget *parent = nullptr);
    ~cam();

public slots:
    void on_openbtn_clicked();
private slots:

    void save_pic(int id, const QImage &preview);

    void on_screenshotbtn_clicked();

    void on_camBackBtn_clicked();

    void on_picbtn_clicked();

private:
    Ui_cam *ui;

    QList<QCameraInfo> cameraList; // 相机列表
    QCamera *myCamera;             // 相机
    QCameraImageCapture *cp;       // 抓拍部件
    QVideoWidget *w;

    int default_index = 0;
    int maxIndex;
};
