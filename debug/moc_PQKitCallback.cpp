/****************************************************************************
** Meta object code from reading C++ file 'PQKitCallback.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../PQKitCallback.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PQKitCallback.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CPQKitCallback_t {
    QByteArrayData data[26];
    char stringdata0[350];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPQKitCallback_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPQKitCallback_t qt_meta_stringdata_CPQKitCallback = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CPQKitCallback"
QT_MOC_LITERAL(1, 15, 22), // "signalInitializeResult"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 7), // "lResult"
QT_MOC_LITERAL(4, 47, 18), // "signalRunCMDResult"
QT_MOC_LITERAL(5, 66, 19), // "signalGetDataResult"
QT_MOC_LITERAL(6, 86, 21), // "signalRaiseDockwindow"
QT_MOC_LITERAL(7, 108, 7), // "i_nType"
QT_MOC_LITERAL(8, 116, 17), // "signalLoginResult"
QT_MOC_LITERAL(9, 134, 12), // "i_nLoginType"
QT_MOC_LITERAL(10, 147, 24), // "signalPathGenerateResult"
QT_MOC_LITERAL(11, 172, 10), // "i_bSuccess"
QT_MOC_LITERAL(12, 183, 12), // "i_nPathCount"
QT_MOC_LITERAL(13, 196, 8), // "i_nIndex"
QT_MOC_LITERAL(14, 205, 10), // "i_ulPathID"
QT_MOC_LITERAL(15, 216, 19), // "signalElementPickup"
QT_MOC_LITERAL(16, 236, 9), // "i_ulObjID"
QT_MOC_LITERAL(17, 246, 11), // "i_lEntityID"
QT_MOC_LITERAL(18, 258, 13), // "i_nEntityType"
QT_MOC_LITERAL(19, 272, 15), // "signalRButtonUp"
QT_MOC_LITERAL(20, 288, 7), // "i_lPosX"
QT_MOC_LITERAL(21, 296, 7), // "i_lPosY"
QT_MOC_LITERAL(22, 304, 15), // "signalLButtonUp"
QT_MOC_LITERAL(23, 320, 13), // "signalMenuPop"
QT_MOC_LITERAL(24, 334, 4), // "int*"
QT_MOC_LITERAL(25, 339, 10) // "o_nHandled"

    },
    "CPQKitCallback\0signalInitializeResult\0"
    "\0lResult\0signalRunCMDResult\0"
    "signalGetDataResult\0signalRaiseDockwindow\0"
    "i_nType\0signalLoginResult\0i_nLoginType\0"
    "signalPathGenerateResult\0i_bSuccess\0"
    "i_nPathCount\0i_nIndex\0i_ulPathID\0"
    "signalElementPickup\0i_ulObjID\0i_lEntityID\0"
    "i_nEntityType\0signalRButtonUp\0i_lPosX\0"
    "i_lPosY\0signalLButtonUp\0signalMenuPop\0"
    "int*\0o_nHandled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPQKitCallback[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       5,    1,   70,    2, 0x06 /* Public */,
       6,    1,   73,    2, 0x06 /* Public */,
       8,    1,   76,    2, 0x06 /* Public */,
      10,    4,   79,    2, 0x06 /* Public */,
      15,    3,   88,    2, 0x06 /* Public */,
      19,    2,   95,    2, 0x06 /* Public */,
      22,    2,  100,    2, 0x06 /* Public */,
      23,    4,  105,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Long,    3,
    QMetaType::Void, QMetaType::Long,    3,
    QMetaType::Void, QMetaType::Long,    3,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Long, QMetaType::Int, QMetaType::Int, QMetaType::ULong,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::ULong, QMetaType::Long, QMetaType::Int,   16,   17,   18,
    QMetaType::Void, QMetaType::Long, QMetaType::Long,   20,   21,
    QMetaType::Void, QMetaType::Long, QMetaType::Long,   20,   21,
    QMetaType::Void, QMetaType::ULong, QMetaType::Long, QMetaType::Long, 0x80000000 | 24,   16,   20,   21,   25,

       0        // eod
};

void CPQKitCallback::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CPQKitCallback *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalInitializeResult((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 1: _t->signalRunCMDResult((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 2: _t->signalGetDataResult((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 3: _t->signalRaiseDockwindow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signalLoginResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->signalPathGenerateResult((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< ulong(*)>(_a[4]))); break;
        case 6: _t->signalElementPickup((*reinterpret_cast< ulong(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->signalRButtonUp((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 8: _t->signalLButtonUp((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 9: _t->signalMenuPop((*reinterpret_cast< ulong(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3])),(*reinterpret_cast< int*(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CPQKitCallback::*)(long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPQKitCallback::signalInitializeResult)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CPQKitCallback::*)(long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPQKitCallback::signalRunCMDResult)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CPQKitCallback::*)(long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPQKitCallback::signalGetDataResult)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CPQKitCallback::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPQKitCallback::signalRaiseDockwindow)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CPQKitCallback::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPQKitCallback::signalLoginResult)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CPQKitCallback::*)(long , int , int , unsigned long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPQKitCallback::signalPathGenerateResult)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CPQKitCallback::*)(unsigned long , long , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPQKitCallback::signalElementPickup)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (CPQKitCallback::*)(long , long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPQKitCallback::signalRButtonUp)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (CPQKitCallback::*)(long , long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPQKitCallback::signalLButtonUp)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (CPQKitCallback::*)(unsigned long , long , long , int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CPQKitCallback::signalMenuPop)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CPQKitCallback::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CPQKitCallback.data,
    qt_meta_data_CPQKitCallback,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CPQKitCallback::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPQKitCallback::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CPQKitCallback.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IPQPlatformComponentCallBack"))
        return static_cast< IPQPlatformComponentCallBack*>(this);
    return QObject::qt_metacast(_clname);
}

int CPQKitCallback::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void CPQKitCallback::signalInitializeResult(long _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CPQKitCallback::signalRunCMDResult(long _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CPQKitCallback::signalGetDataResult(long _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CPQKitCallback::signalRaiseDockwindow(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CPQKitCallback::signalLoginResult(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CPQKitCallback::signalPathGenerateResult(long _t1, int _t2, int _t3, unsigned long _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CPQKitCallback::signalElementPickup(unsigned long _t1, long _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CPQKitCallback::signalRButtonUp(long _t1, long _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CPQKitCallback::signalLButtonUp(long _t1, long _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CPQKitCallback::signalMenuPop(unsigned long _t1, long _t2, long _t3, int * _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
