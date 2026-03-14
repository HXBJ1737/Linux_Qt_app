#ifdef __aarch64__
#include "yolo_app.h"
#include "ui_yolo_app.h"

yolo_app::yolo_app(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::yolo_app)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);


    const char *model_path = "/hxbj/model/yolo11_relu.rknn";
    int ret;

    memset(&rknn_app_ctx, 0, sizeof(rknn_app_context_t));

    init_post_process();

    ret = init_yolo11_model(model_path, &rknn_app_ctx);
    if (ret != 0)
    {
        printf("init_yolo11_model fail! ret=%d model_path=%s\n", ret, model_path);
    }
    else
    {
        printf("success yolo11");
    }
    /*----------------------------------------------*/
    cameraList = QCameraInfo::availableCameras();

    if (cameraList.count() > 0)
    {

        foreach (QCameraInfo info, cameraList)
        {
            // 人能读懂的设备名字
            qDebug() << info.description();
            qDebug() << info.deviceName();
            // ui->camlist->addItem(info.deviceName());
        }
    }
    //----
    myCamera = new QCamera(cameraList[0], this); // camera指向指定的摄像头
    // 设置默认摄像头参数
    QCameraViewfinderSettings set;
    set.setResolution(640, 480);
    myCamera->setViewfinderSettings(set);
    myCamera->start(); // 启动
                       // displayLabel 用来显示处理后带框的图像
    displayLabel = new QLabel(ui->widget);
    displayLabel->setGeometry(ui->widget->rect());
    displayLabel->setScaledContents(true);
    displayLabel->show();

    // 使用 QVideoProbe 接收每一帧进行推理
    probe = new QVideoProbe(this);
    if (probe->setSource(myCamera))
    {
        connect(probe, &QVideoProbe::videoFrameProbed, this, &yolo_app::processFrame);
    }
    else
    {
        qDebug() << "QVideoProbe setSource failed";
    }

}

yolo_app::~yolo_app()
{
    deinit_post_process();

    int ret = release_yolo11_model(&rknn_app_ctx);
    if (ret != 0)
    {
        printf("release_yolo11_model fail! ret=%d\n", ret);
    }
    delete ui;
}

void yolo_app::on_back_btn_clicked()
{
    // 先断开并删除 probe，避免在释放 camera 时还触发回调
    if (probe)
    {
        probe->disconnect(this);
        delete probe;
        probe = nullptr;
    }

    // 停止并删除摄像头
    if (myCamera)
    {
        myCamera->stop();
        delete myCamera;
        myCamera = nullptr;
    }

    // 释放显示控件
    if (displayLabel)
    {
        displayLabel->clear();
        delete displayLabel;
        displayLabel = nullptr;
    }

    // 提前释放推理相关资源
    deinit_post_process();
    int ret = release_yolo11_model(&rknn_app_ctx);
    if (ret != 0)
    {
        qDebug() << "release_yolo11_model fail! ret=" << ret;
    }

    this->close();
}
void yolo_app::processFrame(const QVideoFrame &frame)
{
    static int fpsFrameCount = 0;
    static QElapsedTimer fpsTimer;
    static double currentFps = 0.0;
    if (!fpsTimer.isValid())
        fpsTimer.start();
    fpsFrameCount++;
    qint64 elapsed = fpsTimer.elapsed();
    if (elapsed >= 1000)
    {
        currentFps = fpsFrameCount * 1000.0 / (double)elapsed;
        fpsFrameCount = 0;
        fpsTimer.restart();
        if (ui && ui->label_fps)
        {
            ui->label_fps->setText(QString("FPS: %1").arg(QString::number(currentFps, 'f', 1)));
        }
    }

    if (!frame.isValid())
        return;

    // QVideoProbe 传入的是 const QVideoFrame &，但是 convertNV12ToImageBufferSimple 需要非 const
    QVideoFrame f(frame);

    // 把 QVideoFrame 转为 image_buffer_t（NV12）
    image_buffer_t src;
    memset(&src, 0, sizeof(image_buffer_t));
    if (!convertNV12ToImageBufferSimple(f, &src))
    {
        return;
    }
    rotateNV12Frame180(&src);
    // 推理
    object_detect_result_list od_results;
    memset(&od_results, 0, sizeof(od_results));
    int ret = inference_yolo11_model(&rknn_app_ctx, &src, &od_results);
    if (ret != 0)
    {
        // 推理失败，释放缓冲并返回
        if (src.virt_addr)
        {
            free(src.virt_addr);
            src.virt_addr = NULL;
        }
        return;
    }

    // 在 NV12 缓冲上画框（draw_* 函数需支持 YUV420SP 或内部进行转换）
    // 根据分辨率自适应线宽和字体
    int baseW = src.width > 0 ? src.width : 640;
    int baseH = src.height > 0 ? src.height : 480;
    int scaleW = baseW / 320;
    int scaleH = baseH / 240;
    int box_thickness = qMax(2, scaleW);
    int font_size = qMax(8, 6 * scaleH);
    char text[256];
    QMap<QString, int> labelCount;
    for (int i = 0; i < od_results.count; i++)
    {
        object_detect_result *det = &od_results.results[i];
        int x1 = det->box.left;
        int y1 = det->box.top;
        int x2 = det->box.right;
        int y2 = det->box.bottom;

        draw_rectangle(&src, x1, y1, x2 - x1, y2 - y1, COLOR_BLUE, box_thickness);
        snprintf(text, sizeof(text), "%s %.0f%%", coco_cls_to_name(det->cls_id), det->prop * 100);
        draw_text(&src, text, x1, y1 - 20 * scaleH, COLOR_RED, font_size);
        QString label = QString::fromUtf8(coco_cls_to_name(det->cls_id));
        labelCount[label]++;
    }
    if (ui && ui->label_info)
    {
        if (labelCount.isEmpty())
        {
            ui->label_info->setText("无检测目标");
        }
        else
        {
            QStringList lines;
            for (auto it = labelCount.constBegin(); it != labelCount.constEnd(); ++it)
            {
                lines << QString("%1 %2").arg(it.key()).arg(it.value());
            }
            ui->label_info->setText(lines.join("\n"));
        }
    }

    // NV12 -> RGB 转换并显示（使用 OpenCV）
    // src.virt_addr 已包含连续 NV12 数据：Y plane (H*stride) + UV plane (H/2*stride)
    int w = src.width;
    int h = src.height;
    // 构造单通道 Mat，高度为 h + h/2
    cv::Mat yuv(h + h / 2, w, CV_8UC1, src.virt_addr);
    cv::Mat rgb;
    cv::cvtColor(yuv, rgb, cv::COLOR_YUV2RGB_NV12);

    QImage img((const uchar *)rgb.data, rgb.cols, rgb.rows, static_cast<int>(rgb.step), QImage::Format_RGB888);
    displayLabel->setPixmap(QPixmap::fromImage(img.copy()));

    // 释放 image_buffer_t 中分配的内存
    if (src.virt_addr)
    {
        free(src.virt_addr);
        src.virt_addr = NULL;
        src.size = 0;
    }
}

