/****************************************************************************
** Meta object code from reading C++ file 'AnalyticThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "AnalyticThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnalyticThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CAnalyticThread_t {
    QByteArrayData data[10];
    char stringdata[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CAnalyticThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CAnalyticThread_t qt_meta_stringdata_CAnalyticThread = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 18),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 4),
QT_MOC_LITERAL(4, 41, 3),
QT_MOC_LITERAL(5, 45, 10),
QT_MOC_LITERAL(6, 56, 1),
QT_MOC_LITERAL(7, 58, 1),
QT_MOC_LITERAL(8, 60, 6),
QT_MOC_LITERAL(9, 67, 12)
    },
    "CAnalyticThread\0sendThresholdedImg\0\0"
    "PMat\0img\0sendCircle\0x\0y\0radius\0"
    "analyseImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CAnalyticThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    3,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    6,    7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void CAnalyticThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CAnalyticThread *_t = static_cast<CAnalyticThread *>(_o);
        switch (_id) {
        case 0: _t->sendThresholdedImg((*reinterpret_cast< PMat(*)>(_a[1]))); break;
        case 1: _t->sendCircle((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->analyseImage((*reinterpret_cast< PMat(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PMat >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PMat >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CAnalyticThread::*_t)(PMat );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CAnalyticThread::sendThresholdedImg)) {
                *result = 0;
            }
        }
        {
            typedef void (CAnalyticThread::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CAnalyticThread::sendCircle)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject CAnalyticThread::staticMetaObject = {
    { &CThreadImpl::staticMetaObject, qt_meta_stringdata_CAnalyticThread.data,
      qt_meta_data_CAnalyticThread,  qt_static_metacall, 0, 0}
};


const QMetaObject *CAnalyticThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CAnalyticThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CAnalyticThread.stringdata))
        return static_cast<void*>(const_cast< CAnalyticThread*>(this));
    return CThreadImpl::qt_metacast(_clname);
}

int CAnalyticThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CThreadImpl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CAnalyticThread::sendThresholdedImg(PMat _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CAnalyticThread::sendCircle(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE