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
    unsigned ChessmanIndex = 0;

public:
    BackEnd();

public slots:
    QString getIcon(); //?
    void choose(unsigned index);

signals:
};

#endif // BACKEND_HPP
