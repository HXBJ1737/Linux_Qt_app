#ifndef YOLOV5_H
#define YOLOV5_H

#include <QMainWindow>

namespace Ui {
class yolov5;
}

class yolov5 : public QMainWindow
{
    Q_OBJECT

public:
    explicit yolov5(QWidget *parent = nullptr);
    ~yolov5();

private slots:
    void on_back_btn_clicked();

private:
    Ui::yolov5 *ui;
};

#endif // YOLOV5_H
