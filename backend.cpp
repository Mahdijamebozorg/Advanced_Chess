#include "backend.hpp"
#include "Header/Exceptions.hpp"

using namespace std;

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
    return manager->getUser1()->getPosetiveScore();
}

//__________________________________________________________________________ get P1 Negative Score

unsigned BackEnd::getP1_NScore()
{
    return manager->getUser1()->getNegativeScore();
}

//__________________________________________________________________________ get P2 Positive Score

unsigned BackEnd::getP2_PScore()
{
    return manager->getUser2()->getPosetiveScore();
}

//__________________________________________________________________________ get P2 Negative Score

unsigned BackEnd::getP2_NScore()
{
    return manager->getUser2()->getNegativeScore();
}

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
unsigned BackEnd::choose(unsigned index)
{
    qDebug() << "choosen: " << index;
    qDebug() << "choosen: " << indexToIJ(index);

    Chessman::Index src = indexToIJ(index);
    try {
        srcState = manager->getCellState(src);
    }

    catch (EmptySquare &s) {
        qDebug() << s.what();
        return EMPTY;
    }

    catch (AccessDenied &s) {
        qDebug() << s.what();
        return UNACCESSABLE;
    }

    qDebug() << "canGo" << srcState.first;
    qDebug() << "canHit" << srcState.second;

    srcIndex = index;
    emit choosen();
    return OK;
}

//__________________________________________________________________________ canGo

bool BackEnd::canGo(unsigned index, std::vector<std::pair<unsigned int, unsigned int>> bkndcanGo)
{
    for (auto const &item : bkndcanGo) {
        if (IJToIndex(item) == index) //if this square is in the available squares which piece can go
            return true;
    }
    return false;
}

//__________________________________________________________________________ canHit

bool BackEnd::canHit(unsigned index, std::vector<std::pair<unsigned int, unsigned int>> bkndcanHit)
{
    for (auto const &item : bkndcanHit) {
        if (IJToIndex(item)
            == index) //if this square is in the available squares which piece can hit
            return true;
    }
    return false;
}

//__________________________________________________________________________ cellState

unsigned BackEnd::cellState(unsigned index)
{
    if (index == (unsigned) srcIndex)
        return SELECTED;

    if (canHit(index, srcState.second))
        return CANHIT;

    else if (canGo(index, srcState.first))
        return CANGO;

    else
        return UNAVAILABLE;
}

//__________________________________________________________________________ getSrcIndex

unsigned BackEnd::getSrcIndex()
{
    qDebug() << "src";
    return srcIndex;
}

//__________________________________________________________________________ getDestIndex

unsigned BackEnd::getDestIndex()
{
    qDebug() << "dest";
    return destIndex;
}

//__________________________________________________________________________ isMoved

bool BackEnd::isMoved(unsigned index)
{
    if (srcIndex != -1 && destIndex != -1)
        if (index == (unsigned) previewsSrc || index == (unsigned) destIndex)
            return true;

    return false;
}

//__________________________________________________________________________ unchoosePiece

bool BackEnd::unchoosePiece(unsigned index)
{
    if (index == (unsigned) srcIndex) {
        if (!change) //____________unchoose will clear colored cells and we don't want!
            emit unchoosen();
        change = false;
        return true;
    }

    else
        return false;
}

//__________________________________________________________________________ P1 outs

QString BackEnd::getP1OutsIcon(unsigned index)
{
    auto outs = manager->getUser1()->getChessmansOut();

    if (index + 1 > outs.size() || outs.size() == 0)
        return "";
    else {
        return QString::fromStdString(outs[index]->getIcon());
    }
}

//__________________________________________________________________________ P2 outs

QString BackEnd::getP2OutsIcon(unsigned index)
{
    auto outs = manager->getUser2()->getChessmansOut();

    if (index + 1 > outs.size() || outs.size() == 0)
        return "";
    else {
        return QString::fromStdString(outs[index]->getIcon());
    }
}

//__________________________________________________________________________ move

bool BackEnd::move(unsigned index)
{
    qDebug() << "from: " << srcIndex;
    qDebug() << "from: " << indexToIJ(srcIndex);

    qDebug() << "to: " << index;
    qDebug() << "to: " << indexToIJ(index);

    //unchoose
    if (cellState(index) == SELECTED)
        return false;

    //change choosen piece
    if (manager->getChessBoardGame()->getCell(indexToIJ(index)).isFull()
        && manager->getChessBoardGame()->getCell(indexToIJ(srcIndex)).isFull())
        if (manager->getChessBoardGame()->getCell(indexToIJ(index)).getChessPieces()->getColor()
            == manager->getChessBoardGame()
                   ->getCell(indexToIJ(srcIndex))
                   .getChessPieces()
                   ->getColor()) {
            qDebug() << "change";
            change = true;
            emit unchoosen();
            choose(index);
            return false;
        }

    //if can't go
    if (cellState(index) == UNAVAILABLE) {
        return false;
    }

    destIndex = index;

    try {
        manager->movePiece(indexToIJ(srcIndex), indexToIJ(destIndex));
    }

    catch (...) {
        return false;
    }

    qDebug() << "moved from" << indexToIJ(srcIndex) << " to " << indexToIJ(destIndex);

    if (!_extraMove)
        manager->changeTurn();

    _extraMove = false;

    previewsSrc = srcIndex;

    return true;
}

//__________________________________________________________________________ undo

void BackEnd::undo()
{
    auto back = manager->undo();
    previewsSrc = IJToIndex(back.first);
    destIndex = IJToIndex(back.second);
    emit unchoosen();
}

//__________________________________________________________________________ extraMove
bool BackEnd::extraMove()
{
    //turn user 1
    if (manager->getTurn() == GameManager::USER1)
        if (manager->getUser1()->getPosetiveScore() >= 30) {
            _extraMove = true;
            manager->getUser1()->operator-=(30);
            return true;

        } else
            return false;

    //turn user 2
    else if (manager->getUser2()->getPosetiveScore() >= 30) {
        _extraMove = true;
        manager->getUser2()->operator-=(30);
        return true;

    } else
        return false;
}
