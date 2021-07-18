#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <Header/GameManager.hpp>
#include <vector>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QtQuick>

class BackEnd : public QObject
{
    Q_OBJECT

private:
    //ChessBoard
    unsigned srcIndex;
    unsigned destIndex;

    //    std::shared_ptr<GameManager> manager = GameManager::setGameManager("fdsfd");
    std::shared_ptr<GameManager> manager = GameManager::setGameManager(std::string("game"));

public:
    std::pair<std::vector<Chessman::Index>, std::vector<Chessman::Index>> srcState;

    enum ChooseState { EMPTY, UNACCESSABLE, OK };

    enum CellState { UNAVAILABLE, CANGO, CANHIT, SELECTED };

public slots:

    void startGame();

    //________________________________________________________ users
    void setP1(QString P1Name);

    void setP2(QString P2Name);

    void setGameName(QString GameName);

    QString getP1Name();

    QString getP2Name();

    unsigned getP1_PScore();

    unsigned getP1_NScore();

    unsigned getP2_PScore();

    unsigned getP2_NScore();

    QString getGameName();

    //________________________________________________________ board
    QString getIcon(unsigned index);

    unsigned choose(unsigned index);

    unsigned cellState(unsigned index);

    bool canGo(unsigned index, std::vector<std::pair<unsigned int, unsigned int>> bkndcanGo);

    bool canHit(unsigned index, std::vector<std::pair<unsigned int, unsigned int>> bkndcanGo);

    bool move(unsigned index);

    bool unchoosePiece(unsigned index);

signals:

    void choosen();

    void unchoosen();
};

std::pair<unsigned, unsigned> indexToIJ(unsigned index);

unsigned IJToIndex(std::pair<unsigned int, unsigned int>);

#endif // BACKEND_HPP
