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
    unsigned Chessman_i = 0;
    unsigned Chessman_j = 0;
    std::shared_ptr<GameManager> manager = GameManager::setGameManager();
    std::vector<QString> icons;

public:
    BackEnd();

public slots:

    //login
    void getP1Name(QString P1Name);
    void getP2Name(QString P2Name);
    void getGameName(QString GameName);

    //board
    QString getIcon(); //?
    void choose(unsigned index);

signals:
};

#endif // BACKEND_HPP
