// #ifdef __aarch64__
#include "distance.h"
#include "ui_distance.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QEvent>
#include <QRegularExpression>
#include <QByteArray>
#include <QFile>
#include <QDebug>
#include <QProcess>
#include <QDateTime>
#include <QMutexLocker>
#include <QMetaObject>
#include <QDir>
#include <QPixmap>
#include <QStringList>
#include <QSaveFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <cmath>
namespace
{
    constexpr const char kCpuFreqSysfsPath[] = "/sys/devices/system/cpu/cpufreq/policy0/scaling_setspeed";

    constexpr const char kNpuFreqSysfsPath[] = "/sys/class/devfreq/fde40000.npu/userspace/set_freq";
    constexpr const char kGpuFreqSysfsPath[] = "/sys/class/devfreq/fde60000.gpu/userspace/set_freq";
    constexpr const char kCpuTempSysfsPath[] = "/sys/class/thermal/thermal_zone0/temp";
    constexpr const char kGpuTempSysfsPath[] = "/sys/class/thermal/thermal_zone1/temp";
    constexpr const char kNpuLoadSysfsPath[] = "/sys/kernel/debug/rknpu/load";
    constexpr const char kDdrLoadSysfsPath[] = "/sys/devices/platform/dmc/devfreq/dmc/load";

    QString formatLoadPercentage(const QString &raw)
    {
        const QString trimmed = raw.trimmed();
        if (trimmed.isEmpty())
        {
            return trimmed;
        }

        if (trimmed.contains('%'))
        {
            return trimmed;
        }

        static const QRegularExpression numberPattern(QStringLiteral("(\\d+(?:\\.\\d+)?)"));
        const QRegularExpressionMatch match = numberPattern.match(trimmed);
        if (match.hasMatch())
        {
            return QStringLiteral("%1%").arg(match.captured(1));
        }

        return trimmed;
    }

    bool extractCpuLine(const QString &topOutput, QString &cpuLine)
    {
        const QStringList lines = topOutput.split('\n', Qt::SkipEmptyParts);
        for (const QString &line : lines)
        {
            const QString trimmed = line.trimmed();
            if (trimmed.isEmpty())
            {
                continue;
            }

            if (trimmed.contains(QStringLiteral("CPU"), Qt::CaseInsensitive) &&
                !trimmed.startsWith(QStringLiteral("Mem"), Qt::CaseInsensitive))
            {
                cpuLine = trimmed;
                return true;
            }
        }

        if (!lines.isEmpty())
        {
            const QString fallback = lines.first().trimmed();
            if (!fallback.isEmpty())
            {
                cpuLine = fallback;
                return true;
            }
        }

        return false;
    }

}

distance *distance::s_logReceiver = nullptr;
QtMessageHandler distance::s_prevHandler = nullptr;
QMutex distance::s_logMutex;

distance::distance(QWidget *parent)
    : QWidget(parent), ui(new Ui::distance)
{
    ui->setupUi(this);
    {
        QMutexLocker locker(&s_logMutex);
        if (!s_logReceiver)
        {
            s_logReceiver = this;
            s_prevHandler = qInstallMessageHandler(distance::qtLogProxy);
        }
    }
    logBuffer.clear();
    lastLabelInfoEntry.clear();
    setWindowFlags(Qt::FramelessWindowHint);
    QByteArray ba = qgetenv("PROJECT_ROOT");
    QString projectRoot = ba.isEmpty() ? QString() : QString::fromUtf8(ba);
    QDir::setCurrent(projectRoot);
    setupResourceMonitor();
    useCalibratedFocal = false;
    focalConfigLoaded = loadFocalConfigFromFile();
    currentResolution = QSize(640, 480);
    updateFocalParamsForResolution(currentResolution);
    if (ui->flip_btn)
    {
        ui->flip_btn->setEnabled(true);
    }
    if (ui->filterBtn)
    {
        ui->filterBtn->setEnabled(false);
    }
    if (ui->show1Btn)
    {
        ui->show1Btn->setText(tr("显示十字线"));
    }

    if (ui->lineEdit_1)
    {
        syncPriorSizeToLineEdit();
        activeLineEdit = ui->lineEdit_1;
    }
    else if (ui->lineEdit_2)
    {
        activeLineEdit = ui->lineEdit_2;
    }

    if (ui->lineEdit_2)
    {
        syncCameraHeightToLineEdit();
    }

    // 为 lineEdit_1 安装事件过滤器以禁用键盘输入
    keyboardFilter = new VirtualKeyboardFilter(this);
    if (ui->lineEdit_1)
    {
        ui->lineEdit_1->installEventFilter(keyboardFilter);
        ui->lineEdit_1->setFocusPolicy(Qt::StrongFocus);
        connect(ui->lineEdit_1, &QLineEdit::textEdited, this, [this]()
                {
                    // lineEdit_1 获得焦点时显示虚拟键盘
                });
    }

    if (ui->lineEdit_2)
    {
        ui->lineEdit_2->installEventFilter(keyboardFilter);
        ui->lineEdit_2->setFocusPolicy(Qt::StrongFocus);
    }

    if (ui->back_btn_3)
    {
        ui->back_btn_3->setEnabled(false);
    }
    if (ui->label_info)
    {
        ui->label_info->setWordWrap(true);
        ui->label_info->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        const int lineHeight = ui->label_info->fontMetrics().lineSpacing();
        ui->label_info->setMinimumHeight(lineHeight * kVisibleLogLines);
    }
    updateLabelInfoText(tr("检测未开始"), true);
    if (ui->label_fps)
    {
        ui->label_fps->setText("FPS: 0");
    }
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
            qDebug() << info.description();
            qDebug() << info.deviceName();
        }
    }
    //----
    if (cameraList.isEmpty())
    {
        QMessageBox::warning(this, tr("摄像头不可用"), tr("未检测到可用摄像头"));
        if (ui->back_btn_2)
        {
            ui->back_btn_2->setEnabled(false);
        }
        if (ui->back_btn_3)
        {
            ui->back_btn_3->setEnabled(false);
        }
        return;
    }

    myCamera = new QCamera(cameraList[0], this);
    QCameraViewfinderSettings set;
    set.setResolution(640, 480);
    myCamera->setViewfinderSettings(set);

    displayLabel = new QLabel(ui->widget);
    displayLabel->setGeometry(ui->widget->rect());
    displayLabel->setScaledContents(true);
    displayLabel->hide();

    // 使用 QVideoProbe 接收每一帧进行推理
    probe = new QVideoProbe(this);
    if (probe->setSource(myCamera))
    {
        connect(probe, &QVideoProbe::videoFrameProbed, this, &distance::processFrame, Qt::UniqueConnection);
    }
    else
    {
        QMessageBox::warning(this, tr("初始化失败"), tr("视频帧捕获模块初始化失败"));
        delete probe;
        probe = nullptr;
    }
}

