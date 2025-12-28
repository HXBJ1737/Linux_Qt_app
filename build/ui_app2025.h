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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_app2025
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *time_label;
    QHBoxLayout *horizontalLayout;
    QPushButton *app1_btn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *app2_btn;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *app3_btn;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *app4_btn;
    QSpacerItem *horizontalSpacer;
    QPushButton *close_btn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *app2025)
    {
        if (app2025->objectName().isEmpty())
            app2025->setObjectName(QString::fromUtf8("app2025"));
        app2025->resize(1280, 720);
        app2025->setMinimumSize(QSize(800, 480));
        app2025->setMaximumSize(QSize(1280, 720));
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
"	border-image: url(:/img/b.jpg);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_2, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        time_label = new QLabel(centralwidget);
        time_label->setObjectName(QString::fromUtf8("time_label"));
        time_label->setMaximumSize(QSize(400, 100));
        QFont font2;
        font2.setPointSize(36);
        time_label->setFont(font2);
        time_label->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(time_label);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 6, -1, 10);
        app1_btn = new QPushButton(centralwidget);
        app1_btn->setObjectName(QString::fromUtf8("app1_btn"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(app1_btn->sizePolicy().hasHeightForWidth());
        app1_btn->setSizePolicy(sizePolicy);
        app1_btn->setMinimumSize(QSize(100, 100));
        app1_btn->setMaximumSize(QSize(100, 100));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font3.setPointSize(18);
        font3.setBold(false);
        font3.setItalic(false);
        app1_btn->setFont(font3);
        app1_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(47, 255, 89);\n"
"border-radius: 10px;"));
        app1_btn->setIconSize(QSize(32, 32));
        app1_btn->setAutoDefault(false);

        horizontalLayout->addWidget(app1_btn);

        horizontalSpacer_3 = new QSpacerItem(30, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        app2_btn = new QPushButton(centralwidget);
        app2_btn->setObjectName(QString::fromUtf8("app2_btn"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(app2_btn->sizePolicy().hasHeightForWidth());
        app2_btn->setSizePolicy(sizePolicy1);
        app2_btn->setMinimumSize(QSize(100, 100));
        app2_btn->setMaximumSize(QSize(100, 100));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font4.setPointSize(18);
        app2_btn->setFont(font4);
        app2_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(29, 244, 255);\n"
"border-radius: 10px;"));

        horizontalLayout->addWidget(app2_btn);

        horizontalSpacer_4 = new QSpacerItem(30, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        app3_btn = new QPushButton(centralwidget);
        app3_btn->setObjectName(QString::fromUtf8("app3_btn"));
        sizePolicy1.setHeightForWidth(app3_btn->sizePolicy().hasHeightForWidth());
        app3_btn->setSizePolicy(sizePolicy1);
        app3_btn->setMinimumSize(QSize(100, 100));
        app3_btn->setMaximumSize(QSize(100, 100));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font5.setPointSize(16);
        app3_btn->setFont(font5);
        app3_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(151, 255, 194);\n"
"border-radius: 10px;"));

        horizontalLayout->addWidget(app3_btn);

        horizontalSpacer_5 = new QSpacerItem(30, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        app4_btn = new QPushButton(centralwidget);
        app4_btn->setObjectName(QString::fromUtf8("app4_btn"));
        sizePolicy1.setHeightForWidth(app4_btn->sizePolicy().hasHeightForWidth());
        app4_btn->setSizePolicy(sizePolicy1);
        app4_btn->setMinimumSize(QSize(100, 100));
        app4_btn->setMaximumSize(QSize(100, 100));
        app4_btn->setFont(font5);
        app4_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(151, 255, 194);\n"
"border-radius: 10px;"));

        horizontalLayout->addWidget(app4_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        close_btn = new QPushButton(centralwidget);
        close_btn->setObjectName(QString::fromUtf8("close_btn"));
        sizePolicy1.setHeightForWidth(close_btn->sizePolicy().hasHeightForWidth());
        close_btn->setSizePolicy(sizePolicy1);
        close_btn->setMinimumSize(QSize(100, 100));
        close_btn->setMaximumSize(QSize(100, 100));
        close_btn->setFont(font1);
        close_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 0, 0);\n"
"border-radius: 10px;"));

        horizontalLayout->addWidget(close_btn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        app2025->setCentralWidget(centralwidget);

        retranslateUi(app2025);

        QMetaObject::connectSlotsByName(app2025);
    } // setupUi

    void retranslateUi(QMainWindow *app2025)
    {
        app2025->setWindowTitle(QCoreApplication::translate("app2025", "app2025", nullptr));
        time_label->setText(QCoreApplication::translate("app2025", "00:00:00", nullptr));
        app1_btn->setText(QCoreApplication::translate("app2025", "\347\205\247\347\233\270\346\234\272", nullptr));
        app2_btn->setText(QCoreApplication::translate("app2025", "\347\233\270\345\206\214", nullptr));
        app3_btn->setText(QCoreApplication::translate("app2025", "\346\255\243\347\202\271\345\216\237\345\255\220\n"
"APP", nullptr));
        app4_btn->setText(QCoreApplication::translate("app2025", "YOLO11", nullptr));
        close_btn->setText(QCoreApplication::translate("app2025", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class app2025: public Ui_app2025 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APP2025_H
