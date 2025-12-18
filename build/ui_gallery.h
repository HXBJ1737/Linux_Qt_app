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
#include <QtWidgets/QRadioButton>
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
    QPushButton *rm_Btn;
    QRadioButton *radioButton;

    void setupUi(QMainWindow *gallery)
    {
        if (gallery->objectName().isEmpty())
            gallery->setObjectName(QString::fromUtf8("gallery"));
        gallery->resize(1280, 720);
        QFont font;
        font.setPointSize(14);
        gallery->setFont(font);
        gallery->setStyleSheet(QString::fromUtf8("background-color: rgb(29, 29, 29);\n"
"color: rgb(255, 255, 255);"));
        centralwidget = new QWidget(gallery);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setFont(font);
        centralwidget->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
""));
        backBtn = new QPushButton(centralwidget);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));
        backBtn->setGeometry(QRect(1140, 30, 121, 81));
        backBtn->setFont(font);
        backBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(68, 68, 68);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(160, 0, 960, 720));
        widget->setFont(font);
        lastBtn = new QPushButton(centralwidget);
        lastBtn->setObjectName(QString::fromUtf8("lastBtn"));
        lastBtn->setGeometry(QRect(39, 330, 80, 150));
        QFont font1;
        font1.setPointSize(16);
        lastBtn->setFont(font1);
        lastBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(68, 68, 68);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        nextBtn = new QPushButton(centralwidget);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
        nextBtn->setGeometry(QRect(1150, 330, 80, 150));
        nextBtn->setFont(font1);
        nextBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(68, 68, 68);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        rm_Btn = new QPushButton(centralwidget);
        rm_Btn->setObjectName(QString::fromUtf8("rm_Btn"));
        rm_Btn->setGeometry(QRect(1140, 140, 121, 81));
        rm_Btn->setFont(font);
        rm_Btn->setStyleSheet(QString::fromUtf8("background-color: rgb(148, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(1140, 540, 121, 91));
        radioButton->setFont(font);
        radioButton->setStyleSheet(QString::fromUtf8("background-color: rgb(115, 176, 174);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        radioButton->setIconSize(QSize(32, 32));
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
        rm_Btn->setText(QCoreApplication::translate("gallery", "\345\210\240\351\231\244", nullptr));
        radioButton->setText(QCoreApplication::translate("gallery", "\346\230\276\347\244\272\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gallery: public Ui_gallery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GALLERY_H
