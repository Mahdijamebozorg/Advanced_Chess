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

    //test, these will be gotten from backend
    std::vector<std::string> icons = {"qrc:/Assets/Icons/BBishop.png",
                                      "qrc:/Assets/Icons/BKing.png",
                                      "qrc:/Assets/Icons/BKnight.png",
                                      "qrc:/Assets/Icons/BPawn.png",
                                      "qrc:/Assets/Icons/BQueen.png",
                                      "qrc:/Assets/Icons/BRook.png",
                                      "qrc:/Assets/Icons/WBishop.png",
                                      "qrc:/Assets/Icons/WKing.png",
                                      "qrc:/Assets/Icons/WKnight.png",
                                      "qrc:/Assets/Icons/WPawn.png",
                                      "qrc:/Assets/Icons/WQueen.png",
                                      "qrc:/Assets/Icons/WRook.png"};
    //test
    std::vector<std::pair<unsigned int, unsigned int>> bkndCanGo = {{1, 5}, {1, 4}, {0, 4}, {0, 5}};
    std::vector<std::pair<unsigned int, unsigned int>> bkndCanHit = {{1, 5}, {1, 4}};

public:
    BackEnd();

public slots:

    void startGame();

    //________________________________________________________ users
    void setP1(QString P1Name);

    unsigned getP1_PScore();

    unsigned getP1_NScore();

    unsigned getP2_PScore();

    unsigned getP2_NScore();

    void setP2(QString P2Name);

    void setGameName(QString GameName);

    QString getP1Name();

    QString getP2Name();

    QString getGameName();

    //________________________________________________________ board
    QString getIcon(unsigned index);

    void choose(unsigned index);

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
