#include "backend.hpp"

using namespace std;

BackEnd::BackEnd() {}

//____________________________________________________________________________________________ IJToIndex

unsigned IJToIndex(pair<unsigned, unsigned> index)
{
    return index.second * 8 + index.first;
}

//____________________________________________________________________________________________ indexToIJ

std::pair<unsigned, unsigned> indexToIJ(unsigned index)
{
    unsigned i = index % 8;
    unsigned j = 0;
    while (index > 8) {
        j++;
        index -= 8;
    }
    return make_pair(i, j);
}

//____________________________________________________________________________________________ getP1Name

void BackEnd::setP1(QString P1Name)
{
    manager->setUser(P1Name.QString::toStdString());
}

//____________________________________________________________________________________________ getP2Name

void BackEnd::setP2(QString P2Name)
{
    manager->setUser(P2Name.QString::toStdString());
}

//____________________________________________________________________________________________ getGameName

void BackEnd::getGameName(QString GameName) {}

//____________________________________________________________________________________________ getIcon

QString BackEnd::getIcon(unsigned index)
{
    return QString::fromStdString(manager->getChessBoard().getCell(indexToIJ(index)).getIcon());
}

//____________________________________________________________________________________________ choose

void BackEnd::choose(unsigned index)
{
    srcIndex = index;
    emit choosen();
}

//____________________________________________________________________________________________ canGo

bool BackEnd::canGo(unsigned index, vector<pair<unsigned, unsigned>> bkndcanGo)
{
    for (auto const &item : bkndcanGo) {
        if (IJToIndex(item) == index) {
            return true;
        }
    }
    return false;
}

//____________________________________________________________________________________________ canHit

bool BackEnd::canHit(unsigned index, vector<pair<unsigned, unsigned>> bkndcanHit)
{
    for (auto const &item : bkndcanHit) { //manager->canHin
        if (IJToIndex(item) == index) {
            return true;
        }
    }
    return false;
}

//____________________________________________________________________________________________ cellState

unsigned BackEnd::cellState(unsigned index)
{
    pair<unsigned, unsigned> src = indexToIJ(index);
    pair<vector<pair<unsigned, unsigned>>, vector<pair<unsigned, unsigned>>> state
        = manager->getCellState(src);

    //if can hit
    if (canHit(index, state.second)) {
        return 3;

    }

    //if can go
    else if (canGo(index, state.first)) {
        return 2;

    }

    //if unavailable
    else
        return 0;
}

//____________________________________________________________________________________________ unchoosePiece

bool BackEnd::unchoosePiece(unsigned index)
{
    if (index == srcIndex) {
        emit unchoose();
        return true;
    } else {
        return false;
    }
}

//____________________________________________________________________________________________ move

void BackEnd::move(unsigned index)
{
    destIndex = index;

    manager->movePiece(indexToIJ(srcIndex), indexToIJ((destIndex)));
}
