#include "cam.h"
#include "src/gallery/gallery.h"
#include <QDir>
#ifdef __linux__
extern "C"
{
    void touch_init();
    void touch_simulate(int x, int y);
    void touch_cleanup();
}
#endif

bool cam_ui_open = false;
cam::cam(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_cam)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    QByteArray ba = qgetenv("PROJECT_ROOT");
    QString projectRoot = ba.isEmpty() ? QString() : QString::fromUtf8(ba);
    QDir::setCurrent(projectRoot);

    // 确保保存目录存在
    QDir imgDir("./img");
    if (!imgDir.exists())
        imgDir.mkpath(".");

    // 使用所有受支持的图片格式作为过滤器，扫描 ./img 和 ./ 两个目录（绝对路径、去重、排序）
    QStringList filters;
    for (const QByteArray &fmt : QImageReader::supportedImageFormats())
        filters << "*." + QString(fmt).toLower();

    QStringList searchDirs = {"./img", "./"};
    QSet<QString> seen;
    QStringList foundFiles;
    for (const QString &dpath : searchDirs)
    {
        QDir d(dpath);
        if (!d.exists())
            continue;
        d.setNameFilters(filters);
        d.setSorting(QDir::Name);
        QStringList entries = d.entryList(QDir::Files, QDir::Name);
        for (const QString &ename : entries)
        {
            QString abs = d.absoluteFilePath(ename);
            if (!seen.contains(abs))
            {
                seen.insert(abs);
                foundFiles.append(abs);
            }
        }
    }
    // 按文件名排序（忽略大小写）
    std::sort(foundFiles.begin(), foundFiles.end(), [](const QString &a, const QString &b)
              { return QFileInfo(a).fileName().toLower() < QFileInfo(b).fileName().toLower(); });

    // 如果有图片，设置缩略按钮为最后一张
    if (!foundFiles.isEmpty())
    {
        QString last = foundFiles.last();
        ui->picbtn->setIcon(QIcon(last));
    }
    // 可以在需要时把 foundFiles 保存为成员以便后续使用（这里仅用于缩略图）

    // 初始化摄像头
    cameraList = QCameraInfo::availableCameras();
    if (cameraList.count() > 0)
    {
        for (const QCameraInfo &info : cameraList)
        {
            qDebug() << info.description() << info.deviceName();
        }
    }

    // 使用默认索引（请确保 default_index 有合理值）
    myCamera = new QCamera(cameraList.isEmpty() ? QCameraInfo() : cameraList[default_index], this);
    cp = new QCameraImageCapture(myCamera);

    // 捕获信号
    connect(cp, &QCameraImageCapture::imageCaptured, this, &cam::save_pic);
    videoProbe = new QVideoProbe(this);
    if (videoProbe->setSource(myCamera))
    {
        connect(videoProbe, &QVideoProbe::videoFrameProbed,
                this, &cam::onVideoFrameProbed);
        fpsTimer.start();
        fpsFrameCount = 0;
    }
    else
    {
        delete videoProbe;
        videoProbe = nullptr;
    }

    // 默认 viewfinder 设置（可后续由 comboBox 修改）
    QCameraViewfinderSettings set;
    myCamera->setViewfinderSettings(set);

    w = new QVideoWidget(ui->widget);
    w->resize(ui->widget->size());
    myCamera->stop();
    myCamera->setViewfinder(w);
    myCamera->start();
    w->show();

#ifdef __linux__
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &cam::onTimeout);
    timer->setSingleShot(true);
    timer->start(600);
#endif
}
void cam::onVideoFrameProbed(const QVideoFrame &frame)
{
    Q_UNUSED(frame);
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
}
void cam::onTimeout()
{
#ifdef __linux__
    touch_simulate(0, 0);
    touch_simulate(0, 1);
#endif
}
cam::~cam()
{ // 清理 probe（parent 为 this 可省略，但显式删除也可以）
    if (videoProbe)
    {
        videoProbe->disconnect(); /* parent will delete */
        videoProbe = nullptr;
    }

    delete ui;
}

