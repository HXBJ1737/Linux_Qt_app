#include "app1.h"
#include "cam.h"
#include "gallery.h"
app1::app1(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_app1)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

}

app1::~app1()
{
    delete ui;
}
void app1::on_app1Btn_clicked()
{
    cam *c = new cam;
    c->show();
}

void app1::on_albumBtn_clicked()
{
    gallery *g = new gallery;
    g->show();
}