distance::~distance()
{
    teardownResourceMonitor();
    releaseCameraResources();
    deinit_post_process();

    int ret = release_yolo11_model(&rknn_app_ctx);
    if (ret != 0)
    {
        printf("release_yolo11_model fail! ret=%d\n", ret);
    }
    {
        QMutexLocker locker(&s_logMutex);
        if (s_logReceiver == this)
        {
            qInstallMessageHandler(s_prevHandler);
            s_prevHandler = nullptr;
            s_logReceiver = nullptr;
        }
    }
    delete ui;
}

void distance::on_back_btn_clicked()
{
    releaseCameraResources();
    // 提前释放推理相关资源
    deinit_post_process();
    int ret = release_yolo11_model(&rknn_app_ctx);
    if (ret != 0)
    {
        qDebug() << "release_yolo11_model fail! ret=" << ret;
    }

    this->close();
}

void distance::on_back_btn_2_clicked()
{
    startDetection();
}

void distance::on_back_btn_3_clicked()
{
    stopDetection();
}

void distance::processFrame(const QVideoFrame &frame)
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
        lastTargetHeightPx = 0;
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
    QMap<QString, int> labelCount;
    QString targetLabel;
    bool enableFilter = false;
    if (ui && ui->comboBox_2)
    {
        targetLabel = ui->comboBox_2->currentText().trimmed();
        enableFilter = !targetLabel.isEmpty();
    }
    bool useCameraPrior = false;
    if (ui && ui->comboBox_4)
    {
        const QString modeText = ui->comboBox_4->currentText().trimmed();
        useCameraPrior = (modeText == QStringLiteral("相机先验"));
    }

    int frameTargetHeightPx = 0;
    int detectionCount = 0;
    double lastDistanceMeters = 0.0;
    bool hasValidDistance = false;
    double lastCamHeightOverTanAlphaMm = 0.0;
    bool hasCamHeightOverTanAlpha = false;
    double singleTargetDistanceMeters = 0.0;
    for (int i = 0; i < od_results.count; i++)
    {
        object_detect_result *det = &od_results.results[i];
        QString label = QString::fromUtf8(coco_cls_to_name(det->cls_id));
        if (enableFilter && label.compare(targetLabel, Qt::CaseInsensitive) != 0)
        {
            continue;
        }
        detectionCount++;
        int x1 = det->box.left;
        int y1 = det->box.top;
        int x2 = det->box.right;
        int y2 = det->box.bottom;
        const int targetHeightPx = getTargetHeightPx(*det);
        frameTargetHeightPx = qMax(frameTargetHeightPx, targetHeightPx);

        const double frameHalfHeight = static_cast<double>(baseH) * 0.5;
        const double deltaY = static_cast<double>(y2) - frameHalfHeight;
        const double alpha = (hx_f > 0.0) ? std::atan(deltaY / hx_f) : 0.0;

        QString distanceOverlay = QStringLiteral("--");
        bool currentDistanceValid = false;
        double distanceMeters = 0.0;
        if (useCameraPrior)
        {
            if (alpha != 0.0)
            {
                const double tanAlpha = std::tan(alpha);
                if (tanAlpha != 0.0)
                {
                    const double camHeightOverTanAlpha = camH / tanAlpha;
                    if (std::isfinite(camHeightOverTanAlpha))
                    {
                        hasCamHeightOverTanAlpha = true;
                        lastCamHeightOverTanAlphaMm = std::abs(camHeightOverTanAlpha);
                        distanceMeters = lastCamHeightOverTanAlphaMm / 1000.0;
                        distanceOverlay = formatDistanceText(distanceMeters);
                        currentDistanceValid = (distanceMeters > 0.0);
                    }
                }
            }
        }
        else if (targetHeightPx > 0 && hx_f > 0.0 && hx_W > 0.0)
        {
            const double distanceMm = (hx_f * hx_W) / static_cast<double>(targetHeightPx);
            distanceMeters = distanceMm / 1000.0;
            distanceOverlay = formatDistanceText(distanceMeters);
            currentDistanceValid = true;
        }

        if (currentDistanceValid)
        {
            hasValidDistance = true;
            lastDistanceMeters = distanceMeters;
            if (!hasCamHeightOverTanAlpha)
            {
                singleTargetDistanceMeters = distanceMeters;
            }
        }

        draw_rectangle(&src, x1, y1, x2 - x1, y2 - y1, COLOR_BLUE, box_thickness);
        const QByteArray overlayUtf8 = distanceOverlay.toUtf8();
        draw_text(&src, overlayUtf8.constData(), x1, y1 - 20 * scaleH, COLOR_RED, font_size);
        labelCount[label]++;
    }
    lastTargetHeightPx = frameTargetHeightPx;
    if (labelCount.isEmpty())
    {
        updateLabelInfoText(QStringLiteral("无检测目标"));
    }
    else
    {
        QStringList lines;
        for (auto it = labelCount.constBegin(); it != labelCount.constEnd(); ++it)
        {
            lines << QString("%1 %2").arg(it.key()).arg(it.value());
        }
        updateLabelInfoText(lines.join(QStringLiteral("\n")));
    }

    if (ui && ui->label_dis)
    {
        if (detectionCount == 0)
        {
            ui->label_dis->setText(tr("未检测到目标"));
        }
        else if (detectionCount > 1)
        {
            ui->label_dis->setText(tr("检测到多目标"));
        }
        else
        {
            if (hasValidDistance)
            {
                ui->label_dis->setText(tr("当前距离: %1").arg(formatDistanceText(lastDistanceMeters)));
            }
            else
            {
                ui->label_dis->setText(tr("当前距离: --"));
            }
        }
    }

    auto resetFilterState = [this]()
    {
        distanceFilterActive = false;
        filterSamples.clear();
        if (ui && ui->filterBtn)
        {
            ui->filterBtn->setEnabled(false);
            ui->filterBtn->setText(tr("开始滤波"));
        }
    };

    if (!ui)
    {
        resetFilterState();
    }
    else
    {
        if (!ui->label_dis_2)
        {
            resetFilterState();
        }
        else if (detectionCount != 1 || !hasValidDistance)
        {
            resetFilterState();
            ui->label_dis_2->setText(tr("滤波距离: --"));
        }
        else
        {
            if (!distanceFilterActive)
            {
                if (ui->filterBtn)
                {
                    ui->filterBtn->setEnabled(true);
                    ui->filterBtn->setText(tr("开始滤波"));
                }
            }
            if (distanceFilterActive)
            {
                filterSamples.append(singleTargetDistanceMeters);
                if (filterSamples.size() >= kFilterSampleCount)
                {
                    double sum = 0.0;
                    for (double v : std::as_const(filterSamples))
                    {
                        sum += v;
                    }
                    filteredDistanceMeters = sum / filterSamples.size();
                    ui->label_dis_2->setText(tr("滤波距离: %1").arg(formatDistanceText(filteredDistanceMeters)));
                    distanceFilterActive = false;
                    filterSamples.clear();
                    if (ui->filterBtn)
                    {
                        ui->filterBtn->setEnabled(true);
                        ui->filterBtn->setText(tr("开始滤波"));
                    }
                }
                else
                {
                    ui->label_dis_2->setText(tr("滤波中(%1/%2)").arg(filterSamples.size()).arg(kFilterSampleCount));
                }
            }
            else if (ui->label_dis_2)
            {
                const QString baseText = (filteredDistanceMeters > 0.0) ? formatDistanceText(filteredDistanceMeters) : QStringLiteral("--");
                ui->label_dis_2->setText(tr("滤波距离: %1").arg(baseText));
            }
        }
    }

    if (showCrosshair)
    {
        const int centerX = src.width / 2;
        const int centerY = src.height / 2;
        const int crossThickness = qMax(2, scaleW);
        draw_line(&src, 0, centerY, src.width - 1, centerY, COLOR_GREEN, crossThickness);
        draw_line(&src, centerX, 0, centerX, src.height - 1, COLOR_GREEN, crossThickness);

        const int tickLengthLong = qMax(18, 6 * scaleW);
        const int tickLengthShort = qMax(10, 3 * scaleW);
        const int tickSpacing = qMax(40, 40 * scaleW);

        auto drawTicks = [&](int axisLength, bool horizontal)
        {
            const int halfLength = axisLength / 2;
            for (int offset = tickSpacing; offset <= halfLength; offset += tickSpacing)
            {
                const bool longTick = ((offset / tickSpacing) % 2 == 0);
                const int len = longTick ? tickLengthLong : tickLengthShort;
                if (horizontal)
                {
                    draw_line(&src, centerX + offset, centerY - len, centerX + offset, centerY + len, COLOR_GREEN, crossThickness);
                    draw_line(&src, centerX - offset, centerY - len, centerX - offset, centerY + len, COLOR_GREEN, crossThickness);
                }
                else
                {
                    draw_line(&src, centerX - len, centerY + offset, centerX + len, centerY + offset, COLOR_GREEN, crossThickness);
                    draw_line(&src, centerX - len, centerY - offset, centerX + len, centerY - offset, COLOR_GREEN, crossThickness);
                }
            }
        };

        drawTicks(src.width, true);
        drawTicks(src.height, false);
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
    QImage displayImage = img.copy();

    displayLabel->setPixmap(QPixmap::fromImage(displayImage));

    // 释放 image_buffer_t 中分配的内存
    if (src.virt_addr)
    {
        free(src.virt_addr);
        src.virt_addr = NULL;
        src.size = 0;
    }
}

