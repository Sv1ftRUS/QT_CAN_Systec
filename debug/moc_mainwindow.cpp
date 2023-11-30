/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[506];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 35), // "on_pushButton_Open_Sequence_c..."
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 26), // "on_pushButton_Send_clicked"
QT_MOC_LITERAL(4, 75, 27), // "on_pushButton_Clear_clicked"
QT_MOC_LITERAL(5, 103, 35), // "on_pushButton_Play_Sequence_c..."
QT_MOC_LITERAL(6, 139, 37), // "on_lineEdit_Tester_ID_editing..."
QT_MOC_LITERAL(7, 177, 39), // "on_lineEdit_Tracking_ID_editi..."
QT_MOC_LITERAL(8, 217, 34), // "on_lineEdit_ECU_ID_editingFin..."
QT_MOC_LITERAL(9, 252, 37), // "on_lineEdit_Send_Data_editing..."
QT_MOC_LITERAL(10, 290, 46), // "on_plainTextEdit_TesterECU_Ex..."
QT_MOC_LITERAL(11, 337, 19), // "on_CANStatusChanged"
QT_MOC_LITERAL(12, 357, 14), // "tStatusStruct*"
QT_MOC_LITERAL(13, 372, 9), // "pStatus_p"
QT_MOC_LITERAL(14, 382, 29), // "on_CANUSBConnectStatusChanged"
QT_MOC_LITERAL(15, 412, 8), // "bEvent_p"
QT_MOC_LITERAL(16, 421, 40), // "on_comboBox_BusSpeed_currentI..."
QT_MOC_LITERAL(17, 462, 5), // "index"
QT_MOC_LITERAL(18, 468, 37) // "on_comboBox_IDlen_currentInde..."

    },
    "MainWindow\0on_pushButton_Open_Sequence_clicked\0"
    "\0on_pushButton_Send_clicked\0"
    "on_pushButton_Clear_clicked\0"
    "on_pushButton_Play_Sequence_clicked\0"
    "on_lineEdit_Tester_ID_editingFinished\0"
    "on_lineEdit_Tracking_ID_editingFinished\0"
    "on_lineEdit_ECU_ID_editingFinished\0"
    "on_lineEdit_Send_Data_editingFinished\0"
    "on_plainTextEdit_TesterECU_Excahge_textChanged\0"
    "on_CANStatusChanged\0tStatusStruct*\0"
    "pStatus_p\0on_CANUSBConnectStatusChanged\0"
    "bEvent_p\0on_comboBox_BusSpeed_currentIndexChanged\0"
    "index\0on_comboBox_IDlen_currentIndexChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    1,   88,    2, 0x08 /* Private */,
      14,    1,   91,    2, 0x08 /* Private */,
      16,    1,   94,    2, 0x08 /* Private */,
      18,    1,   97,    2, 0x08 /* Private */,

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
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   17,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_Open_Sequence_clicked(); break;
        case 1: _t->on_pushButton_Send_clicked(); break;
        case 2: _t->on_pushButton_Clear_clicked(); break;
        case 3: _t->on_pushButton_Play_Sequence_clicked(); break;
        case 4: _t->on_lineEdit_Tester_ID_editingFinished(); break;
        case 5: _t->on_lineEdit_Tracking_ID_editingFinished(); break;
        case 6: _t->on_lineEdit_ECU_ID_editingFinished(); break;
        case 7: _t->on_lineEdit_Send_Data_editingFinished(); break;
        case 8: _t->on_plainTextEdit_TesterECU_Excahge_textChanged(); break;
        case 9: _t->on_CANStatusChanged((*reinterpret_cast< tStatusStruct*(*)>(_a[1]))); break;
        case 10: _t->on_CANUSBConnectStatusChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_comboBox_BusSpeed_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_comboBox_IDlen_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
struct qt_meta_stringdata_HexIntegerValidator_t {
    QByteArrayData data[1];
    char stringdata0[20];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HexIntegerValidator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HexIntegerValidator_t qt_meta_stringdata_HexIntegerValidator = {
    {
QT_MOC_LITERAL(0, 0, 19) // "HexIntegerValidator"

    },
    "HexIntegerValidator"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HexIntegerValidator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void HexIntegerValidator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject HexIntegerValidator::staticMetaObject = { {
    QMetaObject::SuperData::link<QValidator::staticMetaObject>(),
    qt_meta_stringdata_HexIntegerValidator.data,
    qt_meta_data_HexIntegerValidator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HexIntegerValidator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HexIntegerValidator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HexIntegerValidator.stringdata0))
        return static_cast<void*>(this);
    return QValidator::qt_metacast(_clname);
}

int HexIntegerValidator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QValidator::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_HexStringValidator_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HexStringValidator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HexStringValidator_t qt_meta_stringdata_HexStringValidator = {
    {
QT_MOC_LITERAL(0, 0, 18) // "HexStringValidator"

    },
    "HexStringValidator"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HexStringValidator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void HexStringValidator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject HexStringValidator::staticMetaObject = { {
    QMetaObject::SuperData::link<QValidator::staticMetaObject>(),
    qt_meta_stringdata_HexStringValidator.data,
    qt_meta_data_HexStringValidator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HexStringValidator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HexStringValidator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HexStringValidator.stringdata0))
        return static_cast<void*>(this);
    return QValidator::qt_metacast(_clname);
}

int HexStringValidator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QValidator::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
