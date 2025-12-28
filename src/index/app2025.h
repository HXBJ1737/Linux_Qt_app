#pragma once
#include "ui_app2025.h"
#include <QMainWindow>
#include <QProcess>
#include <QMessageBox>
class app2025 : public QMainWindow
{
    Q_OBJECT

public:
    app2025(QWidget *parent = nullptr);
    ~app2025();

private slots:
    void on_close_btn_clicked();

    void on_app1_btn_clicked();

    void on_app2_btn_clicked();

    void on_app3_btn_clicked();

    void on_app4_btn_clicked();

    void updateTimeLabel();
    void on_poweroff_pushButton_clicked();

    void on_reboot_pushButton_clicked();

    void on_test_pushButton_clicked();

private:
    Ui_app2025 *ui;
    QProcess *process;
    bool m_dragging = false;
    QPoint m_dragPosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};
