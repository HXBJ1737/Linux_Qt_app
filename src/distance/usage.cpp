#include "usage.h"
#include "ui_usage.h"

usage::usage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::usage)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

usage::~usage()
{
    delete ui;
}

void usage::on_backBtn_clicked()
{
    this->close();
}

