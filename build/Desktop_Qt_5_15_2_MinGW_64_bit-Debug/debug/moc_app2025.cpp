/****************************************************************************
** Meta object code from reading C++ file 'app2025.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/index/app2025.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'app2025.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_app2025_t {
    QByteArrayData data[11];
    char stringdata0[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_app2025_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_app2025_t qt_meta_stringdata_app2025 = {
    {
QT_MOC_LITERAL(0, 0, 7), // "app2025"
QT_MOC_LITERAL(1, 8, 20), // "on_close_btn_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 19), // "on_app1_btn_clicked"
QT_MOC_LITERAL(4, 50, 19), // "on_app2_btn_clicked"
QT_MOC_LITERAL(5, 70, 19), // "on_app3_btn_clicked"
QT_MOC_LITERAL(6, 90, 19), // "on_app4_btn_clicked"
QT_MOC_LITERAL(7, 110, 15), // "updateTimeLabel"
QT_MOC_LITERAL(8, 126, 30), // "on_poweroff_pushButton_clicked"
QT_MOC_LITERAL(9, 157, 28), // "on_reboot_pushButton_clicked"
QT_MOC_LITERAL(10, 186, 26) // "on_test_pushButton_clicked"

    },
    "app2025\0on_close_btn_clicked\0\0"
    "on_app1_btn_clicked\0on_app2_btn_clicked\0"
    "on_app3_btn_clicked\0on_app4_btn_clicked\0"
    "updateTimeLabel\0on_poweroff_pushButton_clicked\0"
    "on_reboot_pushButton_clicked\0"
    "on_test_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_app2025[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void app2025::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<app2025 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_close_btn_clicked(); break;
        case 1: _t->on_app1_btn_clicked(); break;
        case 2: _t->on_app2_btn_clicked(); break;
        case 3: _t->on_app3_btn_clicked(); break;
        case 4: _t->on_app4_btn_clicked(); break;
        case 5: _t->updateTimeLabel(); break;
        case 6: _t->on_poweroff_pushButton_clicked(); break;
        case 7: _t->on_reboot_pushButton_clicked(); break;
        case 8: _t->on_test_pushButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject app2025::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_app2025.data,
    qt_meta_data_app2025,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *app2025::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *app2025::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_app2025.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int app2025::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