int distance::getTargetHeightPx(const object_detect_result &det) const
{
    const int boxWidth = det.box.right - det.box.left;
    const int boxHeight = det.box.bottom - det.box.top;
    const int maxEdge = qMax(boxWidth, boxHeight);
    return qMax(maxEdge, 0);
}

void distance::startDetection()
{
    if (detectionRunning)
    {
        return;
    }

    if (!myCamera)
    {
        if (cameraList.isEmpty())
        {
            QMessageBox::warning(this, tr("摄像头不可用"), tr("未检测到可用摄像头"));
            return;
        }
        myCamera = new QCamera(cameraList.first(), this);
        QCameraViewfinderSettings set;
        set.setResolution(640, 480);
        myCamera->setViewfinderSettings(set);
    }
    if (!displayLabel)
    {
        displayLabel = new QLabel(ui->widget);
        displayLabel->setGeometry(ui->widget->rect());
        displayLabel->setScaledContents(true);
    }

    if (!probe)
    {
        probe = new QVideoProbe(this);
        if (!probe->setSource(myCamera))
        {
            QMessageBox::warning(this, tr("初始化失败"), tr("视频帧捕获模块初始化失败"));
            delete probe;
            probe = nullptr;
            return;
        }
        connect(probe, &QVideoProbe::videoFrameProbed, this, &distance::processFrame, Qt::UniqueConnection);
    }
    else if (!probe->isActive())
    {
        if (!probe->setSource(myCamera))
        {
            QMessageBox::warning(this, tr("初始化失败"), tr("无法连接视频帧捕获模块"));
            return;
        }
    }

    myCamera->start();
    detectionRunning = true;

    if (displayLabel)
    {
        displayLabel->setGeometry(ui->widget->rect());
        displayLabel->show();
    }
    if (ui->back_btn_2)
    {
        ui->back_btn_2->setEnabled(false);
    }
    if (ui->back_btn_3)
    {
        ui->back_btn_3->setEnabled(true);
    }
    updateLabelInfoText(tr("检测中..."), true);
}

void distance::stopDetection()
{
    if (!detectionRunning)
    {
        return;
    }

    if (myCamera)
    {
        myCamera->stop();
    }

    detectionRunning = false;

    if (displayLabel)
    {
        displayLabel->clear();
        displayLabel->hide();
    }
    if (ui->back_btn_2)
    {
        ui->back_btn_2->setEnabled(true);
    }
    if (ui->back_btn_3)
    {
        ui->back_btn_3->setEnabled(false);
    }
    updateLabelInfoText(tr("检测已停止"), true);
    if (ui->label_fps)
    {
        ui->label_fps->setText("FPS: 0");
    }
}

void distance::releaseCameraResources()
{
    stopDetection();

    if (probe)
    {
        probe->setSource(static_cast<QCamera *>(nullptr));
        probe->disconnect(this);
        delete probe;
        probe = nullptr;
    }

    if (myCamera)
    {
        delete myCamera;
        myCamera = nullptr;
    }

    if (displayLabel)
    {
        delete displayLabel;
        displayLabel = nullptr;
    }
}

bool distance::convertNV12ToImageBufferSimple(QVideoFrame &frame, image_buffer_t *image_buf)
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

QString distance::formatDistanceText(double distanceMeters) const
{
    if (distanceMeters < 0.0)
    {
        return QStringLiteral("--");
    }

    if (distanceMeters < 1.0)
    {
        const double centimeters = distanceMeters * 100.0;
        return QStringLiteral("%1cm").arg(QString::number(centimeters, 'f', 1));
    }

    return QStringLiteral("%1m").arg(QString::number(distanceMeters, 'f', 2));
}

void distance::rotateNV12Frame180(image_buffer_t *image_buf)
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

void distance::on_comboBox_currentIndexChanged(int index)
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
    bool wasRunning = detectionRunning;
    myCamera->stop();
    myCamera->setViewfinderSettings(set);
    if (wasRunning)
    {
        myCamera->start();
    }

    qDebug() << "Camera resolution changed to" << desired;
    updateFocalParamsForResolution(desired);
}

void distance::on_lineEdit_1_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1);
    Q_UNUSED(arg2);

    // 当lineEdit_1获得焦点时显示虚拟键盘
    setActiveLineEdit(ui ? ui->lineEdit_1 : nullptr);

    if (!keyboardDialog || !keyboardDialog->isVisible())
    {
        showVirtualKeyboard();
    }
}

