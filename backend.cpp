#include "backend.hpp"

using namespace std;

BackEnd::BackEnd() {}

void BackEnd::getP1Name(QString P1Name) {}

void BackEnd::getP2Name(QString P2Name) {}

void BackEnd::getGameName(QString GameName) {}

QString BackEnd::getIcon(unsigned index)
{
    //get from Chessman class
    //test
    if (index <= 11)
        return QString::fromStdString(icons[index]);
    else
        return "";
}

void BackEnd::choose(unsigned index)
{
    unsigned i = index % 8;
    unsigned j = 0;
    for (; index > 8; j++) {
        index -= 8;
    }
    qDebug() << "i: " << i << " j: " << j;
    src.first = i;
    src.second = j;

    emit choosen();
}

void BackEnd::move(unsigned index)
{
    unsigned i = index % 8;
    unsigned j = 0;
    for (; index > 8; j++) {
        index -= 8;
    }
    icons[2] = "qrc:/Assets/Icons/WRook.png";
    qDebug() << "i: " << i << " j: " << j;
    //    manager->movePiece(src, make_pair(i, j));
}

bool BackEnd::isAvailable(unsigned index)
{
    for (auto const &item : canGo) {
        if (item == index) {
            return true;
        }
    }
    return false;
}

bool BackEnd::canHitPiece(unsigned index)
{
    for (auto const &item : canHit) { //manager->canHin
        if (item == index) {
            return true;
        }
    }
    return false;
}
