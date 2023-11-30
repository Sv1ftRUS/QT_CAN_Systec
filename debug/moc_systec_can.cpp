/****************************************************************************
** Meta object code from reading C++ file 'systec_can.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../systec_can.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'systec_can.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Systec_CAN_t {
    QByteArrayData data[5];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Systec_CAN_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Systec_CAN_t qt_meta_stringdata_Systec_CAN = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Systec_CAN"
QT_MOC_LITERAL(1, 11, 16), // "CANStatusChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 14), // "tStatusStruct*"
QT_MOC_LITERAL(4, 44, 26) // "CANUSBConnectStatusChanged"

    },
    "Systec_CAN\0CANStatusChanged\0\0"
    "tStatusStruct*\0CANUSBConnectStatusChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Systec_CAN[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Systec_CAN::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Systec_CAN *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CANStatusChanged((*reinterpret_cast< tStatusStruct*(*)>(_a[1]))); break;
        case 1: _t->CANUSBConnectStatusChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Systec_CAN::*)(tStatusStruct * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Systec_CAN::CANStatusChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Systec_CAN::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Systec_CAN::CANUSBConnectStatusChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Systec_CAN::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Systec_CAN.data,
    qt_meta_data_Systec_CAN,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Systec_CAN::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Systec_CAN::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Systec_CAN.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Systec_CAN::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Systec_CAN::CANStatusChanged(tStatusStruct * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Systec_CAN::CANUSBConnectStatusChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
