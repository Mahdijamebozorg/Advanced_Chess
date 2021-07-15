#ifndef BACKEND_HPP
#define BACKEND_HPP

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
