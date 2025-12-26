#ifndef YOLO_APP_H
#define YOLO_APP_H

#include <QMainWindow>
#include <QVideoProbe>
#include <QCamera>
#include <QLabel>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVideoFrame>
#include <QAbstractVideoBuffer>
#include <QImage>
#include <QTimer>
#include <QElapsedTimer>
#include <QVideoWidget>   // ? 你用了 QVideoWidget*，需要这个

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>       // ? malloc/free
#include <string.h>       // ? memset/memcpy

#ifdef __linux__
#include "yolo11.h"       // for rknn_app_context_t
#include "image_utils.h"
#include "file_utils.h"
#include "image_drawing.h"
#include <opencv2/opencv.hpp>
#endif

namespace Ui {
class yolo_app;
}

class yolo_app : public QMainWindow
{
    Q_OBJECT

public:
    explicit yolo_app(QWidget *parent = nullptr);
    ~yolo_app();

private slots:
    void on_back_btn_clicked();

#ifdef __linux__
    void processFrame(const QVideoFrame &frame);
    void on_comboBox_currentIndexChanged(int index);   // ? 真正声明在这里（单独一行）
#endif

private:
    Ui::yolo_app *ui;

    QList<QCameraInfo> cameraList; // 相机列表
    QCamera *myCamera = nullptr;   // 相机
    QVideoWidget *w = nullptr;

    QVideoProbe *probe = nullptr;    // 接收每帧
    QLabel *displayLabel = nullptr;  // 显示处理后的帧

#ifdef __linux__
    rknn_app_context_t rknn_app_ctx; // 模型上下文
    bool convertNV12ToImageBufferSimple(QVideoFrame &frame, image_buffer_t *image_buf);
#endif

    int m_index = 0;
    int maxIndex = 0;
};

#endif // YOLO_APP_H
