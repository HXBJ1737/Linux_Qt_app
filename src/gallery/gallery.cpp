#include "gallery.h"
#include "QDir"
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include "src/cam/cam.h"
#include <QImageReader>
extern bool cam_ui_open;
gallery::gallery(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::gallery)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    QByteArray ba = qgetenv("PROJECT_ROOT");
    QString projectRoot = ba.isEmpty() ? QString() : QString::fromUtf8(ba);
    QDir::setCurrent(projectRoot);

    QDir dir("./img");
    if (!dir.exists())
        dir.mkpath(".");

    // 使用所有受支持的图片格式作为过滤器
    QStringList filters;
    for (const QByteArray &fmt : QImageReader::supportedImageFormats())
        filters << "*." + QString(fmt).toLower();

    // 扫描两个目录：./img 和 ./，收集绝对路径，去重并排序
    QStringList searchDirs = {"./img", "./"};
    QSet<QString> seen;
    imageFiles.clear();
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
                imageFiles.append(abs); 
            }
        }
    }
    // 可选按文件名排序（如果需要按目录顺序可调整）
    std::sort(imageFiles.begin(), imageFiles.end(), [](const QString &a, const QString &b)
              { return QFileInfo(a).fileName().toLower() < QFileInfo(b).fileName().toLower(); });

    maxIndex = imageFiles.count() - 1;
    currentIndex = -1;
    if (maxIndex > -1)
    {
        imageLabel = new QLabel(ui->widget);
        imageLabel->setAlignment(Qt::AlignCenter);

        // 显示路径的 QLabel，位于 widget 左下角（初始根据 radioButton 状态决定可见性）
        pathLabel = new QLabel(ui->widget);

        pathLabel->setStyleSheet(
            "color: white;"
            "background-color: rgba(41, 40, 40, 128);"
            "padding: 2px;"
            "border-radius: 15px;"
            "font-size: 20px;"
            "min-width: 480px;"  // 最小宽度
            "max-width: 500px;"  // 最大宽度
            "min-height: 70px;"  // 最小高度
            "max-height: 200px;" // 最大高度
        );
        pathLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
        pathLabel->setWordWrap(true);
        pathLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        pathLabel->setMargin(6);
        pathLabel->setVisible(ui->radioButton->isChecked());
        // 加载并显示图片（封装的函数会同时更新 pathLabel）
        // 初始显示最后一张
        currentIndex = maxIndex;
        QString filePath = imageFiles.at(currentIndex);
        showImage(filePath);
    }
}
void gallery::showImage(const QString &relPath)
{
    QFileInfo fi(relPath);
    QString absPath = fi.absoluteFilePath();
    QPixmap pixmap(relPath);
    int origW = 0, origH = 0;
    if (!pixmap.isNull())
    {
        origW = pixmap.width();
        origH = pixmap.height();

        pixmap = pixmap.scaled(ui->widget->size(),
                               Qt::KeepAspectRatio,
                               Qt::SmoothTransformation);
        imageLabel->setPixmap(pixmap);
        imageLabel->resize(pixmap.size());
        imageLabel->move((ui->widget->width() - imageLabel->width()) / 2,
                         (ui->widget->height() - imageLabel->height()) / 2);
    }
    else
    {
        imageLabel->clear();
    }

    qint64 fsize = fi.size();
    QString sizeStr;
    if (fsize < 1024)
        sizeStr = QString("%1 B").arg(fsize);
    else if (fsize < 1024 * 1024)
        sizeStr = QString("%1 KB").arg(fsize / 1024);
    else
        sizeStr = QString("%1 MB").arg((double)fsize / 1024.0 / 1024.0, 0, 'f', 2);

    QDateTime mtime = fi.lastModified();
    QString timeStr = mtime.toString("yyyy-MM-dd HH:mm:ss");

    QString info = QString("路径: %1\n分辨率: %2 x %3  大小: %4\n时间: %5")
                       .arg(absPath)
                       .arg(origW)
                       .arg(origH)
                       .arg(sizeStr)
                       .arg(timeStr);

    pathLabel->setText(info);
    pathLabel->adjustSize();
    int px = 5;
    int py = ui->widget->height() - pathLabel->height() - 5;
    pathLabel->move(px, py);
    pathLabel->setVisible(ui->radioButton->isChecked());
}
gallery::~gallery()
{

    delete ui;
}

void gallery::on_backBtn_clicked()
{
    if (!cam_ui_open)
        this->close();
    else
    {
        cam_ui_open = false;
        cam *c = new cam;
        c->show();
        this - close();
    }
}

void gallery::on_lastBtn_clicked()
{
    currentIndex--;
    if (currentIndex < 0)
    {
        currentIndex = maxIndex;
    }
    QString filePath = imageFiles.at(currentIndex);
    showImage(filePath);
}

void gallery::on_nextBtn_clicked()
{
    currentIndex++;
    if (currentIndex > maxIndex)
    {
        currentIndex = 0;
    }

    QString filePath = imageFiles.at(currentIndex);
    showImage(filePath);
}

void gallery::on_rm_Btn_clicked()
{

    if (currentIndex < 0)
        return;

    QString filePath = imageFiles.at(currentIndex);

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

    QStringList filters2;
    for (const QByteArray &fmt : QImageReader::supportedImageFormats())
        filters2 << "*." + QString(fmt).toLower();

    QStringList searchDirs2 = {"./img", "./"};
    QSet<QString> seen2;
    imageFiles.clear();
    for (const QString &dpath : searchDirs2)
    {
        QDir d(dpath);
        if (!d.exists())
            continue;
        d.setNameFilters(filters2);
        d.setSorting(QDir::Name);
        QStringList entries = d.entryList(QDir::Files, QDir::Name);
        for (const QString &ename : entries)
        {
            QString abs = d.absoluteFilePath(ename);
            if (!seen2.contains(abs))
            {
                seen2.insert(abs);
                imageFiles.append(abs);
            }
        }
    }
    std::sort(imageFiles.begin(), imageFiles.end(), [](const QString &a, const QString &b)
              { return QFileInfo(a).fileName().toLower() < QFileInfo(b).fileName().toLower(); });
    maxIndex = imageFiles.count() - 1;

    if (maxIndex > -1)
    {
        if (currentIndex > maxIndex)
            currentIndex = maxIndex;
        QString nextPath = imageFiles.at(currentIndex);
        showImage(nextPath);
    }
    else
    {
        // 无图片，清空显示
        currentIndex = -1;
        ui->widget->setStyleSheet("");
        imageLabel->clear();
        pathLabel->clear();
    }
}

void gallery::on_radioButton_clicked(bool checked)
{
    if (pathLabel)
        pathLabel->setVisible(checked);
}
