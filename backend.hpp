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

    std::shared_ptr<GameManager> manager = GameManager::setGameManager();

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
    //    std::vector<unsigned> bkndcanGo = {16, 17, 18, 19, 20, 21, 29, 37, 45, 53, 61};
    //    std::vector<unsigned> canHit = {18, 29};

public:
    BackEnd();

public slots:

    //users
    void setP1(QString P1Name);
    unsigned getP1Score();
    unsigned getP2Score();
    void setP2(QString P2Name);
    void setGameName(QString GameName);
    QString getP1Name();
    QString getP2Name();
    QString getGameName();

    //board
    QString getIcon(unsigned index);
    void choose(unsigned index);
    unsigned cellState();
    bool canGo(unsigned index, std::vector<unsigned> bkndcanGo);
    bool canHit(unsigned index, std::vector<unsigned> bkndcanGo);
    void move(unsigned index);
    bool unchoosePiece(unsigned index);

signals:
    void choosen();
    void unchoose();
};

std::pair<unsigned, unsigned> indexToIJ(unsigned index);
unsigned IJToIndex(std::pair<unsigned, unsigned>);

#endif // BACKEND_HPP
