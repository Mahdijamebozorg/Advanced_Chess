/****************************************************************************
** Meta object code from reading C++ file 'backend.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "backend.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backend.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BackEnd_t {
    QByteArrayData data[20];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BackEnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BackEnd_t qt_meta_stringdata_BackEnd = {
    {
QT_MOC_LITERAL(0, 0, 7), // "BackEnd"
QT_MOC_LITERAL(1, 8, 7), // "choosen"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 8), // "unchoose"
QT_MOC_LITERAL(4, 26, 9), // "getP1Name"
QT_MOC_LITERAL(5, 36, 6), // "P1Name"
QT_MOC_LITERAL(6, 43, 9), // "getP2Name"
QT_MOC_LITERAL(7, 53, 6), // "P2Name"
QT_MOC_LITERAL(8, 60, 11), // "getGameName"
QT_MOC_LITERAL(9, 72, 8), // "GameName"
QT_MOC_LITERAL(10, 81, 7), // "getIcon"
QT_MOC_LITERAL(11, 89, 5), // "index"
QT_MOC_LITERAL(12, 95, 6), // "choose"
QT_MOC_LITERAL(13, 102, 9), // "cellState"
QT_MOC_LITERAL(14, 112, 5), // "canGo"
QT_MOC_LITERAL(15, 118, 17), // "std::vector<uint>"
QT_MOC_LITERAL(16, 136, 9), // "bkndcanGo"
QT_MOC_LITERAL(17, 146, 6), // "canHit"
QT_MOC_LITERAL(18, 153, 4), // "move"
QT_MOC_LITERAL(19, 158, 13) // "unchoosePiece"

    },
    "BackEnd\0choosen\0\0unchoose\0getP1Name\0"
    "P1Name\0getP2Name\0P2Name\0getGameName\0"
    "GameName\0getIcon\0index\0choose\0cellState\0"
    "canGo\0std::vector<uint>\0bkndcanGo\0"
    "canHit\0move\0unchoosePiece"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackEnd[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   76,    2, 0x0a /* Public */,
       6,    1,   79,    2, 0x0a /* Public */,
       8,    1,   82,    2, 0x0a /* Public */,
      10,    1,   85,    2, 0x0a /* Public */,
      12,    1,   88,    2, 0x0a /* Public */,
      13,    0,   91,    2, 0x0a /* Public */,
      14,    2,   92,    2, 0x0a /* Public */,
      17,    2,   97,    2, 0x0a /* Public */,
      18,    1,  102,    2, 0x0a /* Public */,
      19,    1,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::QString, QMetaType::UInt,   11,
    QMetaType::Void, QMetaType::UInt,   11,
    QMetaType::UInt,
    QMetaType::Bool, QMetaType::UInt, 0x80000000 | 15,   11,   16,
    QMetaType::Bool, QMetaType::UInt, 0x80000000 | 15,   11,   16,
    QMetaType::Void, QMetaType::UInt,   11,
    QMetaType::Bool, QMetaType::UInt,   11,

       0        // eod
};

void BackEnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BackEnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->choosen(); break;
        case 1: _t->unchoose(); break;
        case 2: _t->getP1Name((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->getP2Name((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->getGameName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: { QString _r = _t->getIcon((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->choose((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 7: { uint _r = _t->cellState();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->canGo((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::vector<uint>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->canHit((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::vector<uint>(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->move((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 11: { bool _r = _t->unchoosePiece((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BackEnd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::choosen)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::unchoose)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BackEnd::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_BackEnd.data,
    qt_meta_data_BackEnd,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BackEnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackEnd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BackEnd.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BackEnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void BackEnd::choosen()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BackEnd::unchoose()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
