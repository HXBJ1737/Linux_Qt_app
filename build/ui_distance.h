/********************************************************************************
** Form generated from reading UI file 'distance.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCE_H
#define UI_DISTANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_distance
{
public:
    QWidget *widget;
    QPushButton *back_btn;
    QLabel *label_res;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_1;
    QLabel *label_dis;
    QPushButton *back_btn_2;
    QPushButton *back_btn_3;
    QLabel *label_fps;
    QLabel *label_info;
    QPushButton *flip_btn;
    QLabel *label_f;
    QLabel *label_5;
    QComboBox *comboBox_3;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox_4;
    QLabel *label_7;
    QPushButton *usage_btn;
    QLabel *label;
    QComboBox *comboBox_5;
    QLabel *label_8;
    QComboBox *comboBox_6;
    QLabel *label_9;
    QComboBox *comboBox_7;
    QPushButton *scrshotBtn;
    QPushButton *zBtn;
    QPushButton *xBtn;
    QPushButton *show1Btn;
    QLabel *label_dis_2;
    QPushButton *filterBtn;

    void setupUi(QWidget *distance)
    {
        if (distance->objectName().isEmpty())
            distance->setObjectName(QString::fromUtf8("distance"));
        distance->resize(1280, 720);
        distance->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        widget = new QWidget(distance);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 640, 480));
        back_btn = new QPushButton(distance);
        back_btn->setObjectName(QString::fromUtf8("back_btn"));
        back_btn->setGeometry(QRect(1120, 20, 141, 71));
        QFont font;
        font.setPointSize(14);
        back_btn->setFont(font);
        back_btn->setStyleSheet(QString::fromUtf8("background-color: rgb(148, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        label_res = new QLabel(distance);
        label_res->setObjectName(QString::fromUtf8("label_res"));
        label_res->setGeometry(QRect(20, 500, 271, 201));
        label_res->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        comboBox = new QComboBox(distance);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(820, 20, 121, 51));
        QFont font1;
        font1.setPointSize(16);
        comboBox->setFont(font1);
        comboBox->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_2 = new QLabel(distance);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(660, 30, 121, 31));
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        comboBox_2 = new QComboBox(distance);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(820, 100, 111, 61));
        comboBox_2->setFont(font1);
        comboBox_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_3 = new QLabel(distance);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(660, 110, 111, 41));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_4 = new QLabel(distance);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(660, 260, 161, 31));
        QFont font2;
        font2.setPointSize(13);
        label_4->setFont(font2);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_1 = new QLineEdit(distance);
        lineEdit_1->setObjectName(QString::fromUtf8("lineEdit_1"));
        lineEdit_1->setGeometry(QRect(820, 260, 111, 41));
        lineEdit_1->setFont(font1);
        lineEdit_1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(13, 43, 37);\n"
"border-color: rgb(255, 255, 255);"));
        label_dis = new QLabel(distance);
        label_dis->setObjectName(QString::fromUtf8("label_dis"));
        label_dis->setGeometry(QRect(650, 530, 231, 31));
        QFont font3;
        font3.setPointSize(19);
        label_dis->setFont(font3);
        label_dis->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        back_btn_2 = new QPushButton(distance);
        back_btn_2->setObjectName(QString::fromUtf8("back_btn_2"));
        back_btn_2->setGeometry(QRect(1120, 610, 141, 71));
        back_btn_2->setFont(font);
        back_btn_2->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 153, 0) ;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        back_btn_3 = new QPushButton(distance);
        back_btn_3->setObjectName(QString::fromUtf8("back_btn_3"));
        back_btn_3->setGeometry(QRect(1120, 520, 141, 61));
        back_btn_3->setFont(font);
        back_btn_3->setStyleSheet(QString::fromUtf8("background-color: rgb(148, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        label_fps = new QLabel(distance);
        label_fps->setObjectName(QString::fromUtf8("label_fps"));
        label_fps->setGeometry(QRect(650, 480, 111, 16));
        QFont font4;
        font4.setPointSize(12);
        label_fps->setFont(font4);
        label_fps->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_info = new QLabel(distance);
        label_info->setObjectName(QString::fromUtf8("label_info"));
        label_info->setGeometry(QRect(310, 500, 331, 201));
        label_info->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        flip_btn = new QPushButton(distance);
        flip_btn->setObjectName(QString::fromUtf8("flip_btn"));
        flip_btn->setGeometry(QRect(980, 460, 101, 51));
        flip_btn->setFont(font);
        flip_btn->setStyleSheet(QString::fromUtf8("background-color:rgb(170, 0, 0) ;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        label_f = new QLabel(distance);
        label_f->setObjectName(QString::fromUtf8("label_f"));
        label_f->setGeometry(QRect(780, 460, 181, 51));
        label_f->setFont(font2);
        label_f->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_5 = new QLabel(distance);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(660, 200, 91, 21));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        comboBox_3 = new QComboBox(distance);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(820, 190, 111, 41));
        QFont font5;
        font5.setPointSize(17);
        comboBox_3->setFont(font5);
        comboBox_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_6 = new QLabel(distance);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(660, 320, 161, 31));
        label_6->setFont(font2);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        lineEdit_2 = new QLineEdit(distance);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(820, 320, 111, 41));
        lineEdit_2->setFont(font1);
        lineEdit_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(13, 43, 37);\n"
"border-color: rgb(255, 255, 255);"));
        comboBox_4 = new QComboBox(distance);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(820, 380, 111, 51));
        comboBox_4->setFont(font2);
        comboBox_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_7 = new QLabel(distance);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(660, 390, 101, 31));
        label_7->setFont(font);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        usage_btn = new QPushButton(distance);
        usage_btn->setObjectName(QString::fromUtf8("usage_btn"));
        usage_btn->setGeometry(QRect(1120, 120, 141, 61));
        usage_btn->setFont(font);
        usage_btn->setStyleSheet(QString::fromUtf8("background-color:rgb(16, 124, 255) ;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        label = new QLabel(distance);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(970, 40, 81, 21));
        label->setFont(font4);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        comboBox_5 = new QComboBox(distance);
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
        comboBox_5->setGeometry(QRect(960, 110, 111, 41));
        comboBox_5->setFont(font);
        comboBox_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_8 = new QLabel(distance);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(970, 200, 81, 21));
        label_8->setFont(font4);
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        comboBox_6 = new QComboBox(distance);
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));
        comboBox_6->setGeometry(QRect(960, 260, 121, 41));
        comboBox_6->setFont(font2);
        comboBox_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_9 = new QLabel(distance);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(970, 330, 81, 21));
        label_9->setFont(font4);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        comboBox_7 = new QComboBox(distance);
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->setObjectName(QString::fromUtf8("comboBox_7"));
        comboBox_7->setGeometry(QRect(960, 380, 121, 41));
        comboBox_7->setFont(font2);
        comboBox_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        scrshotBtn = new QPushButton(distance);
        scrshotBtn->setObjectName(QString::fromUtf8("scrshotBtn"));
        scrshotBtn->setGeometry(QRect(1120, 420, 141, 61));
        QFont font6;
        font6.setPointSize(15);
        scrshotBtn->setFont(font6);
        scrshotBtn->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 170, 255);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        zBtn = new QPushButton(distance);
        zBtn->setObjectName(QString::fromUtf8("zBtn"));
        zBtn->setGeometry(QRect(1119, 212, 141, 71));
        zBtn->setFont(font2);
        zBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(28, 43, 95);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        xBtn = new QPushButton(distance);
        xBtn->setObjectName(QString::fromUtf8("xBtn"));
        xBtn->setGeometry(QRect(1120, 310, 141, 71));
        xBtn->setFont(font2);
        xBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(28, 43, 95);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));
        show1Btn = new QPushButton(distance);
        show1Btn->setObjectName(QString::fromUtf8("show1Btn"));
        show1Btn->setGeometry(QRect(980, 540, 101, 51));
        show1Btn->setFont(font4);
        show1Btn->setStyleSheet(QString::fromUtf8("background-color:rgb(16, 124, 255) ;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;\n"
""));
        label_dis_2 = new QLabel(distance);
        label_dis_2->setObjectName(QString::fromUtf8("label_dis_2"));
        label_dis_2->setGeometry(QRect(650, 600, 231, 31));
        label_dis_2->setFont(font3);
        label_dis_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        filterBtn = new QPushButton(distance);
        filterBtn->setObjectName(QString::fromUtf8("filterBtn"));
        filterBtn->setGeometry(QRect(980, 620, 101, 51));
        filterBtn->setFont(font4);
        filterBtn->setStyleSheet(QString::fromUtf8("background-color:rgb(0, 153, 0) ;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 20px;"));

        retranslateUi(distance);

        QMetaObject::connectSlotsByName(distance);
    } // setupUi

    void retranslateUi(QWidget *distance)
    {
        distance->setWindowTitle(QCoreApplication::translate("distance", "Form", nullptr));
        back_btn->setText(QCoreApplication::translate("distance", "\350\277\224\345\233\236", nullptr));
        label_res->setText(QCoreApplication::translate("distance", "\345\215\240\347\224\250", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("distance", "640*480", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("distance", "960*720", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("distance", "1280*960", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("distance", "1920*1440", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("distance", "2592*1944", nullptr));

        label_2->setText(QCoreApplication::translate("distance", "\350\276\223\345\205\245\345\210\206\350\276\250\347\216\207", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("distance", "bottle", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("distance", "Person", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("distance", "cell phone", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("distance", "bicycle", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("distance", "car", nullptr));

        label_3->setText(QCoreApplication::translate("distance", "\350\256\276\347\275\256  \347\233\256\346\240\207", nullptr));
        label_4->setText(QCoreApplication::translate("distance", "\347\233\256\346\240\207\345\205\210\351\252\214\345\260\272\345\257\270(mm)", nullptr));
        lineEdit_1->setText(QCoreApplication::translate("distance", "100", nullptr));
        label_dis->setText(QCoreApplication::translate("distance", "\345\275\223\345\211\215\350\267\235\347\246\273: 1.234m", nullptr));
        back_btn_2->setText(QCoreApplication::translate("distance", "\345\274\200\345\247\213\346\265\213\351\207\217", nullptr));
        back_btn_3->setText(QCoreApplication::translate("distance", "\347\273\223\346\235\237", nullptr));
#if QT_CONFIG(whatsthis)
        label_fps->setWhatsThis(QCoreApplication::translate("distance", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_fps->setText(QCoreApplication::translate("distance", "0FPS", nullptr));
        label_info->setText(QCoreApplication::translate("distance", "INFO", nullptr));
        flip_btn->setText(QCoreApplication::translate("distance", "\346\240\241\346\255\243", nullptr));
        label_f->setText(QCoreApplication::translate("distance", "\345\203\217\347\264\240\347\204\246\350\267\235\357\274\232600px", nullptr));
        label_5->setText(QCoreApplication::translate("distance", "\346\240\241\346\255\243\350\267\235\347\246\273", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("distance", "600mm", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("distance", "800mm", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("distance", "1000mm", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("distance", "5000mm", nullptr));
        comboBox_3->setItemText(4, QCoreApplication::translate("distance", "300mm", nullptr));
        comboBox_3->setItemText(5, QCoreApplication::translate("distance", "150mm", nullptr));

        label_6->setText(QCoreApplication::translate("distance", "\347\233\270\346\234\272\351\253\230\345\272\246(mm)", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("distance", "65", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("distance", "\347\233\256\346\240\207\345\205\210\351\252\214", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("distance", "\347\233\270\346\234\272\345\205\210\351\252\214", nullptr));

        label_7->setText(QCoreApplication::translate("distance", "\346\265\213\350\267\235\346\226\271\346\263\225\357\274\232", nullptr));
        usage_btn->setText(QCoreApplication::translate("distance", "\344\275\277\347\224\250\346\226\271\346\263\225", nullptr));
        label->setText(QCoreApplication::translate("distance", "CPU\351\242\221\347\216\207", nullptr));
        comboBox_5->setItemText(0, QCoreApplication::translate("distance", "1800000", nullptr));
        comboBox_5->setItemText(1, QCoreApplication::translate("distance", "1608000", nullptr));
        comboBox_5->setItemText(2, QCoreApplication::translate("distance", "1416000", nullptr));
        comboBox_5->setItemText(3, QCoreApplication::translate("distance", "1104000", nullptr));
        comboBox_5->setItemText(4, QCoreApplication::translate("distance", "816000", nullptr));
        comboBox_5->setItemText(5, QCoreApplication::translate("distance", "600000", nullptr));
        comboBox_5->setItemText(6, QCoreApplication::translate("distance", "408000", nullptr));

        label_8->setText(QCoreApplication::translate("distance", "NPU\351\242\221\347\216\207", nullptr));
        comboBox_6->setItemText(0, QCoreApplication::translate("distance", "900000000", nullptr));
        comboBox_6->setItemText(1, QCoreApplication::translate("distance", "800000000", nullptr));
        comboBox_6->setItemText(2, QCoreApplication::translate("distance", "700000000", nullptr));
        comboBox_6->setItemText(3, QCoreApplication::translate("distance", "600000000", nullptr));
        comboBox_6->setItemText(4, QCoreApplication::translate("distance", "400000000", nullptr));
        comboBox_6->setItemText(5, QCoreApplication::translate("distance", "297000000", nullptr));
        comboBox_6->setItemText(6, QCoreApplication::translate("distance", "200000000", nullptr));

        label_9->setText(QCoreApplication::translate("distance", "GPU\351\242\221\347\216\207", nullptr));
        comboBox_7->setItemText(0, QCoreApplication::translate("distance", "800000000", nullptr));
        comboBox_7->setItemText(1, QCoreApplication::translate("distance", "700000000", nullptr));
        comboBox_7->setItemText(2, QCoreApplication::translate("distance", "600000000", nullptr));
        comboBox_7->setItemText(3, QCoreApplication::translate("distance", "400000000", nullptr));
        comboBox_7->setItemText(4, QCoreApplication::translate("distance", "300000000", nullptr));
        comboBox_7->setItemText(5, QCoreApplication::translate("distance", "200000000", nullptr));

        scrshotBtn->setText(QCoreApplication::translate("distance", "\346\210\252\345\261\217", nullptr));
        zBtn->setText(QCoreApplication::translate("distance", "\344\275\277\347\224\250\346\240\207\345\256\232\347\204\246\350\267\235", nullptr));
        xBtn->setText(QCoreApplication::translate("distance", "\344\275\277\347\224\250\346\240\241\346\255\243\347\204\246\350\267\235", nullptr));
        show1Btn->setText(QCoreApplication::translate("distance", "\346\230\276\347\244\272\350\276\205\345\212\251\347\272\277", nullptr));
        label_dis_2->setText(QCoreApplication::translate("distance", "\345\271\263\345\235\207\350\267\235\347\246\273: 1.234m", nullptr));
        filterBtn->setText(QCoreApplication::translate("distance", "\345\274\200\345\247\213\346\273\244\346\263\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class distance: public Ui_distance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCE_H
