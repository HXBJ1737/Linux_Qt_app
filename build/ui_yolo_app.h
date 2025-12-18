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
    } // retranslateUi

};

namespace Ui {
    class yolo_app: public Ui_yolo_app {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YOLO_APP_H
