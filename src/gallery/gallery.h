#ifndef GALLERY_H
#define GALLERY_H
#include "ui_gallery.h"
#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QStringList>
class gallery : public QMainWindow
{
    Q_OBJECT

public:
    gallery(QWidget *parent = nullptr);
    ~gallery();


private slots:
    void on_backBtn_clicked();

    void on_lastBtn_clicked();

    void on_nextBtn_clicked();

    void on_rm_Btn_clicked();

    void on_radioButton_clicked(bool checked);

private:
    Ui::gallery *ui;
    QLabel *imageLabel = nullptr; // 用于显示图片
    QLabel *pathLabel = nullptr;  // 左下角显示路径/信息
    QStringList imageFiles; // 新增：目录中所有图片文件列表
    // 索引管理
    int maxIndex = -1;
    int currentIndex = -1;
    void showImage(const QString &relPath);
};

#endif // GALLERY_H
