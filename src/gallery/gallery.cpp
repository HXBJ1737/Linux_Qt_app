#include "gallery.h"
#include "QDir"
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include "src/cam/cam.h"

extern bool cam_ui_open;
gallery::gallery(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::gallery)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    QByteArray ba = qgetenv("PROJECT_ROOT");
    QString projectRoot = ba.isEmpty() ? QString() : QString::fromUtf8(ba);
    QDir::setCurrent(projectRoot);

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
        // QString fileName = QString("./saveimg/pic_%1.jpg").arg(maxIndex);
        // ui->widget->setStyleSheet(QString("border-image: url(%1);").arg(fileName));
        // 使用 QLabel 作为图片显示容器
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
            "min-width: 480px;" // 最小宽度
            "max-width: 480px;" // 最大宽度
            "min-height: 70px;" // 最小高度
            "max-height: 70px;" // 最大高度
        );
        pathLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
        pathLabel->setWordWrap(true);
        pathLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        pathLabel->setMargin(6);
        pathLabel->setVisible(ui->radioButton->isChecked());
        // 加载并显示图片（封装的函数会同时更新 pathLabel）
        QString fileName = QString("./saveimg/pic_%1.jpg").arg(maxIndex);
        showImage(fileName);
        currentIndex = maxIndex;
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

    QString info = QString("路径: %1\n大小: %2 x %3  %4 ").arg(absPath).arg(origW).arg(origH).arg(sizeStr);

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

    QString fileName = QString("./saveimg/pic_%1.jpg").arg(currentIndex);
    showImage(fileName);
}

void gallery::on_nextBtn_clicked()
{
    currentIndex++;
    if (currentIndex > maxIndex)
    {
        currentIndex = 0;
    }

    QString fileName = QString("./saveimg/pic_%1.jpg").arg(currentIndex);
    showImage(fileName);
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
        QString fileName = QString("./saveimg/pic_%1.jpg").arg(currentIndex);
        showImage(fileName);
    }
    else
    {
        // 无图片，清空显示
        currentIndex = -1;
        ui->widget->setStyleSheet("");
    }
}

void gallery::on_radioButton_clicked(bool checked)
{
    if (pathLabel)
        pathLabel->setVisible(checked);
}