void distance::showVirtualKeyboard()
{
    if (!activeLineEdit)
    {
        if (ui && ui->lineEdit_1)
        {
            activeLineEdit = ui->lineEdit_1;
        }
        else if (ui && ui->lineEdit_2)
        {
            activeLineEdit = ui->lineEdit_2;
        }
    }

    if (keyboardDialog)
    {
        keyboardDialog->close();
        keyboardDialog->deleteLater();
        keyboardDialog = nullptr;
    }

    keyboardDialog = new QDialog(this, Qt::Window | Qt::FramelessWindowHint);
    keyboardDialog->setWindowTitle("虚拟键盘");
    keyboardDialog->setStyleSheet("background-color: rgb(50, 50, 50); border: 2px solid rgb(100, 100, 100);");
    keyboardDialog->setGeometry(520, 280, 560, 380);

    QVBoxLayout *mainLayout = new QVBoxLayout(keyboardDialog);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(10);

    // 第一行：1-3
    QHBoxLayout *row1 = new QHBoxLayout();
    for (int i = 1; i <= 3; i++)
    {
        QPushButton *btn = new QPushButton(QString::number(i));
        btn->setStyleSheet("background-color: rgb(70, 70, 70); color: white; font-size: 22px; border-radius: 8px;");
        btn->setMinimumHeight(72);
        connect(btn, &QPushButton::clicked, this, [this, i]()
                { onVirtualKeyboardButtonClicked(QString::number(i)); });
        row1->addWidget(btn);
    }
    mainLayout->addLayout(row1);

    // 第二行：4-6
    QHBoxLayout *row2 = new QHBoxLayout();
    for (int i = 4; i <= 6; i++)
    {
        QPushButton *btn = new QPushButton(QString::number(i));
        btn->setStyleSheet("background-color: rgb(70, 70, 70); color: white; font-size: 22px; border-radius: 8px;");
        btn->setMinimumHeight(72);
        connect(btn, &QPushButton::clicked, this, [this, i]()
                { onVirtualKeyboardButtonClicked(QString::number(i)); });
        row2->addWidget(btn);
    }
    mainLayout->addLayout(row2);

    // 第三行：7-9
    QHBoxLayout *row3 = new QHBoxLayout();
    for (int i = 7; i <= 9; i++)
    {
        QPushButton *btn = new QPushButton(QString::number(i));
        btn->setStyleSheet("background-color: rgb(70, 70, 70); color: white; font-size: 22px; border-radius: 8px;");
        btn->setMinimumHeight(72);
        connect(btn, &QPushButton::clicked, this, [this, i]()
                { onVirtualKeyboardButtonClicked(QString::number(i)); });
        row3->addWidget(btn);
    }
    mainLayout->addLayout(row3);

    // 第四行：0、小数点、删除
    QHBoxLayout *row4 = new QHBoxLayout();

    QPushButton *btn0 = new QPushButton("0");
    btn0->setStyleSheet("background-color: rgb(70, 70, 70); color: white; font-size: 22px; border-radius: 8px;");
    btn0->setMinimumHeight(72);
    connect(btn0, &QPushButton::clicked, this, [this]()
            { onVirtualKeyboardButtonClicked("0"); });
    row4->addWidget(btn0);

    QPushButton *btnPoint = new QPushButton(".");
    btnPoint->setStyleSheet("background-color: rgb(70, 70, 70); color: white; font-size: 22px; border-radius: 8px;");
    btnPoint->setMinimumHeight(72);
    connect(btnPoint, &QPushButton::clicked, this, [this]()
            { onVirtualKeyboardButtonClicked("."); });
    row4->addWidget(btnPoint);

    QPushButton *btnDel = new QPushButton("删除");
    btnDel->setStyleSheet("background-color: rgb(100, 50, 50); color: white; font-size: 20px; border-radius: 8px;");
    btnDel->setMinimumHeight(72);
    connect(btnDel, &QPushButton::clicked, this, &distance::onVirtualKeyboardBackspace);
    row4->addWidget(btnDel);

    mainLayout->addLayout(row4);

    // 第五行：清除、确认
    QHBoxLayout *row5 = new QHBoxLayout();

    QPushButton *btnClear = new QPushButton("清除");
    btnClear->setStyleSheet("background-color: rgb(100, 50, 50); color: white; font-size: 20px; border-radius: 8px;");
    btnClear->setMinimumHeight(72);
    connect(btnClear, &QPushButton::clicked, this, &distance::onVirtualKeyboardClear);
    row5->addWidget(btnClear);

    QPushButton *btnOK = new QPushButton("确认");
    btnOK->setStyleSheet("background-color: rgb(50, 100, 50); color: white; font-size: 20px; border-radius: 8px;");
    btnOK->setMinimumHeight(72);
    connect(btnOK, &QPushButton::clicked, this, &distance::onVirtualKeyboardOK);
    row5->addWidget(btnOK);

    mainLayout->addLayout(row5);

    keyboardDialog->setLayout(mainLayout);
    keyboardDialog->show();
}

void distance::onVirtualKeyboardButtonClicked(const QString &text)
{
    QLineEdit *target = activeLineEdit ? activeLineEdit : (ui ? ui->lineEdit_1 : nullptr);
    if (!target)
    {
        return;
    }

    target->insert(text);
}

void distance::onVirtualKeyboardBackspace()
{
    QLineEdit *target = activeLineEdit ? activeLineEdit : (ui ? ui->lineEdit_1 : nullptr);
    if (!target)
    {
        return;
    }

    if (!target->text().isEmpty())
    {
        target->backspace();
    }
}

void distance::onVirtualKeyboardClear()
{
    QLineEdit *target = activeLineEdit ? activeLineEdit : (ui ? ui->lineEdit_1 : nullptr);
    if (!target)
    {
        return;
    }

    target->clear();
}

void distance::onVirtualKeyboardOK()
{
    QLineEdit *target = activeLineEdit ? activeLineEdit : (ui ? ui->lineEdit_1 : nullptr);

    auto handleInvalidInput = [this, target](const QString &message)
    {
        QMessageBox::warning(this, tr("输入无效"), message);
        if (target)
        {
            target->setFocus(Qt::OtherFocusReason);
            target->selectAll();
        }
    };

    if (target == ui->lineEdit_2)
    {
        if (!updateCameraHeightFromLineEdit())
        {
            handleInvalidInput(tr("请输入有效的相机高度数值，单位为 mm"));
            return;
        }
        syncCameraHeightToLineEdit();
    }
    else
    {
        if (!updatePriorSizeFromLineEdit())
        {
            handleInvalidInput(tr("请输入有效的先验尺寸数值，单位为 mm"));
            return;
        }
        syncPriorSizeToLineEdit();
    }

    if (target)
    {
        target->deselect();
        target->clearFocus();
    }

    setFocus(Qt::OtherFocusReason);

    if (keyboardDialog)
    {
        keyboardDialog->close();
        keyboardDialog->deleteLater();
        keyboardDialog = nullptr;
    }
}

void distance::syncPriorSizeToLineEdit()
{
    if (!ui || !ui->lineEdit_1)
    {
        return;
    }

    ui->lineEdit_1->setText(QString::number(hx_W, 'f', 0));
}

