#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <include/GameManager.hpp>
#include <vector>
#include <QObject>
#include <QPair>
#include <QString>
#include <QtQuick>

class BackEnd : public QObject
{
    // connect ot Qt
    Q_OBJECT

private:
    // showing last move
    int previewsSrc = -1;

    // move source index
    int srcIndex = -1;

    // move destination index
    int destIndex = -1;

    // if player changes the chosen piece
    bool _change = false;

    // if player wants extra move
    bool _extraMove = false;

    // if player choose a piecse and don't move it
    bool _touchedPiece = false;

    //
    bool _moved = false;

    // players name in the file
    std::vector<std::string> _filePlayersName;

    // player who canceled the game
    short unsigned _canceler = 2;

    // enable random move feature
    bool _random_enabled = true;

    // choose a piecse and don't move it
    void touchedPiece(GameManager::Turn);

    // game manager class object
    std::unique_ptr<GameManager> manager = std::unique_ptr<GameManager>(GameManager::get("game"));

public:
    std::pair<std::vector<Chessman::Index>, std::vector<Chessman::Index>> srcState;

    // souce cell states
    enum SrcCellState
    {
        EMPTY,
        UNACCESSABLE,
        OK
    };

    // destination cell states
    enum DestCellState
    {
        UNAVAILABLE,
        CANGO,
        CANHIT,
        SELECTED
    };

public slots:

    //________________________________________________________ game

    // setting game up
    void setGame(QString gameName);

    // start game
    void startGame();

    // restart game
    void restartGame();

    // save game and exit
    void saveAndExit();

    // end of the game
    void endGame();

    // check input texts
    bool checkInput(QString name);

    // get game current status
    unsigned gameStatus();

    //--------------------------------------------------------- files

    // load .txt files from "SavedGames" folder
    bool readSaveFiles();

    // get information in file
    QString getFileInfo(unsigned index);

    // load chosen game
    void loadGame(unsigned index);

    // files count in save directory
    unsigned filesCount() const;

    // delete chosen file
    void deleteFile(unsigned index);

    //________________________________________________________ users

    // setup palyer 1 data
    void setP1(QString P1Name);

    // setup palyer 2 data
    void setP2(QString P2Name);

    // get player 1 name
    QString getP1Name();

    // get player 1 name
    QString getP2Name();

    // get player 1 positive score
    int getP1_PScore();

    // get player 1 negative score
    int getP1_NScore();

    // get player 2 positive score
    int getP2_PScore();

    // get player 2 negative score
    int getP2_NScore();

    // get game name
    QString getGameName();

    // get winner index
    unsigned winner();

    // check if palyer must have random move
    void checkRandomMove();

    // set who canceled the game
    void setCanceler();

    // get who canceled the game
    unsigned getCanceler();

    //________________________________________________________ board

    // get peice icon
    QString getIcon(unsigned index);

    // get cells state according to chosen piece
    unsigned cellState(unsigned index);

    // was this cell source or dest of previews move (for highlighting)
    bool isMoved(unsigned index);

    //________________________________________________ indexes

    // convert source to i&j and get i
    unsigned getSrcI();

    // convert source to i&j and get j
    unsigned getSrcJ();

    // convert destination to i&j and get i
    unsigned getDestI();

    // convert destination to i&j and get j
    unsigned getDestJ();

    // get source index
    unsigned getSrcIndex();

    // get dest index
    unsigned getDestIndex();

    //    QString getHitPiece();

    //__________________________________________________________ movement

    // if piece can hit this cell
    bool canHit(unsigned index, std::vector<std::pair<unsigned int, unsigned int>> bkndcanGo);

    // if piece can go to this cell
    bool canGo(unsigned index, std::vector<std::pair<unsigned int, unsigned int>> bkndcanGo);

    // select the piece
    unsigned choose(unsigned index);

    // unselect the piece
    bool unchoosePiece(unsigned index);

    // get player 1 hitted pieces
    QString getP1OutsIcon(unsigned index);

    // get player 2 hitted pieces
    QString getP2OutsIcon(unsigned index);

    // move to selected cell
    bool move(unsigned index) noexcept;

    // undo last move
    void undo();

    // an extra move
    bool extraMove();

    // performe a random move
    void randomMove();

    // toggle random enable
    void toggleRandom();

    // promotion
    void promote(unsigned type);

signals:

    // selection signal
    void choosen();

    // movement signal
    void moved();

    // unselecting signal
    void unchoosen();

    // promotion signal
    void promotion();

    // cancel signal
    void cancel();

    // file error signal
    void fileError();

    // load game signal
    void gameLoaded();
};

// convert index to i&j
std::pair<unsigned, unsigned> indexToIJ(unsigned index);

// convert i&j to indext
unsigned IJToIndex(std::pair<unsigned int, unsigned int>);

#endif // BACKEND_HPP
