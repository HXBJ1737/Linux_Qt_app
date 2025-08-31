#include "app1.h"

#include <QApplication>
#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    app1 w;
    w.show();
    return a.exec();
}