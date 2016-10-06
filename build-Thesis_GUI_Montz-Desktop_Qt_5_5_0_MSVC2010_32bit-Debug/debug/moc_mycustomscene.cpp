/****************************************************************************
** Meta object code from reading C++ file 'mycustomscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Thesis_GUI_Montz/mycustomscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mycustomscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_myCustomScene_t {
    QByteArrayData data[7];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myCustomScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myCustomScene_t qt_meta_stringdata_myCustomScene = {
    {
QT_MOC_LITERAL(0, 0, 13), // "myCustomScene"
QT_MOC_LITERAL(1, 14, 17), // "sceneMousePressed"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 18), // "sceneMouseReleased"
QT_MOC_LITERAL(4, 52, 15), // "sceneMouseMoved"
QT_MOC_LITERAL(5, 68, 23), // "sceneMouseDoubleClicked"
QT_MOC_LITERAL(6, 92, 15) // "scenePosClicked"

    },
    "myCustomScene\0sceneMousePressed\0\0"
    "sceneMouseReleased\0sceneMouseMoved\0"
    "sceneMouseDoubleClicked\0scenePosClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myCustomScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,
       4,    1,   45,    2, 0x06 /* Public */,
       5,    0,   48,    2, 0x06 /* Public */,
       6,    1,   49,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, QMetaType::QPointF,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPointF,    2,

       0        // eod
};

void myCustomScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myCustomScene *_t = static_cast<myCustomScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sceneMousePressed((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->sceneMouseReleased((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 2: _t->sceneMouseMoved((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 3: _t->sceneMouseDoubleClicked(); break;
        case 4: _t->scenePosClicked((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (myCustomScene::*_t)(qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myCustomScene::sceneMousePressed)) {
                *result = 0;
            }
        }
        {
            typedef void (myCustomScene::*_t)(qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myCustomScene::sceneMouseReleased)) {
                *result = 1;
            }
        }
        {
            typedef void (myCustomScene::*_t)(QPointF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myCustomScene::sceneMouseMoved)) {
                *result = 2;
            }
        }
        {
            typedef void (myCustomScene::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myCustomScene::sceneMouseDoubleClicked)) {
                *result = 3;
            }
        }
        {
            typedef void (myCustomScene::*_t)(QPointF );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&myCustomScene::scenePosClicked)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject myCustomScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_myCustomScene.data,
      qt_meta_data_myCustomScene,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myCustomScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myCustomScene::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myCustomScene.stringdata0))
        return static_cast<void*>(const_cast< myCustomScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int myCustomScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void myCustomScene::sceneMousePressed(qreal _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void myCustomScene::sceneMouseReleased(qreal _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void myCustomScene::sceneMouseMoved(QPointF _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void myCustomScene::sceneMouseDoubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void myCustomScene::scenePosClicked(QPointF _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
