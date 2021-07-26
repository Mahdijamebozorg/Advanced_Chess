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
    int previewsSrc = -1;
    int srcIndex = -1;
    int destIndex = -1;
    bool change = false;
    bool _extraMove = false;

    std::unique_ptr<GameManager> manager;

public:
    std::pair<std::vector<Chessman::Index>, std::vector<Chessman::Index>> srcState;

    enum SrcCellState { EMPTY, UNACCESSABLE, OK };

    enum DestCellState { UNAVAILABLE, CANGO, CANHIT, SELECTED };

public slots:

    //________________________________________________________ game
    void setGame(QString gameName);

    void startGame();

    void restartGame();

    void endGame();

    //________________________________________________________ users
    void setP1(QString P1Name);

    void setP2(QString P2Name);

    QString getP1Name();

    QString getP2Name();

    unsigned getP1_PScore();

    int getP1_NScore();

    unsigned getP2_PScore();

    int getP2_NScore();

    QString getGameName();

    //________________________________________________________ board
    QString getIcon(unsigned index);

    unsigned cellState(unsigned index);

    unsigned getSrcIndex();

    unsigned getDestIndex();

    bool isMoved(unsigned index);

    //__________________________________________________________ movement
    bool canHit(unsigned index, std::vector<std::pair<unsigned int, unsigned int>> bkndcanGo);

    bool canGo(unsigned index, std::vector<std::pair<unsigned int, unsigned int>> bkndcanGo);

    unsigned choose(unsigned index);

    bool unchoosePiece(unsigned index);

    QString getP1OutsIcon(unsigned index);

    QString getP2OutsIcon(unsigned index);

    bool move(unsigned index);

    void undo();

    bool extraMove();

    bool randomMove();

    void promote(unsigned type);

signals:

    void choosen();

    void unchoosen();

    void promotion();
};

std::pair<unsigned, unsigned> indexToIJ(unsigned index);

unsigned IJToIndex(std::pair<unsigned int, unsigned int>);

#endif // BACKEND_HPP