bool distance::updatePriorSizeFromLineEdit()
{
    if (!ui || !ui->lineEdit_1)
    {
        return false;
    }

    QString text = ui->lineEdit_1->text().trimmed();
    text.remove(QRegularExpression("[^0-9.]"));

    bool ok = false;
    const double value = text.toDouble(&ok);
    if (!ok || value <= 0.0)
    {
        return false;
    }

    hx_W = value;
    return true;
}

void distance::syncCameraHeightToLineEdit()
{
    if (!ui || !ui->lineEdit_2)
    {
        return;
    }

    ui->lineEdit_2->setText(QString::number(camH, 'f', 0));
}

bool distance::updateCameraHeightFromLineEdit()
{
    if (!ui || !ui->lineEdit_2)
    {
        return false;
    }

    QString text = ui->lineEdit_2->text().trimmed();
    text.remove(QRegularExpression("[^0-9.]"));

    bool ok = false;
    const double value = text.toDouble(&ok);
    if (!ok || value <= 0.0)
    {
        return false;
    }

    camH = value;
    return true;
}

void distance::setActiveLineEdit(QLineEdit *edit)
{
    activeLineEdit = edit;
}

bool distance::applyFrequencySetting(const QString &freqText, const QString &sysfsPath, const QString &componentName)
{
    QString sanitized = freqText.trimmed();
    sanitized.remove(QRegularExpression("[^0-9]"));
    if (sanitized.isEmpty())
    {
        qWarning() << componentName << "frequency text invalid" << freqText;
        return false;
    }

    QFile freqFile(sysfsPath);
    if (!freqFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QMessageBox::warning(this, tr("设置失败"), tr("无法设置%1频率: %2").arg(componentName, freqFile.errorString()));
        return false;
    }

    QByteArray payload = sanitized.toUtf8();
    payload.append('\n');

    if (freqFile.write(payload) == -1)
    {
        QMessageBox::warning(this, tr("设置失败"), tr("写入%1频率失败: %2").arg(componentName, freqFile.errorString()));
        freqFile.close();
        return false;
    }

    freqFile.close();
    qInfo() << componentName << "frequency updated to" << sanitized << "via" << sysfsPath;
    return true;
}

// VirtualKeyboardFilter 实现
VirtualKeyboardFilter::VirtualKeyboardFilter(distance *parent)
    : QObject(parent), parentDistance(parent)
{
}

bool VirtualKeyboardFilter::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
        // 拦截所有物理键盘事件
        return true;

    case QEvent::MouseButtonPress:
    case QEvent::TouchBegin:
        if (QLineEdit *edit = qobject_cast<QLineEdit *>(obj))
        {
            parentDistance->setActiveLineEdit(edit);
            parentDistance->showVirtualKeyboard();
        }
        break;

    case QEvent::FocusIn:
        if (QLineEdit *edit = qobject_cast<QLineEdit *>(obj))
        {
            parentDistance->setActiveLineEdit(edit);
        }
        break;

    default:
        break;
    }

    return QObject::eventFilter(obj, event);
}

void distance::on_flip_btn_clicked()
{
    if (!ui)
    {
        return;
    }

    if (lastTargetHeightPx <= 0 || hx_W <= 0.0)
    {
        if (ui->label_f)
        {
            ui->label_f->setText(QStringLiteral("像素焦距：-- px"));
        }
        return;
    }

    hx_f = (static_cast<double>(lastTargetHeightPx) * hx_cor_dist) / hx_W;

    if (ui->label_f)
    {
        ui->label_f->setText(QStringLiteral("像素焦距：%1 px").arg(QString::number(hx_f, 'f', 2)));
    }
    currentFocalParams.f = hx_f;
    const QString key = buildResolutionKey(currentResolution);
    if (!key.isEmpty())
    {
        focalConfig.insert(key, currentFocalParams);
        if (!persistFocalParamsForResolution(key, currentFocalParams))
        {
            qWarning() << "Failed to persist calibrated focal length for" << key;
        }
    }
}
// #endif

void distance::on_zBtn_clicked()
{
    useCalibratedFocal = true;
    if (ui && ui->flip_btn)
    {
        ui->flip_btn->setEnabled(false);
    }
    applyCurrentFocalSetting();
}

void distance::on_xBtn_clicked()
{
    useCalibratedFocal = false;
    if (ui && ui->flip_btn)
    {
        ui->flip_btn->setEnabled(true);
    }
    applyCurrentFocalSetting();
}

void distance::on_show1Btn_clicked()
{
    showCrosshair = !showCrosshair;
    if (ui && ui->show1Btn)
    {
        ui->show1Btn->setText(showCrosshair ? tr("隐藏十字线") : tr("显示十字线"));
    }
}

void distance::on_filterBtn_clicked()
{
    if (distanceFilterActive)
    {
        return;
    }

    distanceFilterActive = true;
    filterSamples.clear();
    filteredDistanceMeters = 0.0;
    if (ui && ui->filterBtn)
    {
        ui->filterBtn->setEnabled(false);
        ui->filterBtn->setText(tr("滤波中"));
    }
    if (ui && ui->label_dis_2)
    {
        ui->label_dis_2->setText(tr("滤波中(0/%1)").arg(kFilterSampleCount));
    }
}

void distance::on_comboBox_3_currentIndexChanged(int index)
{
    if (!ui || !ui->comboBox_3)
    {
        return;
    }

    if (index < 0 || index >= ui->comboBox_3->count())
    {
        return;
    }

    QString text = ui->comboBox_3->itemText(index).trimmed();
    text.remove(QRegularExpression("[^0-9.]"));

    bool ok = false;
    double value = text.toDouble(&ok);
    if (ok && value > 0.0)
    {
        hx_cor_dist = value;
    }
}

void distance::on_usage_btn_clicked()
{
    usage *u = new usage;
    u->show();
}

void distance::on_comboBox_5_currentIndexChanged(int index)
{
    Q_UNUSED(index);

    if (!ui || !ui->comboBox_5)
    {
        return;
    }

    const QString freqText = ui->comboBox_5->currentText();
    if (freqText.isEmpty())
    {
        return;
    }

    applyFrequencySetting(freqText, QString::fromLatin1(kCpuFreqSysfsPath), tr("CPU"));
}

void distance::on_comboBox_6_currentIndexChanged(int index)
{
    Q_UNUSED(index);

    if (!ui || !ui->comboBox_6)
    {
        return;
    }

    const QString freqText = ui->comboBox_6->currentText();
    if (freqText.isEmpty())
    {
        return;
    }

    applyFrequencySetting(freqText, QString::fromLatin1(kNpuFreqSysfsPath), tr("NPU"));
}

void distance::setupResourceMonitor()
{
    if (resourceTimer)
    {
        return;
    }

    resourceTimer = new QTimer(this);
    resourceTimer->setInterval(2000);
    connect(resourceTimer, &QTimer::timeout, this, &distance::updateTemperatureDisplay);
    resourceTimer->start();
    updateTemperatureDisplay();
}

