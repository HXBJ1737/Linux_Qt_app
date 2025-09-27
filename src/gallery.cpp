#include "gallery.h"
#include "QDir"

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
        currentIndex = 0;
    }
     
    QString fileName = QString("./saveimg/pic_%1.jpg").arg(currentIndex);
    ui->widget->setStyleSheet(QString("border-image: url(%1);").arg(fileName));
        
    
}

void gallery::on_nextBtn_clicked()
{
    currentIndex++;
    if (currentIndex >maxIndex)
    {
        currentIndex = maxIndex;
    }
     
    QString fileName = QString("./saveimg/pic_%1.jpg").arg(currentIndex);
    ui->widget->setStyleSheet(QString("border-image: url(%1);").arg(fileName));
}
