/****************************************************************************
** Meta object code from reading C++ file 'orbitalanimationwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Thesis_GUI_Montz/orbitalanimationwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'orbitalanimationwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OrbitalAnimationWidget_t {
    QByteArrayData data[13];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OrbitalAnimationWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OrbitalAnimationWidget_t qt_meta_stringdata_OrbitalAnimationWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "OrbitalAnimationWidget"
QT_MOC_LITERAL(1, 23, 14), // "startAnimation"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 6), // "Cycles"
QT_MOC_LITERAL(4, 46, 8), // "timeToTX"
QT_MOC_LITERAL(5, 55, 13), // "orbitalPeriod"
QT_MOC_LITERAL(6, 69, 13), // "stopAnimation"
QT_MOC_LITERAL(7, 83, 11), // "resetWidget"
QT_MOC_LITERAL(8, 95, 12), // "timerTimeout"
QT_MOC_LITERAL(9, 108, 20), // "setSatelliteLocation"
QT_MOC_LITERAL(10, 129, 5), // "angle"
QT_MOC_LITERAL(11, 135, 14), // "initializeText"
QT_MOC_LITERAL(12, 150, 10) // "updateText"

    },
    "OrbitalAnimationWidget\0startAnimation\0"
    "\0Cycles\0timeToTX\0orbitalPeriod\0"
    "stopAnimation\0resetWidget\0timerTimeout\0"
    "setSatelliteLocation\0angle\0initializeText\0"
    "updateText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OrbitalAnimationWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   49,    2, 0x0a /* Public */,
       6,    0,   56,    2, 0x0a /* Public */,
       7,    0,   57,    2, 0x0a /* Public */,
       8,    0,   58,    2, 0x0a /* Public */,
       9,    1,   59,    2, 0x0a /* Public */,
      11,    0,   62,    2, 0x0a /* Public */,
      12,    0,   63,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OrbitalAnimationWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OrbitalAnimationWidget *_t = static_cast<OrbitalAnimationWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startAnimation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->stopAnimation(); break;
        case 2: _t->resetWidget(); break;
        case 3: _t->timerTimeout(); break;
        case 4: _t->setSatelliteLocation((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->initializeText(); break;
        case 6: _t->updateText(); break;
        default: ;
        }
    }
}

const QMetaObject OrbitalAnimationWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_OrbitalAnimationWidget.data,
      qt_meta_data_OrbitalAnimationWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OrbitalAnimationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OrbitalAnimationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OrbitalAnimationWidget.stringdata0))
        return static_cast<void*>(const_cast< OrbitalAnimationWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int OrbitalAnimationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
