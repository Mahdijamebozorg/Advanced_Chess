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
    QByteArrayData data[29];
    char stringdata0[281];
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
QT_MOC_LITERAL(3, 17, 9), // "unchoosen"
QT_MOC_LITERAL(4, 27, 9), // "startGame"
QT_MOC_LITERAL(5, 37, 5), // "setP1"
QT_MOC_LITERAL(6, 43, 6), // "P1Name"
QT_MOC_LITERAL(7, 50, 5), // "setP2"
QT_MOC_LITERAL(8, 56, 6), // "P2Name"
QT_MOC_LITERAL(9, 63, 11), // "setGameName"
QT_MOC_LITERAL(10, 75, 8), // "GameName"
QT_MOC_LITERAL(11, 84, 9), // "getP1Name"
QT_MOC_LITERAL(12, 94, 9), // "getP2Name"
QT_MOC_LITERAL(13, 104, 12), // "getP1_PScore"
QT_MOC_LITERAL(14, 117, 12), // "getP1_NScore"
QT_MOC_LITERAL(15, 130, 12), // "getP2_PScore"
QT_MOC_LITERAL(16, 143, 12), // "getP2_NScore"
QT_MOC_LITERAL(17, 156, 11), // "getGameName"
QT_MOC_LITERAL(18, 168, 7), // "getIcon"
QT_MOC_LITERAL(19, 176, 5), // "index"
QT_MOC_LITERAL(20, 182, 6), // "choose"
QT_MOC_LITERAL(21, 189, 9), // "cellState"
QT_MOC_LITERAL(22, 199, 5), // "canGo"
QT_MOC_LITERAL(23, 205, 34), // "std::vector<std::pair<uint,ui..."
QT_MOC_LITERAL(24, 240, 9), // "bkndcanGo"
QT_MOC_LITERAL(25, 250, 6), // "canHit"
QT_MOC_LITERAL(26, 257, 4), // "move"
QT_MOC_LITERAL(27, 262, 13), // "unchoosePiece"
QT_MOC_LITERAL(28, 276, 4) // "undo"

    },
    "BackEnd\0choosen\0\0unchoosen\0startGame\0"
    "setP1\0P1Name\0setP2\0P2Name\0setGameName\0"
    "GameName\0getP1Name\0getP2Name\0getP1_PScore\0"
    "getP1_NScore\0getP2_PScore\0getP2_NScore\0"
    "getGameName\0getIcon\0index\0choose\0"
    "cellState\0canGo\0std::vector<std::pair<uint,uint> >\0"
    "bkndcanGo\0canHit\0move\0unchoosePiece\0"
    "undo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackEnd[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x06 /* Public */,
       3,    0,  120,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
<<<<<<< HEAD
       4,    0,  121,    2, 0x0a /* Public */,
       5,    1,  122,    2, 0x0a /* Public */,
       7,    1,  125,    2, 0x0a /* Public */,
       9,    1,  128,    2, 0x0a /* Public */,
      11,    0,  131,    2, 0x0a /* Public */,
      12,    0,  132,    2, 0x0a /* Public */,
      13,    0,  133,    2, 0x0a /* Public */,
      14,    0,  134,    2, 0x0a /* Public */,
      15,    0,  135,    2, 0x0a /* Public */,
      16,    0,  136,    2, 0x0a /* Public */,
      17,    0,  137,    2, 0x0a /* Public */,
      18,    1,  138,    2, 0x0a /* Public */,
      20,    1,  141,    2, 0x0a /* Public */,
      21,    1,  144,    2, 0x0a /* Public */,
      22,    2,  147,    2, 0x0a /* Public */,
      25,    2,  152,    2, 0x0a /* Public */,
      26,    1,  157,    2, 0x0a /* Public */,
      27,    1,  160,    2, 0x0a /* Public */,
      28,    0,  163,    2, 0x0a /* Public */,
=======
       4,    0,  116,    2, 0x0a /* Public */,
       5,    1,  117,    2, 0x0a /* Public */,
       7,    1,  120,    2, 0x0a /* Public */,
       9,    1,  123,    2, 0x0a /* Public */,
      11,    0,  126,    2, 0x0a /* Public */,
      12,    0,  127,    2, 0x0a /* Public */,
      13,    0,  128,    2, 0x0a /* Public */,
      14,    0,  129,    2, 0x0a /* Public */,
      15,    0,  130,    2, 0x0a /* Public */,
      16,    0,  131,    2, 0x0a /* Public */,
      17,    0,  132,    2, 0x0a /* Public */,
      18,    1,  133,    2, 0x0a /* Public */,
      20,    1,  136,    2, 0x0a /* Public */,
      21,    1,  139,    2, 0x0a /* Public */,
      22,    2,  142,    2, 0x0a /* Public */,
      25,    2,  147,    2, 0x0a /* Public */,
      26,    1,  152,    2, 0x0a /* Public */,
      27,    1,  155,    2, 0x0a /* Public */,
>>>>>>> 255f95ab2c52e92d509f212bc0932fa0a99aea62

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::QString,
    QMetaType::QString, QMetaType::UInt,   19,
    QMetaType::UInt, QMetaType::UInt,   19,
    QMetaType::UInt, QMetaType::UInt,   19,
    QMetaType::Bool, QMetaType::UInt, 0x80000000 | 23,   19,   24,
    QMetaType::Bool, QMetaType::UInt, 0x80000000 | 23,   19,   24,
    QMetaType::Bool, QMetaType::UInt,   19,
    QMetaType::Bool, QMetaType::UInt,   19,
    QMetaType::Void,

       0        // eod
};

void BackEnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BackEnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->choosen(); break;
        case 1: _t->unchoosen(); break;
        case 2: _t->startGame(); break;
        case 3: _t->setP1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->setP2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->setGameName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: { QString _r = _t->getP1Name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 7: { QString _r = _t->getP2Name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 8: { uint _r = _t->getP1_PScore();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 9: { uint _r = _t->getP1_NScore();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 10: { uint _r = _t->getP2_PScore();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 11: { uint _r = _t->getP2_NScore();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 12: { QString _r = _t->getGameName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 13: { QString _r = _t->getIcon((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 14: { uint _r = _t->choose((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 15: { uint _r = _t->cellState((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 16: { bool _r = _t->canGo((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::vector<std::pair<uint,uint> >(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 17: { bool _r = _t->canHit((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::vector<std::pair<uint,uint> >(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 18: { bool _r = _t->move((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: { bool _r = _t->unchoosePiece((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 20: _t->undo(); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::unchoosen)) {
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
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void BackEnd::choosen()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BackEnd::unchoosen()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
