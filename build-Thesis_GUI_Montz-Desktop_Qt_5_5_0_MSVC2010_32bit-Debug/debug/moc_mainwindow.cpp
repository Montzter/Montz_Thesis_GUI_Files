/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Thesis_GUI_Montz/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[70];
    char stringdata0[1204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "showSettings"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 23), // "sendAbortShutdownSignal"
QT_MOC_LITERAL(4, 49, 13), // "sendAckSignal"
QT_MOC_LITERAL(5, 63, 22), // "sendDetectSystemSignal"
QT_MOC_LITERAL(6, 86, 22), // "sendBeginProcessSignal"
QT_MOC_LITERAL(7, 109, 31), // "sendBeginTransmittingDataSignal"
QT_MOC_LITERAL(8, 141, 19), // "sendOrientationData"
QT_MOC_LITERAL(9, 161, 11), // "saveCsvFile"
QT_MOC_LITERAL(10, 173, 16), // "setStatusBarText"
QT_MOC_LITERAL(11, 190, 6), // "char[]"
QT_MOC_LITERAL(12, 197, 11), // "LabelString"
QT_MOC_LITERAL(13, 209, 20), // "refreshStatusBarText"
QT_MOC_LITERAL(14, 230, 28), // "setStatusBarProgressBarValue"
QT_MOC_LITERAL(15, 259, 5), // "PBVal"
QT_MOC_LITERAL(16, 265, 10), // "setRXBlink"
QT_MOC_LITERAL(17, 276, 10), // "setTXBlink"
QT_MOC_LITERAL(18, 287, 20), // "scenePressed_endSlot"
QT_MOC_LITERAL(19, 308, 10), // "pixelValue"
QT_MOC_LITERAL(20, 319, 13), // "clickPosition"
QT_MOC_LITERAL(21, 333, 12), // "histLocation"
QT_MOC_LITERAL(22, 346, 17), // "errorShutdownSlot"
QT_MOC_LITERAL(23, 364, 10), // "statusByte"
QT_MOC_LITERAL(24, 375, 7), // "ackSlot"
QT_MOC_LITERAL(25, 383, 10), // "statusSlot"
QT_MOC_LITERAL(26, 394, 3), // "sID"
QT_MOC_LITERAL(27, 398, 22), // "reqOrientationDataSlot"
QT_MOC_LITERAL(28, 421, 18), // "dataTransferSignal"
QT_MOC_LITERAL(29, 440, 7), // "payload"
QT_MOC_LITERAL(30, 448, 13), // "moveMinSlider"
QT_MOC_LITERAL(31, 462, 3), // "val"
QT_MOC_LITERAL(32, 466, 13), // "moveMaxSlider"
QT_MOC_LITERAL(33, 480, 24), // "on_actionClose_triggered"
QT_MOC_LITERAL(34, 505, 27), // "on_actionSettings_triggered"
QT_MOC_LITERAL(35, 533, 32), // "on_actionDetect_System_triggered"
QT_MOC_LITERAL(36, 566, 19), // "startTest_triggered"
QT_MOC_LITERAL(37, 586, 16), // "resetRXIndicator"
QT_MOC_LITERAL(38, 603, 16), // "resetTXIndicator"
QT_MOC_LITERAL(39, 620, 10), // "refitScene"
QT_MOC_LITERAL(40, 631, 21), // "offsetTimer_triggered"
QT_MOC_LITERAL(41, 653, 22), // "processTimer_triggered"
QT_MOC_LITERAL(42, 676, 23), // "transmitTimer_triggered"
QT_MOC_LITERAL(43, 700, 25), // "simulationTimer_triggered"
QT_MOC_LITERAL(44, 726, 22), // "colorKeyButton_pressed"
QT_MOC_LITERAL(45, 749, 19), // "abortButton_pressed"
QT_MOC_LITERAL(46, 769, 26), // "beginProcessButton_pressed"
QT_MOC_LITERAL(47, 796, 31), // "beginTransmittingButton_pressed"
QT_MOC_LITERAL(48, 828, 23), // "beginTestButton_pressed"
QT_MOC_LITERAL(49, 852, 20), // "zoomInButton_pressed"
QT_MOC_LITERAL(50, 873, 21), // "zoomOutButton_pressed"
QT_MOC_LITERAL(51, 895, 23), // "zoomResetButton_pressed"
QT_MOC_LITERAL(52, 919, 21), // "colormapCombo_changed"
QT_MOC_LITERAL(53, 941, 7), // "cmIndex"
QT_MOC_LITERAL(54, 949, 26), // "InvertingCheckbox_released"
QT_MOC_LITERAL(55, 976, 16), // "clickedOnLogFile"
QT_MOC_LITERAL(56, 993, 5), // "index"
QT_MOC_LITERAL(57, 999, 24), // "logRefreshButton_clicked"
QT_MOC_LITERAL(58, 1024, 13), // "updateLogList"
QT_MOC_LITERAL(59, 1038, 26), // "on_actionConnect_triggered"
QT_MOC_LITERAL(60, 1065, 16), // "clickedOnImgFile"
QT_MOC_LITERAL(61, 1082, 13), // "updateImgList"
QT_MOC_LITERAL(62, 1096, 7), // "loadImg"
QT_MOC_LITERAL(63, 1104, 11), // "updateImage"
QT_MOC_LITERAL(64, 1116, 29), // "on_actionDisconnect_triggered"
QT_MOC_LITERAL(65, 1146, 14), // "minSliderMoved"
QT_MOC_LITERAL(66, 1161, 5), // "value"
QT_MOC_LITERAL(67, 1167, 14), // "maxSliderMoved"
QT_MOC_LITERAL(68, 1182, 13), // "resetColormap"
QT_MOC_LITERAL(69, 1196, 7) // "saveImg"

    },
    "MainWindow\0showSettings\0\0"
    "sendAbortShutdownSignal\0sendAckSignal\0"
    "sendDetectSystemSignal\0sendBeginProcessSignal\0"
    "sendBeginTransmittingDataSignal\0"
    "sendOrientationData\0saveCsvFile\0"
    "setStatusBarText\0char[]\0LabelString\0"
    "refreshStatusBarText\0setStatusBarProgressBarValue\0"
    "PBVal\0setRXBlink\0setTXBlink\0"
    "scenePressed_endSlot\0pixelValue\0"
    "clickPosition\0histLocation\0errorShutdownSlot\0"
    "statusByte\0ackSlot\0statusSlot\0sID\0"
    "reqOrientationDataSlot\0dataTransferSignal\0"
    "payload\0moveMinSlider\0val\0moveMaxSlider\0"
    "on_actionClose_triggered\0"
    "on_actionSettings_triggered\0"
    "on_actionDetect_System_triggered\0"
    "startTest_triggered\0resetRXIndicator\0"
    "resetTXIndicator\0refitScene\0"
    "offsetTimer_triggered\0processTimer_triggered\0"
    "transmitTimer_triggered\0"
    "simulationTimer_triggered\0"
    "colorKeyButton_pressed\0abortButton_pressed\0"
    "beginProcessButton_pressed\0"
    "beginTransmittingButton_pressed\0"
    "beginTestButton_pressed\0zoomInButton_pressed\0"
    "zoomOutButton_pressed\0zoomResetButton_pressed\0"
    "colormapCombo_changed\0cmIndex\0"
    "InvertingCheckbox_released\0clickedOnLogFile\0"
    "index\0logRefreshButton_clicked\0"
    "updateLogList\0on_actionConnect_triggered\0"
    "clickedOnImgFile\0updateImgList\0loadImg\0"
    "updateImage\0on_actionDisconnect_triggered\0"
    "minSliderMoved\0value\0maxSliderMoved\0"
    "resetColormap\0saveImg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      57,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  299,    2, 0x06 /* Public */,
       3,    0,  300,    2, 0x06 /* Public */,
       4,    0,  301,    2, 0x06 /* Public */,
       5,    1,  302,    2, 0x06 /* Public */,
       6,    0,  305,    2, 0x06 /* Public */,
       7,    0,  306,    2, 0x06 /* Public */,
       8,    3,  307,    2, 0x06 /* Public */,
       9,    1,  314,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,  317,    2, 0x0a /* Public */,
      13,    0,  320,    2, 0x0a /* Public */,
      14,    1,  321,    2, 0x0a /* Public */,
      16,    0,  324,    2, 0x0a /* Public */,
      17,    0,  325,    2, 0x0a /* Public */,
      18,    3,  326,    2, 0x0a /* Public */,
      22,    1,  333,    2, 0x0a /* Public */,
      24,    1,  336,    2, 0x0a /* Public */,
      25,    2,  339,    2, 0x0a /* Public */,
      27,    1,  344,    2, 0x0a /* Public */,
      28,    2,  347,    2, 0x0a /* Public */,
      30,    1,  352,    2, 0x0a /* Public */,
      32,    1,  355,    2, 0x0a /* Public */,
      33,    0,  358,    2, 0x08 /* Private */,
      34,    0,  359,    2, 0x08 /* Private */,
      35,    0,  360,    2, 0x08 /* Private */,
      36,    0,  361,    2, 0x08 /* Private */,
      37,    0,  362,    2, 0x08 /* Private */,
      38,    0,  363,    2, 0x08 /* Private */,
      39,    0,  364,    2, 0x08 /* Private */,
      40,    0,  365,    2, 0x08 /* Private */,
      41,    0,  366,    2, 0x08 /* Private */,
      42,    0,  367,    2, 0x08 /* Private */,
      43,    0,  368,    2, 0x08 /* Private */,
      44,    0,  369,    2, 0x08 /* Private */,
      45,    0,  370,    2, 0x08 /* Private */,
      46,    0,  371,    2, 0x08 /* Private */,
      47,    0,  372,    2, 0x08 /* Private */,
      48,    0,  373,    2, 0x08 /* Private */,
      49,    0,  374,    2, 0x08 /* Private */,
      50,    0,  375,    2, 0x08 /* Private */,
      51,    0,  376,    2, 0x08 /* Private */,
      52,    1,  377,    2, 0x08 /* Private */,
      54,    0,  380,    2, 0x08 /* Private */,
      55,    1,  381,    2, 0x08 /* Private */,
      57,    0,  384,    2, 0x08 /* Private */,
      58,    0,  385,    2, 0x08 /* Private */,
      59,    0,  386,    2, 0x08 /* Private */,
      60,    1,  387,    2, 0x08 /* Private */,
      61,    0,  390,    2, 0x08 /* Private */,
      62,    0,  391,    2, 0x08 /* Private */,
      63,    0,  392,    2, 0x08 /* Private */,
      64,    0,  393,    2, 0x08 /* Private */,
      65,    1,  394,    2, 0x08 /* Private */,
      67,    1,  397,    2, 0x08 /* Private */,
      65,    1,  400,    2, 0x08 /* Private */,
      67,    1,  403,    2, 0x08 /* Private */,
      68,    0,  406,    2, 0x08 /* Private */,
      69,    0,  407,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF, QMetaType::Int,   19,   20,   21,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   26,   23,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::QByteArray,   23,   29,
    QMetaType::Void, QMetaType::QReal,   31,
    QMetaType::Void, QMetaType::QReal,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   53,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   56,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   56,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   66,
    QMetaType::Void, QMetaType::Int,   66,
    QMetaType::Void, QMetaType::QReal,   66,
    QMetaType::Void, QMetaType::QReal,   66,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showSettings(); break;
        case 1: _t->sendAbortShutdownSignal(); break;
        case 2: _t->sendAckSignal(); break;
        case 3: _t->sendDetectSystemSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->sendBeginProcessSignal(); break;
        case 5: _t->sendBeginTransmittingDataSignal(); break;
        case 6: _t->sendOrientationData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 7: _t->saveCsvFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setStatusBarText((*reinterpret_cast< char(*)[]>(_a[1]))); break;
        case 9: _t->refreshStatusBarText(); break;
        case 10: _t->setStatusBarProgressBarValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setRXBlink(); break;
        case 12: _t->setTXBlink(); break;
        case 13: _t->scenePressed_endSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 14: _t->errorShutdownSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->ackSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->statusSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 17: _t->reqOrientationDataSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->dataTransferSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 19: _t->moveMinSlider((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 20: _t->moveMaxSlider((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 21: _t->on_actionClose_triggered(); break;
        case 22: _t->on_actionSettings_triggered(); break;
        case 23: _t->on_actionDetect_System_triggered(); break;
        case 24: _t->startTest_triggered(); break;
        case 25: _t->resetRXIndicator(); break;
        case 26: _t->resetTXIndicator(); break;
        case 27: _t->refitScene(); break;
        case 28: _t->offsetTimer_triggered(); break;
        case 29: _t->processTimer_triggered(); break;
        case 30: _t->transmitTimer_triggered(); break;
        case 31: _t->simulationTimer_triggered(); break;
        case 32: _t->colorKeyButton_pressed(); break;
        case 33: _t->abortButton_pressed(); break;
        case 34: _t->beginProcessButton_pressed(); break;
        case 35: _t->beginTransmittingButton_pressed(); break;
        case 36: _t->beginTestButton_pressed(); break;
        case 37: _t->zoomInButton_pressed(); break;
        case 38: _t->zoomOutButton_pressed(); break;
        case 39: _t->zoomResetButton_pressed(); break;
        case 40: _t->colormapCombo_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->InvertingCheckbox_released(); break;
        case 42: _t->clickedOnLogFile((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 43: _t->logRefreshButton_clicked(); break;
        case 44: _t->updateLogList(); break;
        case 45: _t->on_actionConnect_triggered(); break;
        case 46: _t->clickedOnImgFile((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 47: _t->updateImgList(); break;
        case 48: _t->loadImg(); break;
        case 49: _t->updateImage(); break;
        case 50: _t->on_actionDisconnect_triggered(); break;
        case 51: _t->minSliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->maxSliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 53: _t->minSliderMoved((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 54: _t->maxSliderMoved((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 55: _t->resetColormap(); break;
        case 56: _t->saveImg(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::showSettings)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sendAbortShutdownSignal)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sendAckSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sendDetectSystemSignal)) {
                *result = 3;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sendBeginProcessSignal)) {
                *result = 4;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sendBeginTransmittingDataSignal)) {
                *result = 5;
            }
        }
        {
            typedef void (MainWindow::*_t)(double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sendOrientationData)) {
                *result = 6;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::saveCsvFile)) {
                *result = 7;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 57)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 57;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 57)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 57;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::showSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MainWindow::sendAbortShutdownSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MainWindow::sendAckSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void MainWindow::sendDetectSystemSignal(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::sendBeginProcessSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void MainWindow::sendBeginTransmittingDataSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void MainWindow::sendOrientationData(double _t1, double _t2, double _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::saveCsvFile(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
