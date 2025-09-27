/********************************************************************************
** Form generated from reading UI file 'gallery.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GALLERY_H
#define UI_GALLERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gallery
{
public:
    QWidget *centralwidget;
    QPushButton *backBtn;
    QWidget *widget;
    QPushButton *lastBtn;
    QPushButton *nextBtn;

    void setupUi(QMainWindow *gallery)
    {
        if (gallery->objectName().isEmpty())
            gallery->setObjectName(QString::fromUtf8("gallery"));
        gallery->resize(800, 480);
        centralwidget = new QWidget(gallery);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        backBtn = new QPushButton(centralwidget);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));
        backBtn->setGeometry(QRect(710, 0, 91, 51));
        QFont font;
        font.setPointSize(14);
        backBtn->setFont(font);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(70, 0, 640, 480));
        lastBtn = new QPushButton(centralwidget);
        lastBtn->setObjectName(QString::fromUtf8("lastBtn"));
        lastBtn->setGeometry(QRect(0, 180, 61, 71));
        QFont font1;
        font1.setPointSize(16);
        lastBtn->setFont(font1);
        nextBtn = new QPushButton(centralwidget);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
        nextBtn->setGeometry(QRect(720, 180, 61, 71));
        nextBtn->setFont(font1);
        gallery->setCentralWidget(centralwidget);

        retranslateUi(gallery);

        QMetaObject::connectSlotsByName(gallery);
    } // setupUi

    void retranslateUi(QMainWindow *gallery)
    {
        gallery->setWindowTitle(QCoreApplication::translate("gallery", "MainWindow", nullptr));
        backBtn->setText(QCoreApplication::translate("gallery", "\350\277\224\345\233\236", nullptr));
        lastBtn->setText(QCoreApplication::translate("gallery", "<", nullptr));
        nextBtn->setText(QCoreApplication::translate("gallery", ">", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gallery: public Ui_gallery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GALLERY_H
