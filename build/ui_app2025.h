/********************************************************************************
** Form generated from reading UI file 'app2025.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP2025_H
#define UI_APP2025_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_app2025
{
public:
    QWidget *centralwidget;
    QPushButton *app1_btn;
    QPushButton *app2_btn;
    QPushButton *close_btn;
    QPushButton *app3_btn;

    void setupUi(QMainWindow *app2025)
    {
        if (app2025->objectName().isEmpty())
            app2025->setObjectName(QString::fromUtf8("app2025"));
        app2025->resize(1280, 720);
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(14);
        app2025->setFont(font);
        centralwidget = new QWidget(app2025);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(800, 480));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font1.setPointSize(14);
        centralwidget->setFont(font1);
        centralwidget->setStyleSheet(QString::fromUtf8("#centralwidget{\n"
"	 border-image: url(:/src/img/b.jpg);\n"
"\n"
"}\n"
"\n"
"\n"
"\n"
""));
        app1_btn = new QPushButton(centralwidget);
        app1_btn->setObjectName(QString::fromUtf8("app1_btn"));
        app1_btn->setGeometry(QRect(40, 60, 100, 100));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font2.setPointSize(16);
        font2.setBold(false);
        font2.setItalic(false);
        app1_btn->setFont(font2);
        app1_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(47, 255, 89);\n"
"border-radius: 10px;"));
        app1_btn->setIconSize(QSize(32, 32));
        app1_btn->setAutoDefault(false);
        app2_btn = new QPushButton(centralwidget);
        app2_btn->setObjectName(QString::fromUtf8("app2_btn"));
        app2_btn->setGeometry(QRect(190, 60, 100, 100));
        app2_btn->setFont(font1);
        app2_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(29, 244, 255);\n"
"border-radius: 10px;"));
        close_btn = new QPushButton(centralwidget);
        close_btn->setObjectName(QString::fromUtf8("close_btn"));
        close_btn->setGeometry(QRect(1130, 60, 100, 100));
        close_btn->setFont(font1);
        close_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 0, 0);\n"
"border-radius: 10px;"));
        app3_btn = new QPushButton(centralwidget);
        app3_btn->setObjectName(QString::fromUtf8("app3_btn"));
        app3_btn->setGeometry(QRect(340, 60, 100, 100));
        app3_btn->setFont(font1);
        app3_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(151, 255, 194);\n"
"border-radius: 10px;"));
        app2025->setCentralWidget(centralwidget);

        retranslateUi(app2025);

        QMetaObject::connectSlotsByName(app2025);
    } // setupUi

    void retranslateUi(QMainWindow *app2025)
    {
        app2025->setWindowTitle(QCoreApplication::translate("app2025", "app2025", nullptr));
        app1_btn->setText(QCoreApplication::translate("app2025", "\347\205\247\347\233\270\346\234\272", nullptr));
        app2_btn->setText(QCoreApplication::translate("app2025", "\347\233\270\345\206\214", nullptr));
        close_btn->setText(QCoreApplication::translate("app2025", "\351\200\200\345\207\272", nullptr));
        app3_btn->setText(QCoreApplication::translate("app2025", "APP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class app2025: public Ui_app2025 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP2025_H
