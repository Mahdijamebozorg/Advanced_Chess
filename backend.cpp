#include "backend.hpp"
#include "include/Exceptions.hpp"

using namespace std;

//__________________________________________________________________________________________________ game
//__________________________________________________________________________

void BackEnd::setGame(QString gameName)
{
    //    manager = unique_ptr<GameManager>(GameManager::get(gameName.QString::toStdString()));
    manager->setGameName(gameName.QString::toStdString());
    //    manager = GameManager::get(gameName.QString::toStdString());
}

//__________________________________________________________________________

void BackEnd::startGame()
{
    qDebug() << " ##### before start game called ########";
    manager->startGame();
    qDebug() << "******start game called*********";
}

//__________________________________________________________________________ restartGame

void BackEnd::restartGame()
{
    manager->restartGame();
    previewsSrc = -1;
    srcIndex = -1;
    destIndex = -1;
}

//__________________________________________________________________________ endGame

void BackEnd::endGame()
{
    manager->endGame();
    previewsSrc = -1;
    srcIndex = -1;
    destIndex = -1;
    qDebug() << "game ended";
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
    manager->setUser1(P1Name.QString::toStdString(), 0, 0);
    qDebug() << "user 1 setted";
}

//__________________________________________________________________________ setP2Name

void BackEnd::setP2(QString P2Name)
{
    manager->setUser2(P2Name.QString::toStdString(), 0, 0);
    qDebug() << "user 2 setted";
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

int BackEnd::getP1_PScore()
{
    return manager->getUser1()->getScore();
}

//__________________________________________________________________________ get P1 Negative Score

int BackEnd::getP1_NScore()
{
    return manager->getUser1()->getNegativeScore();
}

//__________________________________________________________________________ get P2 Positive Score

int BackEnd::getP2_PScore()
{
    return manager->getUser2()->getScore();
}

//__________________________________________________________________________ get P2 Negative Score

int BackEnd::getP2_NScore()
{
    return manager->getUser2()->getNegativeScore();
}

//______________________________________________________________________________________________________ Board options
//__________________________________________________________________________ getGameName
QString BackEnd::getGameName()
{
    return QString::fromStdString(manager->getGameName());
}

//__________________________________________________________________________ Winner

QString BackEnd::winnerUser()
{
    return QString::fromStdString(manager->getWinner()->getName());
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
    if (_change) { //____________ on changing piece no error should be opened
        _change = false;
        return true;
    }
    if (index == (unsigned) srcIndex) {
        emit unchoosen();
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

    //if index is in outs length
    if (index < outs.size())
        return QString::fromStdString(outs[index]->getIcon());
    else {
        return "";
    }
}

//__________________________________________________________________________ move

bool BackEnd::move(unsigned index) noexcept
{
    qDebug() << "src: " << srcIndex;
    qDebug() << "src: " << indexToIJ(srcIndex);

    qDebug() << "dest: " << index;
    qDebug() << "dest: " << indexToIJ(index);

    //unchoose
    if (cellState(index) == SELECTED) {
        //if user have chosen a moveable piece for first time in this turn
        if (!_touchedPiece)
            //if piece is moveable
            if (!srcState.first.empty()) {
                _touchedPiece = true;
                this->touchedPiece(manager->getTurn());
            }
        return false;
    }

    //___________________________change choosen piece

    //if cell is full
    if (manager->getChessBoardGame()->getCell(indexToIJ(index)).isFull()
        && manager->getChessBoardGame()->getCell(indexToIJ(srcIndex)).isFull()) {
        //if colors are the same
        if (manager->getChessBoardGame()->getCell(indexToIJ(index)).getChessPieces()->getColor()
            == manager->getChessBoardGame()
                   ->getCell(indexToIJ(srcIndex))
                   .getChessPieces()
                   ->getColor()) {
            _change = true;

            //if user have chosen a moveable piece for first time in this turn
            if (!_touchedPiece)
                //if piece is moveable
                if (!srcState.first.empty()) {
                    _touchedPiece = true;
                    this->touchedPiece(manager->getTurn());
                }

            emit unchoosen();
            choose(index);
            return false;
        }
    }

    //if can't go
    if (cellState(index) == UNAVAILABLE) {
        return false;
    }

    try {
        destIndex = index;
        manager->movePiece(indexToIJ(srcIndex), indexToIJ(destIndex));
    }

    catch (ImpossibleHitKing &s) {
        qDebug() << s.what();
        return false;
    }

    catch (FinalCellForPawn &s) {
        qDebug() << s.what();
        emit promotion();
        _change = true;
        previewsSrc = srcIndex;
        return false;
    }

    catch (exception &s) {
        qDebug() << s.what();
        return false;
    }

    previewsSrc = srcIndex;

    qDebug() << "moved from" << indexToIJ(srcIndex) << " to " << indexToIJ(destIndex);

    if (!_extraMove)
        manager->changeTurn();
    else
        _extraMove = false;

    //Turn changed
    _touchedPiece = false;

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
    if (manager->extraMovements()) {
        _extraMove = true;
        return true;
    }
    return false;
}

//__________________________________________________________________________ random Move

bool BackEnd::randomMove()
{
    pair<bool, pair<Chessman::Index, Chessman::Index>> temp;

    try {
        temp = manager->randomMovements();
    }

    catch (exception &s) {
        qDebug() << s.what();
        return false;
    }

    if (temp.first) { //if moved
        previewsSrc = (int) IJToIndex(temp.second.first);
        destIndex = (int) IJToIndex(temp.second.second);
        manager->changeTurn();
        return true;
    } else
        return false;
}

//__________________________________________________________________________ promote
void BackEnd::promote(unsigned type)
{
    manager->promote(indexToIJ(destIndex), (Chessman::ChessType) type);
    manager->changeTurn();
}

//__________________________________________________________________________ is King Checked

bool BackEnd::isKingChecked()
{
    return manager->isKingChecked();
}

//__________________________________________________________________________ is King Checkmate

bool BackEnd::isKingCheckmate()
{
    return manager->isCheckmate();
}

//__________________________________________________________________________ stalemate

bool BackEnd::stalemate()
{
    //    return manager->isStalemate();
    return false;
}

//__________________________________________________________________________ touched piece
void BackEnd::touchedPiece(GameManager::Turn turn)
{
    if (turn == GameManager::USER1) {
        manager->getUser1()->incNegativeScore(5);
        qDebug() << "@@@@@@@@@@@@@@@@@@ user1 N score inc";
    } else {
        manager->getUser2()->incNegativeScore(5);
        qDebug() << "@@@@@@@@@@@@@@@@@@ user2 N score inc";
    }
}
