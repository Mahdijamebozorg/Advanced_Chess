#include "backend.hpp"

using namespace std;

BackEnd::BackEnd() {}

void BackEnd::startGame()
{
    manager->startGame();
}

//__________________________________________________________________________ i & j and index convertion
//__________________________________________________________________________ IJToIndex

unsigned IJToIndex(pair<unsigned int, unsigned int> index)
{
    return index.first * 8 + index.second;
}

//__________________________________________________________________________ indexToIJ

std::pair<unsigned, unsigned> indexToIJ(unsigned index)
{
    unsigned j = index % 8;
    unsigned i = 0;
    while (index >= 8) {
        i++;
        index -= 8;
    }
    return make_pair(i, j);
}
//______________________________________________________________________________________________________ User options
//__________________________________________________________________________ setP1Name

void BackEnd::setP1(QString P1Name)
{
    manager->setUser1(P1Name.QString::toStdString(), 0);
}

//__________________________________________________________________________ setP2Name

void BackEnd::setP2(QString P2Name)
{
    manager->setUser2(P2Name.QString::toStdString(), 0);
}

//__________________________________________________________________________ setGameName

void BackEnd::setGameName(QString GameName)
{
    manager->setGameName(GameName.QString::toStdString());
}

//__________________________________________________________________________ getGameName

QString BackEnd::getP1Name()
{
    return QString::fromStdString(manager->getUser1()->getName());
}

//__________________________________________________________________________ getGameName

QString BackEnd::getP2Name()
{
    return QString::fromStdString(manager->getUser2()->getName());
}

//__________________________________________________________________________ get P1 Positive Score

unsigned BackEnd::getP1_PScore()
{
    return manager->getUser1()->getScore();
}

//__________________________________________________________________________ get P1 Negative Score

unsigned BackEnd::getP1_NScore() {}

//__________________________________________________________________________ get P2 Positive Score

unsigned BackEnd::getP2_PScore()
{
    return manager->getUser2()->getScore();
}

//__________________________________________________________________________ get P2 Negative Score

unsigned BackEnd::getP2_NScore() {}

//______________________________________________________________________________________________________ Board options
//__________________________________________________________________________ getGameName
QString BackEnd::getGameName()
{
    return QString::fromStdString(manager->getGameName());
}

//__________________________________________________________________________ getIcon

QString BackEnd::getIcon(unsigned index)
{
    return QString::fromStdString(
        manager->getChessBoardGame()->getCell(indexToIJ((index))).getIcon());
}

//__________________________________________________________________________ choose
void BackEnd::choose(unsigned index)
{
    srcIndex = index;
    qDebug() << "choosen: " << index;
    qDebug() << "choosen: " << indexToIJ(index);
    emit choosen();
}

//__________________________________________________________________________ canGo

bool BackEnd::canGo(unsigned index, std::vector<std::pair<unsigned int, unsigned int>> bkndcanGo)
{
    for (auto const &item : bkndcanGo) {
        if (IJToIndex(item) == index)
            return true;
    }
    return false;
}

//__________________________________________________________________________ canHit

bool BackEnd::canHit(unsigned index, std::vector<std::pair<unsigned int, unsigned int>> bkndcanHit)
{
    for (auto const &item : bkndcanHit) {
        if (IJToIndex(item) == index)
            return true;
    }
    return false;
}

//__________________________________________________________________________ cellState

unsigned BackEnd::cellState(unsigned index)
{
    Chessman::Index src = indexToIJ(index);
    pair<vector<Chessman::Index>, vector<Chessman::Index>> state; //includes canGo and canHit
    try {
        state = manager->getCellState(src);
    } catch (invalid_argument &s) {
        qDebug() << s.what();
        return 0;
    } catch (...) {
        qDebug() << "an error happened";
        return 0;
    }
    //if can hit
    if (canHit(index, state.second))
        return 2;

    //if can go
    else if (canGo(index, state.first))
        return 1;

    //if unavailable
    else
        return 0;
}

//__________________________________________________________________________ unchoosePiece

bool BackEnd::unchoosePiece(unsigned index)
{
    if (index == srcIndex) {
        emit unchoosen();
        return true;
    } else
        return false;
}

//__________________________________________________________________________ move

bool BackEnd::move(unsigned index)
{
    qDebug() << "destination: " << index;
    qDebug() << "destination: " << indexToIJ(index);
    if (cellState(index) == 0)
        return false;

    destIndex = index;
    try {
        manager->movePiece(indexToIJ(srcIndex), indexToIJ(destIndex));
    } catch (...) {
        return false;
    }
    return true;
}
