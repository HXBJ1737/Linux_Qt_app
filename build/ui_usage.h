/********************************************************************************
** Form generated from reading UI file 'usage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USAGE_H
#define UI_USAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_usage
{
public:
    QPushButton *backBtn;
    QLabel *label;

    void setupUi(QWidget *usage)
    {
        if (usage->objectName().isEmpty())
            usage->setObjectName(QString::fromUtf8("usage"));
        usage->resize(1280, 720);
        usage->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 200);"));
        backBtn = new QPushButton(usage);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));
        backBtn->setGeometry(QRect(1130, 20, 131, 71));
        QFont font;
        font.setPointSize(15);
        backBtn->setFont(font);
        backBtn->setStyleSheet(QString::fromUtf8("background-color:rgb(220, 0, 0) ;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        label = new QLabel(usage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 10, 721, 161));
        QFont font1;
        font1.setPointSize(14);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        retranslateUi(usage);

        QMetaObject::connectSlotsByName(usage);
    } // setupUi

    void retranslateUi(QWidget *usage)
    {
        usage->setWindowTitle(QCoreApplication::translate("usage", "Form", nullptr));
        backBtn->setText(QCoreApplication::translate("usage", "\350\277\224\345\233\236", nullptr));
        label->setText(QCoreApplication::translate("usage", "<html><head/><body><p>1.\346\240\241\346\255\243\345\203\217\347\264\240\347\204\246\350\267\235\357\274\214\345\203\217\347\264\240\347\204\246\350\267\235\351\232\217\345\210\206\350\276\250\347\216\207\347\272\277\346\200\247\345\217\230\346\215\242\357\274\233</p><p>2.\347\233\256\346\240\207\345\205\210\351\252\214\357\274\232\351\234\200\350\246\201\347\233\256\346\240\207\351\253\230\345\272\246\357\274\233</p><p>3.\347\233\270\346\234\272\345\205\210\351\252\214\357\274\232\351\234\200\350\246\201\347\233\270\346\234\272\351\253\230\345\272\246\345\222\214\347\233\270\346\234\272\350\247\222\345\272\246\357\274\214\346\255\244\345\244\204\344\277\235\346\214\2010\345\272\246\357\274\214\345\215\263\345\205\211\350\275\264\345\271\263\350\241\214\345\234\260\351\235\242\343\200\202</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class usage: public Ui_usage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USAGE_H
