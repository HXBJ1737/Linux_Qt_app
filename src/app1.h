#pragma once
#include "ui_app1.h"
#include <QMainWindow>

class app1 : public QMainWindow {
    Q_OBJECT
    
public:
    app1(QWidget* parent = nullptr);
    ~app1();

private slots:
    void on_app1Btn_clicked();

    void on_albumBtn_clicked();

private:
    Ui_app1* ui;
};
