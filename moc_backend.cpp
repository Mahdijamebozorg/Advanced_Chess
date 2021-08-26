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
    QByteArrayData data[57];
    char stringdata0[568];
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
QT_MOC_LITERAL(3, 17, 5), // "moved"
QT_MOC_LITERAL(4, 23, 9), // "unchoosen"
QT_MOC_LITERAL(5, 33, 9), // "promotion"
QT_MOC_LITERAL(6, 43, 6), // "cancel"
QT_MOC_LITERAL(7, 50, 7), // "setGame"
QT_MOC_LITERAL(8, 58, 8), // "gameName"
QT_MOC_LITERAL(9, 67, 9), // "startGame"
QT_MOC_LITERAL(10, 77, 11), // "restartGame"
QT_MOC_LITERAL(11, 89, 7), // "endGame"
QT_MOC_LITERAL(12, 97, 9), // "loadFiles"
QT_MOC_LITERAL(13, 107, 11), // "getFileName"
QT_MOC_LITERAL(14, 119, 5), // "index"
QT_MOC_LITERAL(15, 125, 18), // "getFilePlayersName"
QT_MOC_LITERAL(16, 144, 8), // "loadGame"
QT_MOC_LITERAL(17, 153, 10), // "filesCount"
QT_MOC_LITERAL(18, 164, 10), // "gameStatus"
QT_MOC_LITERAL(19, 175, 5), // "setP1"
QT_MOC_LITERAL(20, 181, 6), // "P1Name"
QT_MOC_LITERAL(21, 188, 5), // "setP2"
QT_MOC_LITERAL(22, 194, 6), // "P2Name"
QT_MOC_LITERAL(23, 201, 9), // "getP1Name"
QT_MOC_LITERAL(24, 211, 9), // "getP2Name"
QT_MOC_LITERAL(25, 221, 12), // "getP1_PScore"
QT_MOC_LITERAL(26, 234, 12), // "getP1_NScore"
QT_MOC_LITERAL(27, 247, 12), // "getP2_PScore"
QT_MOC_LITERAL(28, 260, 12), // "getP2_NScore"
QT_MOC_LITERAL(29, 273, 11), // "getGameName"
QT_MOC_LITERAL(30, 285, 6), // "winner"
QT_MOC_LITERAL(31, 292, 15), // "checkRandomMove"
QT_MOC_LITERAL(32, 308, 11), // "setCanceler"
QT_MOC_LITERAL(33, 320, 11), // "getCanceler"
QT_MOC_LITERAL(34, 332, 7), // "getIcon"
QT_MOC_LITERAL(35, 340, 9), // "cellState"
QT_MOC_LITERAL(36, 350, 7), // "isMoved"
QT_MOC_LITERAL(37, 358, 7), // "getSrcI"
QT_MOC_LITERAL(38, 366, 7), // "getSrcJ"
QT_MOC_LITERAL(39, 374, 8), // "getDestI"
QT_MOC_LITERAL(40, 383, 8), // "getDestJ"
QT_MOC_LITERAL(41, 392, 11), // "getSrcIndex"
QT_MOC_LITERAL(42, 404, 12), // "getDestIndex"
QT_MOC_LITERAL(43, 417, 6), // "canHit"
QT_MOC_LITERAL(44, 424, 34), // "std::vector<std::pair<uint,ui..."
QT_MOC_LITERAL(45, 459, 9), // "bkndcanGo"
QT_MOC_LITERAL(46, 469, 5), // "canGo"
QT_MOC_LITERAL(47, 475, 6), // "choose"
QT_MOC_LITERAL(48, 482, 13), // "unchoosePiece"
QT_MOC_LITERAL(49, 496, 13), // "getP1OutsIcon"
QT_MOC_LITERAL(50, 510, 13), // "getP2OutsIcon"
QT_MOC_LITERAL(51, 524, 4), // "move"
QT_MOC_LITERAL(52, 529, 4), // "undo"
QT_MOC_LITERAL(53, 534, 9), // "extraMove"
QT_MOC_LITERAL(54, 544, 10), // "randomMove"
QT_MOC_LITERAL(55, 555, 7), // "promote"
QT_MOC_LITERAL(56, 563, 4) // "type"

    },
    "BackEnd\0choosen\0\0moved\0unchoosen\0"
    "promotion\0cancel\0setGame\0gameName\0"
    "startGame\0restartGame\0endGame\0loadFiles\0"
    "getFileName\0index\0getFilePlayersName\0"
    "loadGame\0filesCount\0gameStatus\0setP1\0"
    "P1Name\0setP2\0P2Name\0getP1Name\0getP2Name\0"
    "getP1_PScore\0getP1_NScore\0getP2_PScore\0"
    "getP2_NScore\0getGameName\0winner\0"
    "checkRandomMove\0setCanceler\0getCanceler\0"
    "getIcon\0cellState\0isMoved\0getSrcI\0"
    "getSrcJ\0getDestI\0getDestJ\0getSrcIndex\0"
    "getDestIndex\0canHit\0"
    "std::vector<std::pair<uint,uint> >\0"
    "bkndcanGo\0canGo\0choose\0unchoosePiece\0"
    "getP1OutsIcon\0getP2OutsIcon\0move\0undo\0"
    "extraMove\0randomMove\0promote\0type"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackEnd[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      48,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  254,    2, 0x06 /* Public */,
       3,    0,  255,    2, 0x06 /* Public */,
       4,    0,  256,    2, 0x06 /* Public */,
       5,    0,  257,    2, 0x06 /* Public */,
       6,    0,  258,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,  259,    2, 0x0a /* Public */,
       9,    0,  262,    2, 0x0a /* Public */,
      10,    0,  263,    2, 0x0a /* Public */,
      11,    0,  264,    2, 0x0a /* Public */,
      12,    0,  265,    2, 0x0a /* Public */,
      13,    1,  266,    2, 0x0a /* Public */,
      15,    1,  269,    2, 0x0a /* Public */,
      16,    1,  272,    2, 0x0a /* Public */,
      17,    0,  275,    2, 0x0a /* Public */,
      18,    0,  276,    2, 0x0a /* Public */,
      19,    1,  277,    2, 0x0a /* Public */,
      21,    1,  280,    2, 0x0a /* Public */,
      23,    0,  283,    2, 0x0a /* Public */,
      24,    0,  284,    2, 0x0a /* Public */,
      25,    0,  285,    2, 0x0a /* Public */,
      26,    0,  286,    2, 0x0a /* Public */,
      27,    0,  287,    2, 0x0a /* Public */,
      28,    0,  288,    2, 0x0a /* Public */,
      29,    0,  289,    2, 0x0a /* Public */,
      30,    0,  290,    2, 0x0a /* Public */,
      31,    0,  291,    2, 0x0a /* Public */,
      32,    0,  292,    2, 0x0a /* Public */,
      33,    0,  293,    2, 0x0a /* Public */,
      34,    1,  294,    2, 0x0a /* Public */,
      35,    1,  297,    2, 0x0a /* Public */,
      36,    1,  300,    2, 0x0a /* Public */,
      37,    0,  303,    2, 0x0a /* Public */,
      38,    0,  304,    2, 0x0a /* Public */,
      39,    0,  305,    2, 0x0a /* Public */,
      40,    0,  306,    2, 0x0a /* Public */,
      41,    0,  307,    2, 0x0a /* Public */,
      42,    0,  308,    2, 0x0a /* Public */,
      43,    2,  309,    2, 0x0a /* Public */,
      46,    2,  314,    2, 0x0a /* Public */,
      47,    1,  319,    2, 0x0a /* Public */,
      48,    1,  322,    2, 0x0a /* Public */,
      49,    1,  325,    2, 0x0a /* Public */,
      50,    1,  328,    2, 0x0a /* Public */,
      51,    1,  331,    2, 0x0a /* Public */,
      52,    0,  334,    2, 0x0a /* Public */,
      53,    0,  335,    2, 0x0a /* Public */,
      54,    0,  336,    2, 0x0a /* Public */,
      55,    1,  337,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, QMetaType::UInt,   14,
    QMetaType::QString, QMetaType::UInt,   14,
    QMetaType::Bool, QMetaType::QString,    2,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::UInt,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::UInt,
    QMetaType::QString, QMetaType::UInt,   14,
    QMetaType::UInt, QMetaType::UInt,   14,
    QMetaType::Bool, QMetaType::UInt,   14,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::Bool, QMetaType::UInt, 0x80000000 | 44,   14,   45,
    QMetaType::Bool, QMetaType::UInt, 0x80000000 | 44,   14,   45,
    QMetaType::UInt, QMetaType::UInt,   14,
    QMetaType::Bool, QMetaType::UInt,   14,
    QMetaType::QString, QMetaType::UInt,   14,
    QMetaType::QString, QMetaType::UInt,   14,
    QMetaType::Bool, QMetaType::UInt,   14,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,   56,

       0        // eod
};

void BackEnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BackEnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->choosen(); break;
        case 1: _t->moved(); break;
        case 2: _t->unchoosen(); break;
        case 3: _t->promotion(); break;
        case 4: _t->cancel(); break;
        case 5: _t->setGame((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->startGame(); break;
        case 7: _t->restartGame(); break;
        case 8: _t->endGame(); break;
        case 9: _t->loadFiles(); break;
        case 10: { QString _r = _t->getFileName((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->getFilePlayersName((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->loadGame((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { uint _r = _t->filesCount();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 14: { uint _r = _t->gameStatus();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->setP1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->setP2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: { QString _r = _t->getP1Name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 18: { QString _r = _t->getP2Name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 19: { int _r = _t->getP1_PScore();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 20: { int _r = _t->getP1_NScore();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 21: { int _r = _t->getP2_PScore();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 22: { int _r = _t->getP2_NScore();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 23: { QString _r = _t->getGameName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 24: { uint _r = _t->winner();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 25: _t->checkRandomMove(); break;
        case 26: _t->setCanceler(); break;
        case 27: { uint _r = _t->getCanceler();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 28: { QString _r = _t->getIcon((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 29: { uint _r = _t->cellState((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 30: { bool _r = _t->isMoved((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 31: { uint _r = _t->getSrcI();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 32: { uint _r = _t->getSrcJ();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 33: { uint _r = _t->getDestI();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 34: { uint _r = _t->getDestJ();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 35: { uint _r = _t->getSrcIndex();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 36: { uint _r = _t->getDestIndex();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 37: { bool _r = _t->canHit((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::vector<std::pair<uint,uint> >(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 38: { bool _r = _t->canGo((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::vector<std::pair<uint,uint> >(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 39: { uint _r = _t->choose((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 40: { bool _r = _t->unchoosePiece((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 41: { QString _r = _t->getP1OutsIcon((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 42: { QString _r = _t->getP2OutsIcon((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 43: { bool _r = _t->move((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 44: _t->undo(); break;
        case 45: { bool _r = _t->extraMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 46: _t->randomMove(); break;
        case 47: _t->promote((*reinterpret_cast< uint(*)>(_a[1]))); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::moved)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::unchoosen)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::promotion)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::cancel)) {
                *result = 4;
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
        if (_id < 48)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 48;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 48)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 48;
    }
    return _id;
}

// SIGNAL 0
void BackEnd::choosen()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BackEnd::moved()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BackEnd::unchoosen()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void BackEnd::promotion()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void BackEnd::cancel()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
