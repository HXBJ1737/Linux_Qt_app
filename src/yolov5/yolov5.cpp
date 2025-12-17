#include "yolov5.h"
#include "ui_yolov5.h"

yolov5::yolov5(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::yolov5)
{
    ui->setupUi(this);
}

yolov5::~yolov5()
{
    delete ui;
}

void yolov5::on_back_btn_clicked()
{
    this->close();
}

