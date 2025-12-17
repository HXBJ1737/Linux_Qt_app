#pragma once
#include "ui_app2025.h"
#include <QMainWindow>
#include <QProcess>
class app2025 : public QMainWindow {
    Q_OBJECT
    
public:
    app2025(QWidget* parent = nullptr);
    ~app2025();

private slots:
    void on_close_btn_clicked();

    void on_app1_btn_clicked();

    void on_app2_btn_clicked();

    void on_app3_btn_clicked();

    void on_app4_btn_clicked();

private:
    Ui_app2025* ui;
    QProcess *process;
};
