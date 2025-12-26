#include "index/app2025.h"

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#pragma comment(lib, "user32.lib")


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString PROJECT_ROOT = QDir::currentPath();
    qDebug() << "Current Path:" << PROJECT_ROOT;
    qputenv("PROJECT_ROOT", PROJECT_ROOT.toUtf8());

    app2025 w;
    w.show();
    return a.exec();
}