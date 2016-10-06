/****************************************************************************
** Meta object code from reading C++ file 'myuart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Thesis_GUI_Montz/myuart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myuart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyUART_t {
    QByteArrayData data[24];
    char stringdata0[311];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyUART_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyUART_t qt_meta_stringdata_MyUART = {
    {
QT_MOC_LITERAL(0, 0, 6), // "MyUART"
QT_MOC_LITERAL(1, 7, 19), // "errorShutdownSignal"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "statusByte"
QT_MOC_LITERAL(4, 39, 9), // "ackSignal"
QT_MOC_LITERAL(5, 49, 12), // "statusSignal"
QT_MOC_LITERAL(6, 62, 8), // "systemID"
QT_MOC_LITERAL(7, 71, 24), // "reqOrientationDataSignal"
QT_MOC_LITERAL(8, 96, 18), // "DataTransferSignal"
QT_MOC_LITERAL(9, 115, 7), // "payload"
QT_MOC_LITERAL(10, 123, 8), // "rxSignal"
QT_MOC_LITERAL(11, 132, 8), // "txSignal"
QT_MOC_LITERAL(12, 141, 17), // "sendAbortShutdown"
QT_MOC_LITERAL(13, 159, 7), // "sendACK"
QT_MOC_LITERAL(14, 167, 16), // "sendDetectSystem"
QT_MOC_LITERAL(15, 184, 7), // "updates"
QT_MOC_LITERAL(16, 192, 16), // "sendBeginProcess"
QT_MOC_LITERAL(17, 209, 25), // "sendBeginTransmittingData"
QT_MOC_LITERAL(18, 235, 19), // "sendOrientationData"
QT_MOC_LITERAL(19, 255, 10), // "currentLat"
QT_MOC_LITERAL(20, 266, 10), // "currentLon"
QT_MOC_LITERAL(21, 277, 10), // "currentAzi"
QT_MOC_LITERAL(22, 288, 8), // "sendNACK"
QT_MOC_LITERAL(23, 297, 13) // "readyReadSlot"

    },
    "MyUART\0errorShutdownSignal\0\0statusByte\0"
    "ackSignal\0statusSignal\0systemID\0"
    "reqOrientationDataSignal\0DataTransferSignal\0"
    "payload\0rxSignal\0txSignal\0sendAbortShutdown\0"
    "sendACK\0sendDetectSystem\0updates\0"
    "sendBeginProcess\0sendBeginTransmittingData\0"
    "sendOrientationData\0currentLat\0"
    "currentLon\0currentAzi\0sendNACK\0"
    "readyReadSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyUART[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       4,    1,   92,    2, 0x06 /* Public */,
       5,    2,   95,    2, 0x06 /* Public */,
       7,    1,  100,    2, 0x06 /* Public */,
       8,    2,  103,    2, 0x06 /* Public */,
      10,    0,  108,    2, 0x06 /* Public */,
      11,    0,  109,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,  110,    2, 0x0a /* Public */,
      13,    0,  111,    2, 0x0a /* Public */,
      14,    1,  112,    2, 0x0a /* Public */,
      16,    0,  115,    2, 0x0a /* Public */,
      17,    0,  116,    2, 0x0a /* Public */,
      18,    3,  117,    2, 0x0a /* Public */,
      22,    0,  124,    2, 0x0a /* Public */,
      23,    0,  125,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::QByteArray,    3,    9,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   19,   20,   21,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyUART::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyUART *_t = static_cast<MyUART *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->errorShutdownSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->ackSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->statusSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->reqOrientationDataSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->DataTransferSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 5: _t->rxSignal(); break;
        case 6: _t->txSignal(); break;
        case 7: _t->sendAbortShutdown(); break;
        case 8: _t->sendACK(); break;
        case 9: _t->sendDetectSystem((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->sendBeginProcess(); break;
        case 11: _t->sendBeginTransmittingData(); break;
        case 12: _t->sendOrientationData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 13: _t->sendNACK(); break;
        case 14: _t->readyReadSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyUART::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyUART::errorShutdownSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (MyUART::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyUART::ackSignal)) {
                *result = 1;
            }
        }
        {
            typedef void (MyUART::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyUART::statusSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (MyUART::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyUART::reqOrientationDataSignal)) {
                *result = 3;
            }
        }
        {
            typedef void (MyUART::*_t)(int , QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyUART::DataTransferSignal)) {
                *result = 4;
            }
        }
        {
            typedef void (MyUART::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyUART::rxSignal)) {
                *result = 5;
            }
        }
        {
            typedef void (MyUART::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyUART::txSignal)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject MyUART::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MyUART.data,
      qt_meta_data_MyUART,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyUART::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyUART::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyUART.stringdata0))
        return static_cast<void*>(const_cast< MyUART*>(this));
    return QObject::qt_metacast(_clname);
}

int MyUART::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MyUART::errorShutdownSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyUART::ackSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyUART::statusSignal(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyUART::reqOrientationDataSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyUART::DataTransferSignal(int _t1, QByteArray _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MyUART::rxSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void MyUART::txSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
