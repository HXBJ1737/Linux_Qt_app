#include "gallery.h"
#include "QDir"
#include <QMessageBox>
#include <QFile>
gallery::gallery(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::gallery)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

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
        ui->widget->setStyleSheet(QString("border-image: url(%1);").arg(fileName));
        currentIndex = maxIndex;

    }
}

gallery::~gallery()
{
    delete ui;
}

void gallery::on_backBtn_clicked()
{
    this->close();
}

void gallery::on_lastBtn_clicked()
{
    currentIndex--;
    if (currentIndex < 0)
    {
        currentIndex =maxIndex ;
    }
     
    QString fileName = QString("./saveimg/pic_%1.jpg").arg(currentIndex);
    ui->widget->setStyleSheet(QString("border-image: url(%1);").arg(fileName));
        
    
}

void gallery::on_nextBtn_clicked()
{
    currentIndex++;
    if (currentIndex >maxIndex)
    {
        currentIndex = 0;
    }
     
    QString fileName = QString("./saveimg/pic_%1.jpg").arg(currentIndex);
    ui->widget->setStyleSheet(QString("border-image: url(%1);").arg(fileName));
}

void gallery::on_rm_Btn_clicked()
{


    if (currentIndex < 0)
        return;

    QString dirPath = "./saveimg";
    QString filePath = QString("%1/pic_%2.jpg").arg(dirPath).arg(currentIndex);

    // 确认删除
    if (QMessageBox::question(this, tr("删除图片"), tr("确定要删除当前图片？"),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
    {
        return;
    }

    QFile file(filePath);
    if (!file.exists())
    {
        QMessageBox::warning(this, tr("删除失败"), tr("文件不存在：%1").arg(filePath));
        return;
    }

    if (!file.remove())
    {
        QMessageBox::warning(this, tr("删除失败"), tr("无法删除文件：%1").arg(filePath));
        return;
    }

    // 重新扫描目录，更新 maxIndex 与 currentIndex
    QDir dir(dirPath);
    QStringList filters;
    filters << "pic_*.jpg";
    dir.setNameFilters(filters);
    dir.setSorting(QDir::Name);

    maxIndex = -1;
    foreach (QString f, dir.entryList())
    {
        QRegExp rx("pic_(\\d+)\\.jpg");
        if (rx.exactMatch(f))
        {
            int idx = rx.cap(1).toInt();
            if (idx > maxIndex)
                maxIndex = idx;
        }
    }

    if (maxIndex > -1)
    {
        currentIndex = maxIndex;
        QString nextFile = QString("%1/pic_%2.jpg").arg(dirPath).arg(currentIndex);
        ui->widget->setStyleSheet(QString("border-image: url(%1);").arg(nextFile));
    }
    else
    {
        // 无图片，清空显示
        currentIndex = -1;
        ui->widget->setStyleSheet("");
    }
}