void distance::teardownResourceMonitor()
{
    if (!resourceTimer)
    {
        return;
    }

    resourceTimer->stop();
    resourceTimer->deleteLater();
    resourceTimer = nullptr;
}

void distance::updateTemperatureDisplay()
{
    if (!ui || !ui->label_res)
    {
        return;
    }

    double cpuTemp = 0.0;
    double gpuTemp = 0.0;
    const bool cpuOk = readTemperatureValue(QString::fromLatin1(kCpuTempSysfsPath), cpuTemp);
    const bool gpuOk = readTemperatureValue(QString::fromLatin1(kGpuTempSysfsPath), gpuTemp);

    QStringList lines;
    if (cpuOk)
    {
        lines << tr("CPU温度: %1°C").arg(QString::number(cpuTemp, 'f', 1));
    }
    else
    {
        lines << tr("CPU温度: --");
    }

    if (gpuOk)
    {
        lines << tr("GPU温度: %1°C").arg(QString::number(gpuTemp, 'f', 1));
    }
    else
    {
        lines << tr("GPU温度: --");
    }

    double memPercent = 0.0;
    double memUsedMB = 0.0;
    double memTotalMB = 0.0;
    if (readMemoryUsageViaFree(memPercent, memUsedMB, memTotalMB))
    {
        lines << tr("内存: %1MB / %2MB (%3%)")
                     .arg(QString::number(memUsedMB, 'f', 0),
                          QString::number(memTotalMB, 'f', 0),
                          QString::number(memPercent, 'f', 1));
    }
    else
    {
        lines << tr("内存: --");
    }

    QString cpuLine;
    // if (readCpuUsageLineViaTop(cpuLine))
    // {
    //     lines << tr("CPU占用(top): %1").arg(cpuLine);
    // }
    // else
    // {
    //     lines << tr("CPU占用(top): --");
    // }

    QString npuLine;
    if (readNpuLoadInfo(npuLine))
    {
        lines << tr("NPU占用: %1").arg(npuLine);
    }
    else
    {
        lines << tr("NPU占用: --");
    }

    QString ddrLine;
    if (readDdrLoadInfo(ddrLine))
    {
        lines << tr("DDR带宽: %1").arg(ddrLine);
    }
    else
    {
        lines << tr("DDR带宽: --");
    }

    ui->label_res->setText(lines.join("\n"));
}

bool distance::readTemperatureValue(const QString &path, double &valueCelsius)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open temp node" << path << file.errorString();
        return false;
    }

    QByteArray content = file.readAll().trimmed();
    file.close();

    bool ok = false;
    const double rawValue = content.toDouble(&ok);
    if (!ok)
    {
        qWarning() << "Invalid temperature value" << content << "from" << path;
        return false;
    }

    valueCelsius = rawValue / 1000.0;
    return true;
}

bool distance::readMemoryUsageViaFree(double &usedPercent, double &usedMB, double &totalMB)
{
    QProcess process;
    process.start(QStringLiteral("free"), QStringList() << QStringLiteral("-m"));
    if (!process.waitForFinished(1000))
    {
        process.kill();
        return false;
    }

    const QByteArray stdoutData = process.readAllStandardOutput();
    if (stdoutData.isEmpty())
    {
        return false;
    }

    const QStringList lines = QString::fromUtf8(stdoutData).split('\n', Qt::SkipEmptyParts);
    for (const QString &line : lines)
    {
        const QString trimmed = line.trimmed();
        if (!trimmed.startsWith(QStringLiteral("Mem:")))
        {
            continue;
        }

        QStringList parts = trimmed.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        if (parts.size() < 3)
        {
            return false;
        }

        bool totalOk = false;
        bool usedOk = false;
        const double totalValue = parts.at(1).toDouble(&totalOk);
        const double usedValue = parts.at(2).toDouble(&usedOk);
        if (!totalOk || !usedOk || totalValue <= 0.0)
        {
            return false;
        }

        totalMB = totalValue;
        usedMB = usedValue;
        usedPercent = (usedMB / totalMB) * 100.0;
        return true;
    }

    return false;
}

bool distance::readNpuLoadInfo(QString &resultLine)
{
    QFile file(QString::fromLatin1(kNpuLoadSysfsPath));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open NPU load node" << kNpuLoadSysfsPath << file.errorString();
        return false;
    }

    const QString content = QString::fromUtf8(file.readAll()).trimmed();
    file.close();

    if (content.isEmpty())
    {
        return false;
    }

    const QStringList lines = content.split('\n', Qt::SkipEmptyParts);
    if (lines.isEmpty())
    {
        return false;
    }

    for (const QString &line : lines)
    {
        const QString trimmed = line.trimmed();
        if (trimmed.isEmpty())
        {
            continue;
        }

        if (trimmed.contains(QStringLiteral("load"), Qt::CaseInsensitive) || trimmed.contains('%'))
        {
            resultLine = formatLoadPercentage(trimmed);
            return true;
        }
    }

    resultLine = formatLoadPercentage(lines.first().trimmed());
    return true;
}

bool distance::readDdrLoadInfo(QString &resultLine)
{
    QFile file(QString::fromLatin1(kDdrLoadSysfsPath));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open DDR load node" << kDdrLoadSysfsPath << file.errorString();
        return false;
    }

    const QString content = QString::fromUtf8(file.readAll()).trimmed();
    file.close();

    if (content.isEmpty())
    {
        return false;
    }

    const QStringList lines = content.split('\n', Qt::SkipEmptyParts);
    if (lines.isEmpty())
    {
        return false;
    }

    for (const QString &line : lines)
    {
        const QString trimmed = line.trimmed();
        if (trimmed.isEmpty())
        {
            continue;
        }

        if (trimmed.contains(QStringLiteral("load"), Qt::CaseInsensitive) ||
            trimmed.contains(QStringLiteral("util"), Qt::CaseInsensitive))
        {
            resultLine = formatLoadPercentage(trimmed);
            return true;
        }
    }

    const QString firstLine = lines.first().trimmed();
    if (firstLine.isEmpty())
    {
        return false;
    }

    resultLine = formatLoadPercentage(firstLine);
    return true;
}

bool distance::readCpuUsageLineViaTop(QString &cpuLine)
{
    QString output = runCommandAndCapture(QStringLiteral("top"),
                                          {QStringLiteral("-b"), QStringLiteral("-n"), QStringLiteral("1")});
    if (!output.isEmpty() && extractCpuLine(output, cpuLine))
    {
        return true;
    }

    output = runCommandAndCapture(QStringLiteral("top"), {QStringLiteral("-n"), QStringLiteral("1")});
    if (!output.isEmpty() && extractCpuLine(output, cpuLine))
    {
        return true;
    }

    const QStringList shellCommands = {
        QStringLiteral("COLUMNS=256 top -b -n 1 | head -n 5"),
        QStringLiteral("COLUMNS=256 top -n 1 | head -n 5"),
        QStringLiteral("COLUMNS=256 busybox top -n 1 | head -n 5")};

    for (const QString &command : shellCommands)
    {
        output = runShellCommand(command);
        if (output.isEmpty())
        {
            continue;
        }

        if (extractCpuLine(output, cpuLine))
        {
            return true;
        }
    }

    static bool warnedTopFailure = false;
    if (!warnedTopFailure)
    {
        warnedTopFailure = true;
        qWarning() << "Failed to gather CPU usage via top";
    }

    return false;
}

