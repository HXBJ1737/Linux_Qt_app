/********************************************************************************
** Form generated from reading UI file 'yolo_app.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YOLO_APP_H
#define UI_YOLO_APP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_yolo_app
{
public:
    QWidget *centralwidget;
    QPushButton *back_btn;
    QWidget *widget;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_fps;
    QLabel *label_info;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *yolo_app)
    {
        if (yolo_app->objectName().isEmpty())
            yolo_app->setObjectName(QString::fromUtf8("yolo_app"));
        yolo_app->resize(1280, 720);
        yolo_app->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        centralwidget = new QWidget(yolo_app);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        back_btn = new QPushButton(centralwidget);
        back_btn->setObjectName(QString::fromUtf8("back_btn"));
        back_btn->setGeometry(QRect(1140, 10, 121, 71));
        QFont font;
        font.setPointSize(16);
        back_btn->setFont(font);
        back_btn->setStyleSheet(QString::fromUtf8("background-color: rgb(148, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 960, 720));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(960, 30, 131, 41));
        QFont font1;
        font1.setPointSize(14);
        comboBox->setFont(font1);
        comboBox->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(970, 0, 91, 21));
        QFont font2;
        font2.setPointSize(12);
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_fps = new QLabel(centralwidget);
        label_fps->setObjectName(QString::fromUtf8("label_fps"));
        label_fps->setGeometry(QRect(970, 100, 141, 31));
        label_fps->setFont(font2);
        label_fps->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_info = new QLabel(centralwidget);
        label_info->setObjectName(QString::fromUtf8("label_info"));
        label_info->setGeometry(QRect(970, 180, 291, 481));
        label_info->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        yolo_app->setCentralWidget(centralwidget);
        menubar = new QMenuBar(yolo_app);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 20));
        yolo_app->setMenuBar(menubar);
        statusbar = new QStatusBar(yolo_app);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        yolo_app->setStatusBar(statusbar);

        retranslateUi(yolo_app);

        QMetaObject::connectSlotsByName(yolo_app);
    } // setupUi

    void retranslateUi(QMainWindow *yolo_app)
    {
        yolo_app->setWindowTitle(QCoreApplication::translate("yolo_app", "MainWindow", nullptr));
        back_btn->setText(QCoreApplication::translate("yolo_app", "\350\277\224\345\233\236", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("yolo_app", "640 x 480", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("yolo_app", "960 x 720", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("yolo_app", "1280 x 960", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("yolo_app", "1920 x 1440", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("yolo_app", "2592 x 1944", nullptr));

        label->setText(QCoreApplication::translate("yolo_app", "\350\276\223\345\205\245\345\210\206\350\276\250\347\216\207", nullptr));
        label_fps->setText(QCoreApplication::translate("yolo_app", "0fps", nullptr));
        label_info->setText(QCoreApplication::translate("yolo_app", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class yolo_app: public Ui_yolo_app {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YOLO_APP_H
