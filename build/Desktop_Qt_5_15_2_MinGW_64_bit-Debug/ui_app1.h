/********************************************************************************
** Form generated from reading UI file 'app1.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APP1_H
#define UI_APP1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_app1
{
public:
    QWidget *centralwidget;
    QPushButton *app1Btn;
    QPushButton *albumBtn;

    void setupUi(QMainWindow *app1)
    {
        if (app1->objectName().isEmpty())
            app1->setObjectName(QString::fromUtf8("app1"));
        app1->resize(800, 480);
        centralwidget = new QWidget(app1);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 9, 9);"));
        app1Btn = new QPushButton(centralwidget);
        app1Btn->setObjectName(QString::fromUtf8("app1Btn"));
        app1Btn->setGeometry(QRect(30, 30, 81, 81));
        QFont font;
        font.setPointSize(16);
        app1Btn->setFont(font);
        app1Btn->setStyleSheet(QString::fromUtf8("background-color: rgb(79, 255, 123);\n"
"color: rgb(0, 0, 0);\n"
"border-radius: 10px;\n"
""));
        app1Btn->setAutoDefault(false);
        albumBtn = new QPushButton(centralwidget);
        albumBtn->setObjectName(QString::fromUtf8("albumBtn"));
        albumBtn->setGeometry(QRect(140, 30, 81, 81));
        albumBtn->setFont(font);
        albumBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(119, 201, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-radius: 10px;"));
        app1->setCentralWidget(centralwidget);

        retranslateUi(app1);

        QMetaObject::connectSlotsByName(app1);
    } // setupUi

    void retranslateUi(QMainWindow *app1)
    {
        app1->setWindowTitle(QCoreApplication::translate("app1", "app1", nullptr));
        app1Btn->setText(QCoreApplication::translate("app1", "\347\205\247\347\233\270\346\234\272", nullptr));
        albumBtn->setText(QCoreApplication::translate("app1", "\347\233\270\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class app1: public Ui_app1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP1_H