QString distance::runCommandAndCapture(const QString &program, const QStringList &arguments, int timeoutMs) const
{
    if (program.trimmed().isEmpty())
    {
        return QString();
    }

    QProcess process;
    process.start(program, arguments);
    if (!process.waitForStarted(timeoutMs))
    {
        return QString();
    }

    if (!process.waitForFinished(timeoutMs))
    {
        process.kill();
        process.waitForFinished(500);
        return QString();
    }

    const QByteArray stdOut = process.readAllStandardOutput();
    if (!stdOut.isEmpty())
    {
        return QString::fromUtf8(stdOut).trimmed();
    }

    const QByteArray stdErr = process.readAllStandardError();
    return QString::fromUtf8(stdErr).trimmed();
}

QString distance::runShellCommand(const QString &command, int timeoutMs) const
{
    const QString trimmed = command.trimmed();
    if (trimmed.isEmpty())
    {
        return QString();
    }

    return runCommandAndCapture(QStringLiteral("/bin/sh"),
                                {QStringLiteral("-c"), trimmed},
                                timeoutMs);
}

QString distance::buildResolutionKey(const QSize &resolution) const
{
    if (resolution.width() <= 0 || resolution.height() <= 0)
    {
        return QString();
    }

    return QStringLiteral("%1x%2").arg(resolution.width()).arg(resolution.height());
}

bool distance::persistFocalParamsForResolution(const QString &resolutionKey, const FocalParams &params)
{
    if (resolutionKey.isEmpty() || params.f <= 0.0)
    {
        return false;
    }

    if (focalConfigPath.isEmpty())
    {
        focalConfigLoaded = loadFocalConfigFromFile();
        if (focalConfigPath.isEmpty())
        {
            qWarning() << "Cannot persist focal params, config path missing";
            return false;
        }
    }

    QFile readFile(focalConfigPath);
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to reopen" << focalConfigPath << readFile.errorString();
        return false;
    }

    const QByteArray rawJson = readFile.readAll();
    readFile.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(rawJson, &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject())
    {
        qWarning() << "Persist failed, invalid JSON" << focalConfigPath << parseError.errorString();
        return false;
    }

    QJsonObject root = doc.object();
    QJsonValue resolutionsValue = root.value(QStringLiteral("resolutions"));
    if (!resolutionsValue.isObject() && !resolutionsValue.isArray())
    {
        qWarning() << "Persist failed, missing 'resolutions' node";
        return false;
    }

    const auto matchesResolution = [this, &resolutionKey](const QString &keyHint, const QJsonObject &entry) -> bool
    {
        const int width = entry.value(QStringLiteral("width")).toInt();
        const int height = entry.value(QStringLiteral("height")).toInt();
        if (width == currentResolution.width() && height == currentResolution.height())
        {
            return true;
        }
        const QString derived = (width > 0 && height > 0) ? QStringLiteral("%1x%2").arg(width).arg(height) : QString();
        if (!derived.isEmpty() && derived == resolutionKey)
        {
            return true;
        }
        if (!keyHint.isEmpty() && keyHint == resolutionKey)
        {
            return true;
        }
        const QStringList parts = keyHint.split(QLatin1Char('x'));
        if (parts.size() == 2)
        {
            bool wOk = false;
            bool hOk = false;
            const int hintedW = parts.at(0).toInt(&wOk);
            const int hintedH = parts.at(1).toInt(&hOk);
            if (wOk && hOk && hintedW == currentResolution.width() && hintedH == currentResolution.height())
            {
                return true;
            }
        }
        return false;
    };

    const auto assignFocalValues = [&params](QJsonObject &entry)
    {
        entry.insert(QStringLiteral("f"), params.f);
    };

    bool updated = false;
    if (resolutionsValue.isObject())
    {
        QJsonObject resObj = resolutionsValue.toObject();
        for (auto it = resObj.begin(); it != resObj.end(); ++it)
        {
            if (!it.value().isObject())
            {
                continue;
            }
            QJsonObject entry = it.value().toObject();
            if (!matchesResolution(it.key(), entry))
            {
                continue;
            }
            assignFocalValues(entry);
            resObj[it.key()] = entry;
            updated = true;
            break;
        }
        if (updated)
        {
            root.insert(QStringLiteral("resolutions"), resObj);
        }
    }
    else
    {
        QJsonArray resArray = resolutionsValue.toArray();
        for (int i = 0; i < resArray.size(); ++i)
        {
            if (!resArray.at(i).isObject())
            {
                continue;
            }
            QJsonObject entry = resArray.at(i).toObject();
            const QString keyHint = QStringLiteral("%1x%2").arg(entry.value(QStringLiteral("width")).toInt()).arg(entry.value(QStringLiteral("height")).toInt());
            if (!matchesResolution(keyHint, entry))
            {
                continue;
            }
            assignFocalValues(entry);
            resArray.replace(i, entry);
            updated = true;
            break;
        }
        if (updated)
        {
            root.insert(QStringLiteral("resolutions"), resArray);
        }
    }

    if (!updated)
    {
        qWarning() << "Persist failed, resolution entry not found for" << resolutionKey;
        return false;
    }

    QSaveFile outFile(focalConfigPath);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open config for writing" << focalConfigPath << outFile.errorString();
        return false;
    }

    QJsonDocument outDoc(root);
    const QByteArray payload = outDoc.toJson(QJsonDocument::Indented);
    if (outFile.write(payload) != payload.size())
    {
        qWarning() << "Failed to write complete config payload";
        outFile.cancelWriting();
        return false;
    }

    if (!outFile.commit())
    {
        qWarning() << "Failed to commit config changes" << focalConfigPath;
        outFile.cancelWriting();
        return false;
    }

    return true;
}

