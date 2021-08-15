#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <include/GameManager.hpp>
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
    int previewsSrc = -1; //for showing movements
    int srcIndex = -1;
    int destIndex = -1;
    bool _change = false;
    bool _extraMove = false;
    bool _touchedPiece = false;
    void touchedPiece(GameManager::Turn);

    std::unique_ptr<GameManager> manager = std::unique_ptr<GameManager>(GameManager::get("game"));

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

    unsigned gameStatus();

    //________________________________________________________ users
    void setP1(QString P1Name);

    void setP2(QString P2Name);

    QString getP1Name();

    QString getP2Name();

    int getP1_PScore();

    int getP1_NScore();

    int getP2_PScore();

    int getP2_NScore();

    QString getGameName();

    unsigned winner();

    bool checkRandomMove();

    //________________________________________________________ board
    QString getIcon(unsigned index);

    unsigned cellState(unsigned index);

    bool isMoved(unsigned index);

    //__________________________________________________________ movement
    bool canHit(unsigned index, std::vector<std::pair<unsigned int, unsigned int>> bkndcanGo);

    bool canGo(unsigned index, std::vector<std::pair<unsigned int, unsigned int>> bkndcanGo);

    unsigned choose(unsigned index);

    bool unchoosePiece(unsigned index);

    QString getP1OutsIcon(unsigned index);

    QString getP2OutsIcon(unsigned index);

    bool move(unsigned index) noexcept;

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
