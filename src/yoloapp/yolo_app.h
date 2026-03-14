#ifndef YOLO_APP_H
#define YOLO_APP_H
#ifdef __aarch64__
#include <QMainWindow>
#include <QVideoProbe>
#include <QCamera>
#include <QLabel>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QVideoFrame>
#include <QAbstractVideoBuffer>
#include <QImage>
#include <QTimer>
#include <QElapsedTimer>
#include <QMessageBox>

#include "yolo11.h" // for rknn_app_context_t
#include "image_utils.h"
#include "file_utils.h"
#include "image_drawing.h"
#include <opencv2/opencv.hpp>

namespace Ui
{
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

    void processFrame(const QVideoFrame &frame); // 新增槽
    void on_comboBox_currentIndexChanged(int index);




private:
    Ui::yolo_app *ui;
    QList<QCameraInfo> cameraList; // 相机列表
    QCamera *myCamera;             // 相机
    QVideoWidget *w;

    QVideoProbe *probe;   // 用来接收每帧
    QLabel *displayLabel; // 显示处理后帧

    rknn_app_context_t rknn_app_ctx; // 模型上下文移到成员，保持可用性 
    bool convertNV12ToImageBufferSimple(QVideoFrame &frame, image_buffer_t *image_buf);
    void rotateNV12Frame180(image_buffer_t *image_buf);
    int m_index = 0;
    int maxIndex;

   
};
#endif
#endif // YOLO_APP_H