// void cam::on_openbtn_clicked() // 刷新
// {
// }
static QString makeUniqueImagePath(const QString &dirPath, const QString &ext = "jpg")
{
    QDir dir(dirPath);
    if (!dir.exists())
        dir.mkpath(".");

    // 时间戳 + UUID 保证唯一性（不依赖索引）
    QString base = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss_zzz");
    QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QString name = QString("%1_%2.%3").arg(base).arg(uuid).arg(ext);
    return dir.filePath(name);
}
void cam::save_pic(int id, const QImage &preview)
{

    // 保存目录与格式（可改为从设置中读取）
    const QString dirPath = QStringLiteral("./img");
    const QString ext = QStringLiteral("jpg"); // 或 "png"

    // 先生成目标路径与临时文件路径
    QString target = makeUniqueImagePath(dirPath, ext);
    QString tmp = target + ".tmp";

    // 保存到临时文件（指定格式）
    bool ok = preview.save(tmp, ext.toUtf8().constData());
    if (!ok)
    {
        qWarning() << "保存临时图片失败：" << tmp;
        QFile::remove(tmp);
        return;
    }

    // 原子重命名到目标文件（覆盖保护）
    if (QFile::exists(target))
        QFile::remove(target);
    if (!QFile::rename(tmp, target))
    {
        qWarning() << "临时文件重命名失败：" << tmp << "->" << target;
        QFile::remove(tmp);
        return;
    }

    qDebug() << id << "saved to" << target;

    // 更新缩略按钮图标（使用缩放的 pixmap）
    QPixmap mmp = QPixmap::fromImage(preview);
    mmp = mmp.scaled(ui->picbtn->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->picbtn->setIcon(QIcon(mmp));
}

void cam::on_screenshotbtn_clicked()
{
    cp->capture();
}

void cam::on_camBackBtn_clicked()
{
    myCamera->stop();
    w->close();
    delete myCamera;
    delete cp;
    delete w;
    this->close();
}

void cam::on_picbtn_clicked()
{
    gallery *g = new gallery();
    g->show();
    cam_ui_open = true;
    myCamera->stop();
    w->close();
    delete myCamera;
    delete cp;
    delete w;
    this->close();
}

void cam::on_comboBox_currentIndexChanged(int index)
{
    if (!myCamera)
        return;

    // 根据 combo index 选择期望分辨率
    QSize desired;
    switch (index)
    {
    case 0:
        desired = QSize(2592, 1944);
        break; // index=0 -> 1920x1080
    case 1:
        desired = QSize(1920, 1440);
        break; // index=1 -> 1920x1440
    case 2:
        desired = QSize(1280, 960);
        break; // index=2 -> 1280x960
    case 3:
        desired = QSize(960, 720);
        break;
    case 4:
        desired = QSize(640, 480);
        break;
    default:
        desired = QSize(2592, 1944);
        break;
    }
    // 构造并应用 viewfinder 设置（需要 stop/set/start）
    QCameraViewfinderSettings viewSet;
    viewSet.setResolution(desired);
    viewSet.setMinimumFrameRate(15.0);
    viewSet.setMaximumFrameRate(30.0);

    bool wasActive = (myCamera->state() == QCamera::ActiveState);
    myCamera->stop();
    myCamera->setViewfinderSettings(viewSet);
    myCamera->setViewfinder(w); // 保持输出窗口
    if (wasActive)
        myCamera->start();

    // 可选：为抓拍设置编码分辨率（若后端支持）
    if (cp)
    {
        QImageEncoderSettings enc;
        enc.setCodec("image/jpeg");
        enc.setQuality(QMultimedia::NormalQuality);
        enc.setResolution(desired);
        cp->setEncodingSettings(enc);
    }

    qDebug() << "Camera resolution changed to" << desired;
#ifdef __linux__
    timer->start(600);
#endif
}
void cam::sim_click(int x, int y)
{
    QMouseEvent *pressEvent, *releaseEvent;
    pressEvent = new QMouseEvent(QEvent::MouseButtonPress, QPoint(x, y), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    releaseEvent = new QMouseEvent(QEvent::MouseButtonRelease, QPoint(x, y), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(w, pressEvent);
    QApplication::sendEvent(w, releaseEvent);
}
void cam::mousePressEvent(QMouseEvent *event)
{
    auto pos = event->pos(); // 获得鼠标点击的位置
    qDebug() << pos;
}
