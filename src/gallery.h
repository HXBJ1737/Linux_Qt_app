#ifndef GALLERY_H
#define GALLERY_H
#include "ui_gallery.h"
#include <QMainWindow>

class gallery : public QMainWindow
{
    Q_OBJECT

public:
   gallery(QWidget *parent = nullptr);
    ~gallery();
   int maxIndex;
   int currentIndex;
   private slots:
   void on_backBtn_clicked();

    void on_lastBtn_clicked();

   void on_nextBtn_clicked();
 
   private:
    Ui::gallery *ui;
};

#endif // GALLERY_H
