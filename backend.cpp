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
    srcIndex = index;
    emit choosen();
}

bool BackEnd::move(unsigned index)
{
    if (unchoosePiece(index)) //if not moved
    {
        return false;
    }

    else {
        destIndex = index;

        //convert srcIndex to i & j
        unsigned i1 = srcIndex % 8;
        unsigned j1 = 0;
        while (srcIndex > 8) {
            j1++;
            srcIndex -= 8;
        }

        //convert destIndex to i & j
        unsigned i2 = destIndex % 8;
        unsigned j2 = 0;
        while (destIndex > 8) {
            j2++;
            destIndex -= 8;
        }

        manager->movePiece(make_pair(i1, j1), make_pair(i2, j2));
        return true;
        //        //test
        //        icons[2] = "qrc:/Assets/Icons/WRook.png";
    }
}

bool BackEnd::unchoosePiece(unsigned index)
{
    if (index == srcIndex) {
        emit unchoose();
        return true;
    } else {
        return false;
    }
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
