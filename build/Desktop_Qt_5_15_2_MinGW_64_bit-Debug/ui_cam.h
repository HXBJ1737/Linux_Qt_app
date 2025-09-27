/********************************************************************************
** Form generated from reading UI file 'cam.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAM_H
#define UI_CAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cam
{
public:
    QWidget *centralwidget;
    QPushButton *openbtn;
    QWidget *widget;
    QPushButton *screenshotbtn;
    QPushButton *picbtn;
    QPushButton *camBackBtn;

    void setupUi(QMainWindow *cam)
    {
        if (cam->objectName().isEmpty())
            cam->setObjectName(QString::fromUtf8("cam"));
        cam->resize(800, 480);
        centralwidget = new QWidget(cam);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(9, 9, 9);"));
        openbtn = new QPushButton(centralwidget);
        openbtn->setObjectName(QString::fromUtf8("openbtn"));
        openbtn->setGeometry(QRect(670, 110, 101, 51));
        QFont font;
        font.setPointSize(12);
        openbtn->setFont(font);
        openbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(195, 188, 230);\n"
"color: rgb(22, 37, 63);"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(5, 5, 624, 468));
        QFont font1;
        font1.setPointSize(9);
        widget->setFont(font1);
        screenshotbtn = new QPushButton(centralwidget);
        screenshotbtn->setObjectName(QString::fromUtf8("screenshotbtn"));
        screenshotbtn->setGeometry(QRect(680, 200, 80, 80));
        screenshotbtn->setFont(font);
        screenshotbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(195, 188, 230);\n"
"color: rgb(22, 37, 63);\n"
"border-radius:40px;"));
        picbtn = new QPushButton(centralwidget);
        picbtn->setObjectName(QString::fromUtf8("picbtn"));
        picbtn->setGeometry(QRect(660, 340, 128, 96));
        picbtn->setIconSize(QSize(128, 96));
        camBackBtn = new QPushButton(centralwidget);
        camBackBtn->setObjectName(QString::fromUtf8("camBackBtn"));
        camBackBtn->setGeometry(QRect(670, 20, 101, 51));
        camBackBtn->setFont(font);
        camBackBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(195, 188, 230);\n"
"color: rgb(22, 37, 63);"));
        cam->setCentralWidget(centralwidget);

        retranslateUi(cam);

        QMetaObject::connectSlotsByName(cam);
    } // setupUi

    void retranslateUi(QMainWindow *cam)
    {
        cam->setWindowTitle(QCoreApplication::translate("cam", "cam", nullptr));
        openbtn->setText(QCoreApplication::translate("cam", "\345\210\267\346\226\260", nullptr));
        screenshotbtn->setText(QCoreApplication::translate("cam", "\346\213\215\347\205\247", nullptr));
        picbtn->setText(QString());
        camBackBtn->setText(QCoreApplication::translate("cam", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cam: public Ui_cam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAM_H
