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
    //-----------------/
    QDir dir("./saveimg");
    if (!dir.exists())
    {
        dir.mkpath(".");
    }
    QStringList filters;
    filters << "pic_*.jpg";
    dir.setNameFilters(filters);
    dir.setSorting(QDir::Name);

    maxIndex = -1;
    foreach (QString file, dir.entryList())
    {
        QRegExp rx("pic_(\\d+)\\.jpg");
        if (rx.exactMatch(file))
        {
            int idx = rx.cap(1).toInt();
            if (idx > maxIndex)
                maxIndex = idx;
        }
    }
    if (maxIndex > -1)
    {
        QString fileName = QString("./saveimg/pic_%1.jpg").arg(maxIndex);
        ui->picbtn->setIcon(QIcon(fileName));
    }

    //---------------
    cameraList = QCameraInfo::availableCameras();

    if (cameraList.count() > 0)
    {

        foreach (QCameraInfo info, cameraList)
        {
            // 人能读懂的设备名字
            qDebug() << info.description();
            qDebug() << info.deviceName();
        }
    }
    //----
    myCamera = new QCamera(cameraList[default_index], this); // camera指向指定的摄像头
    cp = new QCameraImageCapture(myCamera);

    // 抓取图片的信号
    connect(cp, &QCameraImageCapture::imageCaptured, this, &cam::save_pic);
    // 设置默认摄像头参数
    QCameraViewfinderSettings set;
    // set.setResolution(960, 720); // 设置显示分辨率
    // set.setMaximumFrameRate(30);  // 设置帧率
    myCamera->setViewfinderSettings(set);
    w = new QVideoWidget(ui->widget);
    w->resize(ui->widget->size());
    myCamera->stop();
    myCamera->setViewfinder(w); // 指定图像的输出窗口
    myCamera->start();          // 启动
    w->show();
#ifdef __linux__
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &cam::onTimeout);
    timer->setSingleShot(true);
    timer->start(600);
#endif
}
void cam::onTimeout()
{
#ifdef __linux__
    touch_simulate(0, 0);
    touch_simulate(0, 1);
#endif
}
cam::~cam()
{

    delete ui;
}

// void cam::on_openbtn_clicked() // 刷新
// {
// }

void cam::save_pic(int id, const QImage &preview)
{

    int nextIndex = maxIndex + 1;
    maxIndex = nextIndex;
    QString fileName = QString("./saveimg/pic_%1.jpg").arg(nextIndex);
    qDebug() << id << fileName;
    preview.save(fileName);
    QPixmap mmp = QPixmap::fromImage(preview);
    mmp = mmp.scaled(ui->picbtn->size(), Qt::KeepAspectRatio,
                     Qt::SmoothTransformation);
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
        desired = QSize(960, 720);
        break;
    case 2:
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
