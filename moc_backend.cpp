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
    QByteArrayData data[59];
    char stringdata0[581];
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
QT_MOC_LITERAL(7, 50, 9), // "fileError"
QT_MOC_LITERAL(8, 60, 10), // "gameLoaded"
QT_MOC_LITERAL(9, 71, 7), // "setGame"
QT_MOC_LITERAL(10, 79, 8), // "gameName"
QT_MOC_LITERAL(11, 88, 9), // "startGame"
QT_MOC_LITERAL(12, 98, 11), // "restartGame"
QT_MOC_LITERAL(13, 110, 11), // "saveAndExit"
QT_MOC_LITERAL(14, 122, 7), // "endGame"
QT_MOC_LITERAL(15, 130, 10), // "gameStatus"
QT_MOC_LITERAL(16, 141, 8), // "getFiles"
QT_MOC_LITERAL(17, 150, 11), // "getFileInfo"
QT_MOC_LITERAL(18, 162, 5), // "index"
QT_MOC_LITERAL(19, 168, 8), // "loadGame"
QT_MOC_LITERAL(20, 177, 10), // "filesCount"
QT_MOC_LITERAL(21, 188, 5), // "setP1"
QT_MOC_LITERAL(22, 194, 6), // "P1Name"
QT_MOC_LITERAL(23, 201, 5), // "setP2"
QT_MOC_LITERAL(24, 207, 6), // "P2Name"
QT_MOC_LITERAL(25, 214, 9), // "getP1Name"
QT_MOC_LITERAL(26, 224, 9), // "getP2Name"
QT_MOC_LITERAL(27, 234, 12), // "getP1_PScore"
QT_MOC_LITERAL(28, 247, 12), // "getP1_NScore"
QT_MOC_LITERAL(29, 260, 12), // "getP2_PScore"
QT_MOC_LITERAL(30, 273, 12), // "getP2_NScore"
QT_MOC_LITERAL(31, 286, 11), // "getGameName"
QT_MOC_LITERAL(32, 298, 6), // "winner"
QT_MOC_LITERAL(33, 305, 15), // "checkRandomMove"
QT_MOC_LITERAL(34, 321, 11), // "setCanceler"
QT_MOC_LITERAL(35, 333, 11), // "getCanceler"
QT_MOC_LITERAL(36, 345, 7), // "getIcon"
QT_MOC_LITERAL(37, 353, 9), // "cellState"
QT_MOC_LITERAL(38, 363, 7), // "isMoved"
QT_MOC_LITERAL(39, 371, 7), // "getSrcI"
QT_MOC_LITERAL(40, 379, 7), // "getSrcJ"
QT_MOC_LITERAL(41, 387, 8), // "getDestI"
QT_MOC_LITERAL(42, 396, 8), // "getDestJ"
QT_MOC_LITERAL(43, 405, 11), // "getSrcIndex"
QT_MOC_LITERAL(44, 417, 12), // "getDestIndex"
QT_MOC_LITERAL(45, 430, 6), // "canHit"
QT_MOC_LITERAL(46, 437, 34), // "std::vector<std::pair<uint,ui..."
QT_MOC_LITERAL(47, 472, 9), // "bkndcanGo"
QT_MOC_LITERAL(48, 482, 5), // "canGo"
QT_MOC_LITERAL(49, 488, 6), // "choose"
QT_MOC_LITERAL(50, 495, 13), // "unchoosePiece"
QT_MOC_LITERAL(51, 509, 13), // "getP1OutsIcon"
QT_MOC_LITERAL(52, 523, 13), // "getP2OutsIcon"
QT_MOC_LITERAL(53, 537, 4), // "move"
QT_MOC_LITERAL(54, 542, 4), // "undo"
QT_MOC_LITERAL(55, 547, 9), // "extraMove"
QT_MOC_LITERAL(56, 557, 10), // "randomMove"
QT_MOC_LITERAL(57, 568, 7), // "promote"
QT_MOC_LITERAL(58, 576, 4) // "type"

    },
    "BackEnd\0choosen\0\0moved\0unchoosen\0"
    "promotion\0cancel\0fileError\0gameLoaded\0"
    "setGame\0gameName\0startGame\0restartGame\0"
    "saveAndExit\0endGame\0gameStatus\0getFiles\0"
    "getFileInfo\0index\0loadGame\0filesCount\0"
    "setP1\0P1Name\0setP2\0P2Name\0getP1Name\0"
    "getP2Name\0getP1_PScore\0getP1_NScore\0"
    "getP2_PScore\0getP2_NScore\0getGameName\0"
    "winner\0checkRandomMove\0setCanceler\0"
    "getCanceler\0getIcon\0cellState\0isMoved\0"
    "getSrcI\0getSrcJ\0getDestI\0getDestJ\0"
    "getSrcIndex\0getDestIndex\0canHit\0"
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
      50,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  264,    2, 0x06 /* Public */,
       3,    0,  265,    2, 0x06 /* Public */,
       4,    0,  266,    2, 0x06 /* Public */,
       5,    0,  267,    2, 0x06 /* Public */,
       6,    0,  268,    2, 0x06 /* Public */,
       7,    0,  269,    2, 0x06 /* Public */,
       8,    0,  270,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,  271,    2, 0x0a /* Public */,
      11,    0,  274,    2, 0x0a /* Public */,
      12,    0,  275,    2, 0x0a /* Public */,
      13,    0,  276,    2, 0x0a /* Public */,
      14,    0,  277,    2, 0x0a /* Public */,
      15,    0,  278,    2, 0x0a /* Public */,
      16,    0,  279,    2, 0x0a /* Public */,
      17,    1,  280,    2, 0x0a /* Public */,
      19,    1,  283,    2, 0x0a /* Public */,
      20,    0,  286,    2, 0x0a /* Public */,
      21,    1,  287,    2, 0x0a /* Public */,
      23,    1,  290,    2, 0x0a /* Public */,
      25,    0,  293,    2, 0x0a /* Public */,
      26,    0,  294,    2, 0x0a /* Public */,
      27,    0,  295,    2, 0x0a /* Public */,
      28,    0,  296,    2, 0x0a /* Public */,
      29,    0,  297,    2, 0x0a /* Public */,
      30,    0,  298,    2, 0x0a /* Public */,
      31,    0,  299,    2, 0x0a /* Public */,
      32,    0,  300,    2, 0x0a /* Public */,
      33,    0,  301,    2, 0x0a /* Public */,
      34,    0,  302,    2, 0x0a /* Public */,
      35,    0,  303,    2, 0x0a /* Public */,
      36,    1,  304,    2, 0x0a /* Public */,
      37,    1,  307,    2, 0x0a /* Public */,
      38,    1,  310,    2, 0x0a /* Public */,
      39,    0,  313,    2, 0x0a /* Public */,
      40,    0,  314,    2, 0x0a /* Public */,
      41,    0,  315,    2, 0x0a /* Public */,
      42,    0,  316,    2, 0x0a /* Public */,
      43,    0,  317,    2, 0x0a /* Public */,
      44,    0,  318,    2, 0x0a /* Public */,
      45,    2,  319,    2, 0x0a /* Public */,
      48,    2,  324,    2, 0x0a /* Public */,
      49,    1,  329,    2, 0x0a /* Public */,
      50,    1,  332,    2, 0x0a /* Public */,
      51,    1,  335,    2, 0x0a /* Public */,
      52,    1,  338,    2, 0x0a /* Public */,
      53,    1,  341,    2, 0x0a /* Public */,
      54,    0,  344,    2, 0x0a /* Public */,
      55,    0,  345,    2, 0x0a /* Public */,
      56,    0,  346,    2, 0x0a /* Public */,
      57,    1,  347,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::UInt,
    QMetaType::Void,
    QMetaType::QString, QMetaType::UInt,   18,
    QMetaType::Void, QMetaType::UInt,   18,
    QMetaType::UInt,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   24,
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
    QMetaType::QString, QMetaType::UInt,   18,
    QMetaType::UInt, QMetaType::UInt,   18,
    QMetaType::Bool, QMetaType::UInt,   18,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::UInt,
    QMetaType::Bool, QMetaType::UInt, 0x80000000 | 46,   18,   47,
    QMetaType::Bool, QMetaType::UInt, 0x80000000 | 46,   18,   47,
    QMetaType::UInt, QMetaType::UInt,   18,
    QMetaType::Bool, QMetaType::UInt,   18,
    QMetaType::QString, QMetaType::UInt,   18,
    QMetaType::QString, QMetaType::UInt,   18,
    QMetaType::Bool, QMetaType::UInt,   18,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,   58,

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
        case 5: _t->fileError(); break;
        case 6: _t->gameLoaded(); break;
        case 7: _t->setGame((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->startGame(); break;
        case 9: _t->restartGame(); break;
        case 10: _t->saveAndExit(); break;
        case 11: _t->endGame(); break;
        case 12: { uint _r = _t->gameStatus();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->getFiles(); break;
        case 14: { QString _r = _t->getFileInfo((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->loadGame((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 16: { uint _r = _t->filesCount();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->setP1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->setP2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: { QString _r = _t->getP1Name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 20: { QString _r = _t->getP2Name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 21: { int _r = _t->getP1_PScore();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 22: { int _r = _t->getP1_NScore();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 23: { int _r = _t->getP2_PScore();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 24: { int _r = _t->getP2_NScore();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 25: { QString _r = _t->getGameName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 26: { uint _r = _t->winner();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 27: _t->checkRandomMove(); break;
        case 28: _t->setCanceler(); break;
        case 29: { uint _r = _t->getCanceler();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 30: { QString _r = _t->getIcon((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 31: { uint _r = _t->cellState((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 32: { bool _r = _t->isMoved((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 33: { uint _r = _t->getSrcI();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 34: { uint _r = _t->getSrcJ();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 35: { uint _r = _t->getDestI();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 36: { uint _r = _t->getDestJ();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 37: { uint _r = _t->getSrcIndex();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 38: { uint _r = _t->getDestIndex();
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 39: { bool _r = _t->canHit((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::vector<std::pair<uint,uint> >(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 40: { bool _r = _t->canGo((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::vector<std::pair<uint,uint> >(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 41: { uint _r = _t->choose((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 42: { bool _r = _t->unchoosePiece((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 43: { QString _r = _t->getP1OutsIcon((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 44: { QString _r = _t->getP2OutsIcon((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 45: { bool _r = _t->move((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 46: _t->undo(); break;
        case 47: { bool _r = _t->extraMove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 48: _t->randomMove(); break;
        case 49: _t->promote((*reinterpret_cast< uint(*)>(_a[1]))); break;
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
        {
            using _t = void (BackEnd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::fileError)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (BackEnd::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BackEnd::gameLoaded)) {
                *result = 6;
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
        if (_id < 50)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 50;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 50)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 50;
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

// SIGNAL 5
void BackEnd::fileError()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void BackEnd::gameLoaded()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