bool yolo_app::convertNV12ToImageBufferSimple(QVideoFrame &frame, image_buffer_t *image_buf)
{
    if (!frame.isValid() || !image_buf)
    {
        return false;
    }

    if (!frame.map(QAbstractVideoBuffer::ReadOnly))
    {
        return false;
    }

    if (frame.pixelFormat() != QVideoFrame::Format_NV12)
    {
        frame.unmap();
        return false;
    }

    int width = frame.width();
    int height = frame.height();
    int stride = frame.bytesPerLine();

    // 设置图像缓冲区
    image_buf->width = width;
    image_buf->height = height;
    image_buf->width_stride = stride;
    image_buf->height_stride = height;
    image_buf->format = IMAGE_FORMAT_YUV420SP_NV12;

    // 计算大小
    int ySize = height * stride;
    int uvSize = (height / 2) * stride;
    image_buf->size = ySize + uvSize;

    // 分配内存
    if (!image_buf->virt_addr || image_buf->size != (ySize + uvSize))
    {
        if (image_buf->virt_addr)
        {
            free(image_buf->virt_addr);
        }
        image_buf->virt_addr = (unsigned char *)malloc(image_buf->size);
        if (!image_buf->virt_addr)
        {
            frame.unmap();
            return false;
        }
    }

    const uchar *src = frame.bits();
    uchar *dst = image_buf->virt_addr;

    // 复制Y平面
    if (stride == width)
    {
        // 无padding，直接复制
        memcpy(dst, src, ySize);
        src += ySize;
        dst += ySize;

        // 复制UV平面
        memcpy(dst, src, uvSize);
    }
    else
    {
        // 有padding，逐行复制
        // Y平面
        for (int y = 0; y < height; y++)
        {
            memcpy(dst + y * width, src + y * stride, width);
        }

        // UV平面
        dst += ySize;
        src += ySize;
        int uvWidth = width; // UV交错，每行width字节

        for (int y = 0; y < height / 2; y++)
        {
            memcpy(dst + y * uvWidth, src + y * stride, uvWidth);
        }
    }

    frame.unmap();
    return true;
}
void yolo_app::rotateNV12Frame180(image_buffer_t *image_buf)
{
    if (!image_buf || !image_buf->virt_addr || image_buf->width <= 0 || image_buf->height <= 0)
    {
        return;
    }

    const int width = image_buf->width;
    const int height = image_buf->height;
    unsigned char *yPlane = image_buf->virt_addr;
    const int uvPlaneOffset = image_buf->width_stride * image_buf->height_stride;
    const int uvPlaneSize = width * height / 2;
    if (uvPlaneOffset + uvPlaneSize > image_buf->size)
    {
        return;
    }
    unsigned char *uvPlane = image_buf->virt_addr + uvPlaneOffset;

    cv::Mat yMat(height, width, CV_8UC1, yPlane);
    cv::flip(yMat, yMat, -1);

    if (width % 2 != 0 || height % 2 != 0)
    {
        return;
    }

    cv::Mat uvMat(height / 2, width / 2, CV_8UC2, uvPlane);
    cv::flip(uvMat, uvMat, -1);
}
void yolo_app::on_comboBox_currentIndexChanged(int index)
{
    if (!myCamera)
        return;

    QSize desired;
    if (index == 0)
        desired = QSize(640, 480);
    else if (index == 1)
        desired = QSize(960, 720);
    else if (index == 2)
        desired = QSize(1280, 960);
    else if (index == 3)
        desired = QSize(1920, 1440);
    else if (index == 4)
        desired = QSize(2592, 1944);
    else
        return;

    // 设置摄像头分辨率
    QCameraViewfinderSettings set;
    set.setResolution(desired);
    myCamera->stop();
    myCamera->setViewfinderSettings(set);
    myCamera->start();

    qDebug() << "Camera resolution changed to" << desired;

}

#endif