bool distance::loadFocalConfigFromFile()
{
    const QStringList candidatePaths = {
        QStringLiteral("src/distance/conf.json"),
        QStringLiteral("distance/conf.json"),
        QStringLiteral("./conf.json")};

    QString configPath;
    for (const QString &path : candidatePaths)
    {
        if (QFile::exists(path))
        {
            configPath = path;
            break;
        }
    }

    if (configPath.isEmpty())
    {
        qWarning() << "conf.json not found for focal config";
        focalConfig.clear();
        focalConfigPath.clear();
        return false;
    }

    focalConfigPath = configPath;

    QFile configFile(configPath);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Unable to open" << configPath << configFile.errorString();
        focalConfig.clear();
        return false;
    }

    const QByteArray rawJson = configFile.readAll();
    configFile.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(rawJson, &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject())
    {
        qWarning() << "Invalid JSON in" << configPath << parseError.errorString();
        focalConfig.clear();
        return false;
    }

    const QJsonObject rootObj = doc.object();
    const QJsonValue resolutionsValue = rootObj.value(QStringLiteral("resolutions"));
    if (!resolutionsValue.isObject() && !resolutionsValue.isArray())
    {
        qWarning() << "Missing 'resolutions' node in" << configPath;
        focalConfig.clear();
        return false;
    }

    focalConfig.clear();

    auto consumeEntry = [this](const QString &keyHint, const QJsonObject &entry)
    {
        QSize size;
        if (entry.contains(QStringLiteral("width")) && entry.contains(QStringLiteral("height")))
        {
            size.setWidth(entry.value(QStringLiteral("width")).toInt());
            size.setHeight(entry.value(QStringLiteral("height")).toInt());
        }
        else if (!keyHint.isEmpty())
        {
            const QStringList parts = keyHint.split(QLatin1Char('x'));
            if (parts.size() == 2)
            {
                bool wOk = false;
                bool hOk = false;
                const int width = parts.at(0).toInt(&wOk);
                const int height = parts.at(1).toInt(&hOk);
                if (wOk && hOk)
                {
                    size = QSize(width, height);
                }
            }
        }

        if (size.isEmpty())
        {
            return;
        }

        FocalParams params;
        params.f = entry.value(QStringLiteral("f")).toDouble();
        if (params.f <= 0.0)
        {
            params.f = entry.value(QStringLiteral("fx")).toDouble();
        }
        params.fy = entry.value(QStringLiteral("fy")).toDouble();

        const QString key = buildResolutionKey(size);
        if (!key.isEmpty())
        {
            focalConfig.insert(key, params);
        }
    };

    if (resolutionsValue.isObject())
    {
        const QJsonObject resObj = resolutionsValue.toObject();
        for (auto it = resObj.constBegin(); it != resObj.constEnd(); ++it)
        {
            if (!it.value().isObject())
            {
                continue;
            }
            consumeEntry(it.key(), it.value().toObject());
        }
    }
    else
    {
        const QJsonArray resArray = resolutionsValue.toArray();
        for (const QJsonValue &value : resArray)
        {
            if (!value.isObject())
            {
                continue;
            }
            consumeEntry(QString(), value.toObject());
        }
    }

    return !focalConfig.isEmpty();
}

bool distance::updateFocalParamsForResolution(const QSize &resolution)
{
    currentResolution = resolution;
    if (!focalConfigLoaded)
    {
        focalConfigLoaded = loadFocalConfigFromFile();
    }

    const QString key = buildResolutionKey(resolution);
    if (key.isEmpty())
    {
        return false;
    }

    if (!focalConfig.contains(key))
    {
        qWarning() << "No focal config for" << key;
        return false;
    }

    currentFocalParams = focalConfig.value(key);
    applyCurrentFocalSetting();
    return true;
}

void distance::applyCurrentFocalSetting()
{
    double candidate = useCalibratedFocal ? currentFocalParams.fy : currentFocalParams.f;
    if (candidate <= 0.0)
    {
        const double fallback = useCalibratedFocal ? currentFocalParams.f : currentFocalParams.fy;
        candidate = fallback;
    }

    if (candidate <= 0.0)
    {
        return;
    }

    hx_f = candidate;
    if (ui && ui->label_f)
    {
        const QString modeText = useCalibratedFocal ? tr("标定焦距") : tr("校正焦距");
        ui->label_f->setText(tr("%1：%2 px").arg(modeText, QString::number(hx_f, 'f', 2)));
    }
}

void distance::on_comboBox_7_currentIndexChanged(int index)
{
    Q_UNUSED(index);

    if (!ui || !ui->comboBox_7)
    {
        return;
    }

    const QString freqText = ui->comboBox_7->currentText();
    if (freqText.isEmpty())
    {
        return;
    }

    applyFrequencySetting(freqText, QString::fromLatin1(kGpuFreqSysfsPath), tr("GPU"));
}

void distance::handleLogMessage(const QString &line)
{
    appendLogLine(line);
}

void distance::appendLogLine(const QString &line)
{
    const QString trimmed = line.trimmed();
    if (trimmed.isEmpty())
    {
        return;
    }

    const QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("HH:mm:ss"));
    const QString entry = QStringLiteral("[%1] %2").arg(timestamp, trimmed);

    logBuffer.append(entry);
    while (logBuffer.size() > kMaxLogLines)
    {
        logBuffer.removeFirst();
    }

    if (ui && ui->label_info)
    {
        const int startIndex = qMax(0, logBuffer.size() - kVisibleLogLines);
        const QStringList visibleLines = logBuffer.mid(startIndex);
        ui->label_info->setText(visibleLines.join(QStringLiteral("\n")));
    }
}

void distance::updateLabelInfoText(const QString &text, bool forceLog)
{
    const QString normalized = text.trimmed();

    if (normalized.isEmpty())
    {
        return;
    }

    if (!forceLog && normalized == lastLabelInfoEntry)
    {
        return;
    }

    lastLabelInfoEntry = normalized;
    appendLogLine(normalized);
}

void distance::qtLogProxy(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QtMessageHandler previous = s_prevHandler;
    if (previous)
    {
        previous(type, context, msg);
    }

    distance *receiver = nullptr;
    {
        QMutexLocker locker(&s_logMutex);
        receiver = s_logReceiver;
    }

    if (!receiver)
    {
        return;
    }

    const QString trimmed = msg.trimmed();
    if (trimmed.isEmpty())
    {
        return;
    }

    QMetaObject::invokeMethod(receiver,
                              "handleLogMessage",
                              Qt::QueuedConnection,
                              Q_ARG(QString, trimmed));
}

void distance::on_scrshotBtn_clicked()
{
    const QString dirPath = QStringLiteral("./img");
    QDir dir(dirPath);
    if (!dir.exists())
    {
        dir.mkpath(QStringLiteral("."));
    }

    QProcess process;
    process.setProgram(QStringLiteral("weston-screenshooter"));
    process.setWorkingDirectory(dir.absolutePath());

    process.start(QIODevice::ReadOnly);
    if (!process.waitForStarted(3000))
    {
        QMessageBox::warning(this, tr("截屏失败"), tr("无法启动weston-screenshooter"));
        updateLabelInfoText(tr("截屏失败: 启动命令失败"), true);
        return;
    }

    if (!process.waitForFinished(10000))
    {
        process.kill();
        QMessageBox::warning(this, tr("截屏失败"), tr("weston-screenshooter超时"));
        updateLabelInfoText(tr("截屏失败: 命令超时"), true);
        return;
    }

    if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0)
    {
        const QString err = QString::fromUtf8(process.readAllStandardError());
        QMessageBox::warning(this, tr("截屏失败"), tr("weston-screenshooter返回错误: %1").arg(err));
        updateLabelInfoText(tr("截屏失败: %1").arg(err.isEmpty() ? QString::number(process.exitCode()) : err), true);
        return;
    }
    updateLabelInfoText(tr("截图完成"), true);
}

