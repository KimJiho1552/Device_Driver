/****************************************************************************
** Meta object code from reading C++ file 'tab1devcontrol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tab1devcontrol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tab1devcontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Tab1DevControl_t {
    QByteArrayData data[6];
    char stringdata[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Tab1DevControl_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Tab1DevControl_t qt_meta_stringdata_Tab1DevControl = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 14),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 20),
QT_MOC_LITERAL(4, 52, 16),
QT_MOC_LITERAL(5, 69, 21)
    },
    "Tab1DevControl\0slotTimerStart\0\0"
    "slotTimerValueChange\0slotSetValueDial\0"
    "slotKeyCheckBoxUpdate\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tab1DevControl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08,
       3,    1,   37,    2, 0x08,
       4,    0,   40,    2, 0x08,
       5,    1,   41,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Tab1DevControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Tab1DevControl *_t = static_cast<Tab1DevControl *>(_o);
        switch (_id) {
        case 0: _t->slotTimerStart((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slotTimerValueChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->slotSetValueDial(); break;
        case 3: _t->slotKeyCheckBoxUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Tab1DevControl::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Tab1DevControl.data,
      qt_meta_data_Tab1DevControl,  qt_static_metacall, 0, 0}
};


const QMetaObject *Tab1DevControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tab1DevControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Tab1DevControl.stringdata))
        return static_cast<void*>(const_cast< Tab1DevControl*>(this));
    return QWidget::qt_metacast(_clname);
}

int Tab1DevControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
