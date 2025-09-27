#include "cam.h"
#include "gallery.h"
#include <QDir>

cam::cam(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_cam)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

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
    // 创建一个获取图片对象
    cp = new QCameraImageCapture(myCamera);

    // 抓取图片的信号
    connect(cp, &QCameraImageCapture::imageCaptured, this, &cam::save_pic);
    // 设置默认摄像头参数
    QCameraViewfinderSettings set;
    set.setResolution(640, 480); // 设置显示分辨率
    set.setMaximumFrameRate(30); // 设置帧率
    myCamera->setViewfinderSettings(set);

    myCamera->start(); // 启动

    w = new QVideoWidget(ui->widget);
    w->resize(ui->widget->size());
    myCamera->setViewfinder(w); // 指定图像的输出窗口
    w->show();
}

cam::~cam()
{
    delete ui;
}
void cam::on_openbtn_clicked() // 刷新
{
}

void cam::save_pic(int id, const QImage &preview)
{

    int nextIndex = maxIndex + 1;
    maxIndex = nextIndex;
    QString fileName = QString("./saveimg/pic_%1.jpg").arg(nextIndex);
    qDebug() << id << fileName;
    preview.save(fileName);
    QPixmap mmp = QPixmap::fromImage(preview);
    mmp = mmp.scaled(ui->picbtn->size());
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
}
