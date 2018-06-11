/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Roboter/inc/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[41];
    char stringdata0[1207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "closeEvent"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "QCloseEvent*"
QT_MOC_LITERAL(4, 36, 1), // "e"
QT_MOC_LITERAL(5, 38, 19), // "timerFunctionUpdate"
QT_MOC_LITERAL(6, 58, 13), // "timerFunction"
QT_MOC_LITERAL(7, 72, 15), // "timerFunction1s"
QT_MOC_LITERAL(8, 88, 15), // "timerFunction5s"
QT_MOC_LITERAL(9, 104, 20), // "timerFunctionRandGen"
QT_MOC_LITERAL(10, 125, 27), // "ticksPerSecondTimerFunction"
QT_MOC_LITERAL(11, 153, 31), // "on_RightSpeedSlder_valueChanged"
QT_MOC_LITERAL(12, 185, 5), // "value"
QT_MOC_LITERAL(13, 191, 28), // "on_LeftSpeedSlider_destroyed"
QT_MOC_LITERAL(14, 220, 31), // "on_LeftSpeedSlider_valueChanged"
QT_MOC_LITERAL(15, 252, 36), // "on_net_control_toggle_button_..."
QT_MOC_LITERAL(16, 289, 34), // "on_net_control_kill_button_cl..."
QT_MOC_LITERAL(17, 324, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(18, 346, 37), // "on_MutationFactor_Slider_valu..."
QT_MOC_LITERAL(19, 384, 39), // "on_drawNetXDistance_slider_va..."
QT_MOC_LITERAL(20, 424, 39), // "on_drawNetYDistance_slider_va..."
QT_MOC_LITERAL(21, 464, 37), // "on_drawNeuronSize_slider_valu..."
QT_MOC_LITERAL(22, 502, 41), // "on_drawConnectionSize_slider_..."
QT_MOC_LITERAL(23, 544, 33), // "on_drawAnimal_slider_valueCha..."
QT_MOC_LITERAL(24, 578, 36), // "on_robotPathSize_slider_value..."
QT_MOC_LITERAL(25, 615, 45), // "on_net_control_beamLength_sli..."
QT_MOC_LITERAL(26, 661, 49), // "on_net_control_obsticleAmount..."
QT_MOC_LITERAL(27, 711, 43), // "on_net_control_addSpeed_slide..."
QT_MOC_LITERAL(28, 755, 38), // "on_MutationDivisor_Slider_val..."
QT_MOC_LITERAL(29, 794, 11), // "resizeEvent"
QT_MOC_LITERAL(30, 806, 13), // "QResizeEvent*"
QT_MOC_LITERAL(31, 820, 5), // "event"
QT_MOC_LITERAL(32, 826, 51), // "on_net_control_speedMultiplay..."
QT_MOC_LITERAL(33, 878, 50), // "on_net_control_speedMultiplay..."
QT_MOC_LITERAL(34, 929, 50), // "on_net_control_speedMultiplay..."
QT_MOC_LITERAL(35, 980, 50), // "on_net_control_speedMultiplay..."
QT_MOC_LITERAL(36, 1031, 51), // "on_net_control_speedMultiplay..."
QT_MOC_LITERAL(37, 1083, 37), // "on_displayInputValue_checkBox..."
QT_MOC_LITERAL(38, 1121, 7), // "checked"
QT_MOC_LITERAL(39, 1129, 38), // "on_displayHiddenValue_checkBo..."
QT_MOC_LITERAL(40, 1168, 38) // "on_displayOutputValue_checkBo..."

    },
    "MainWindow\0closeEvent\0\0QCloseEvent*\0"
    "e\0timerFunctionUpdate\0timerFunction\0"
    "timerFunction1s\0timerFunction5s\0"
    "timerFunctionRandGen\0ticksPerSecondTimerFunction\0"
    "on_RightSpeedSlder_valueChanged\0value\0"
    "on_LeftSpeedSlider_destroyed\0"
    "on_LeftSpeedSlider_valueChanged\0"
    "on_net_control_toggle_button_clicked\0"
    "on_net_control_kill_button_clicked\0"
    "on_pushButton_clicked\0"
    "on_MutationFactor_Slider_valueChanged\0"
    "on_drawNetXDistance_slider_valueChanged\0"
    "on_drawNetYDistance_slider_valueChanged\0"
    "on_drawNeuronSize_slider_valueChanged\0"
    "on_drawConnectionSize_slider_valueChanged\0"
    "on_drawAnimal_slider_valueChanged\0"
    "on_robotPathSize_slider_valueChanged\0"
    "on_net_control_beamLength_slider_valueChanged\0"
    "on_net_control_obsticleAmount_slider_valueChanged\0"
    "on_net_control_addSpeed_slider_valueChanged\0"
    "on_MutationDivisor_Slider_valueChanged\0"
    "resizeEvent\0QResizeEvent*\0event\0"
    "on_net_control_speedMultiplayerToOne_button_clicked\0"
    "on_net_control_speedMultiplayerTo10_button_clicked\0"
    "on_net_control_speedMultiplayerTo30_button_clicked\0"
    "on_net_control_speedMultiplayerTo60_button_clicked\0"
    "on_net_control_speedMultiplayerTo100_button_clicked\0"
    "on_displayInputValue_checkBox_toggled\0"
    "checked\0on_displayHiddenValue_checkBox_toggled\0"
    "on_displayOutputValue_checkBox_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  179,    2, 0x08 /* Private */,
       5,    0,  182,    2, 0x08 /* Private */,
       6,    0,  183,    2, 0x08 /* Private */,
       7,    0,  184,    2, 0x08 /* Private */,
       8,    0,  185,    2, 0x08 /* Private */,
       9,    0,  186,    2, 0x08 /* Private */,
      10,    0,  187,    2, 0x08 /* Private */,
      11,    1,  188,    2, 0x08 /* Private */,
      13,    0,  191,    2, 0x08 /* Private */,
      14,    1,  192,    2, 0x08 /* Private */,
      15,    0,  195,    2, 0x08 /* Private */,
      16,    0,  196,    2, 0x08 /* Private */,
      17,    0,  197,    2, 0x08 /* Private */,
      18,    1,  198,    2, 0x08 /* Private */,
      19,    1,  201,    2, 0x08 /* Private */,
      20,    1,  204,    2, 0x08 /* Private */,
      21,    1,  207,    2, 0x08 /* Private */,
      22,    1,  210,    2, 0x08 /* Private */,
      23,    1,  213,    2, 0x08 /* Private */,
      24,    1,  216,    2, 0x08 /* Private */,
      25,    1,  219,    2, 0x08 /* Private */,
      26,    1,  222,    2, 0x08 /* Private */,
      27,    1,  225,    2, 0x08 /* Private */,
      28,    1,  228,    2, 0x08 /* Private */,
      29,    1,  231,    2, 0x08 /* Private */,
      32,    0,  234,    2, 0x08 /* Private */,
      33,    0,  235,    2, 0x08 /* Private */,
      34,    0,  236,    2, 0x08 /* Private */,
      35,    0,  237,    2, 0x08 /* Private */,
      36,    0,  238,    2, 0x08 /* Private */,
      37,    1,  239,    2, 0x08 /* Private */,
      39,    1,  242,    2, 0x08 /* Private */,
      40,    1,  245,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   38,
    QMetaType::Void, QMetaType::Bool,   38,
    QMetaType::Void, QMetaType::Bool,   38,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 1: _t->timerFunctionUpdate(); break;
        case 2: _t->timerFunction(); break;
        case 3: _t->timerFunction1s(); break;
        case 4: _t->timerFunction5s(); break;
        case 5: _t->timerFunctionRandGen(); break;
        case 6: _t->ticksPerSecondTimerFunction(); break;
        case 7: _t->on_RightSpeedSlder_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_LeftSpeedSlider_destroyed(); break;
        case 9: _t->on_LeftSpeedSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_net_control_toggle_button_clicked(); break;
        case 11: _t->on_net_control_kill_button_clicked(); break;
        case 12: _t->on_pushButton_clicked(); break;
        case 13: _t->on_MutationFactor_Slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_drawNetXDistance_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_drawNetYDistance_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_drawNeuronSize_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_drawConnectionSize_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_drawAnimal_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_robotPathSize_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->on_net_control_beamLength_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->on_net_control_obsticleAmount_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->on_net_control_addSpeed_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->on_MutationDivisor_Slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 25: _t->on_net_control_speedMultiplayerToOne_button_clicked(); break;
        case 26: _t->on_net_control_speedMultiplayerTo10_button_clicked(); break;
        case 27: _t->on_net_control_speedMultiplayerTo30_button_clicked(); break;
        case 28: _t->on_net_control_speedMultiplayerTo60_button_clicked(); break;
        case 29: _t->on_net_control_speedMultiplayerTo100_button_clicked(); break;
        case 30: _t->on_displayInputValue_checkBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->on_displayHiddenValue_checkBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->on_displayOutputValue_checkBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 33;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
