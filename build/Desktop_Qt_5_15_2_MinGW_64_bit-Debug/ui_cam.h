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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cam
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QPushButton *camBackBtn;
    QPushButton *screenshotbtn;
    QPushButton *picbtn;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_fps;

    void setupUi(QMainWindow *cam)
    {
        if (cam->objectName().isEmpty())
            cam->setObjectName(QString::fromUtf8("cam"));
        cam->resize(1280, 720);
        cam->setMinimumSize(QSize(800, 480));
        cam->setMaximumSize(QSize(1280, 720));
        cam->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(9, 9, 9);"));
        centralwidget = new QWidget(cam);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 960, 720));
        widget->setMinimumSize(QSize(640, 480));
        widget->setMaximumSize(QSize(1280, 720));
        QFont font;
        font.setPointSize(9);
        widget->setFont(font);
        widget->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(9, 9, 9);"));
        camBackBtn = new QPushButton(centralwidget);
        camBackBtn->setObjectName(QString::fromUtf8("camBackBtn"));
        camBackBtn->setGeometry(QRect(1140, 30, 100, 100));
        QFont font1;
        font1.setPointSize(12);
        camBackBtn->setFont(font1);
        camBackBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(121, 28, 0);\n"
"border-radius: 50px;"));
        camBackBtn->setIconSize(QSize(50, 50));
        screenshotbtn = new QPushButton(centralwidget);
        screenshotbtn->setObjectName(QString::fromUtf8("screenshotbtn"));
        screenshotbtn->setGeometry(QRect(1140, 330, 100, 100));
        screenshotbtn->setFont(font1);
        screenshotbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(4, 90, 100);\n"
"border-radius: 50px;\n"
"\n"
""));
        screenshotbtn->setIconSize(QSize(50, 50));
        picbtn = new QPushButton(centralwidget);
        picbtn->setObjectName(QString::fromUtf8("picbtn"));
        picbtn->setGeometry(QRect(990, 520, 240, 180));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(picbtn->sizePolicy().hasHeightForWidth());
        picbtn->setSizePolicy(sizePolicy);
        picbtn->setMinimumSize(QSize(240, 180));
        picbtn->setStyleSheet(QString::fromUtf8(""));
        picbtn->setIconSize(QSize(240, 180));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(970, 50, 141, 51));
        QFont font2;
        font2.setPointSize(14);
        comboBox->setFont(font2);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(970, 20, 71, 21));
        label->setFont(font2);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(970, 150, 51, 21));
        label_2->setFont(font2);
        label_fps = new QLabel(centralwidget);
        label_fps->setObjectName(QString::fromUtf8("label_fps"));
        label_fps->setGeometry(QRect(1040, 150, 101, 21));
        label_fps->setFont(font1);
        cam->setCentralWidget(centralwidget);

        retranslateUi(cam);

        QMetaObject::connectSlotsByName(cam);
    } // setupUi

    void retranslateUi(QMainWindow *cam)
    {
        cam->setWindowTitle(QCoreApplication::translate("cam", "cam", nullptr));
        camBackBtn->setText(QCoreApplication::translate("cam", "\351\200\200\345\207\272", nullptr));
        screenshotbtn->setText(QCoreApplication::translate("cam", "\346\213\215\347\205\247", nullptr));
        picbtn->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("cam", "2592 x 1944", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("cam", "1980 x 1440", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("cam", "1280 x960", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("cam", "960 x 720", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("cam", "640 x 480", nullptr));

        label->setText(QCoreApplication::translate("cam", "\345\210\206\350\276\250\347\216\207", nullptr));
        label_2->setText(QCoreApplication::translate("cam", "\345\270\247\347\216\207", nullptr));
        label_fps->setText(QCoreApplication::translate("cam", "0 fps", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cam: public Ui_cam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAM_H
