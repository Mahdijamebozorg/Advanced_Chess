#include "backend.hpp"

BackEnd::BackEnd()
{
    
}

QString BackEnd::getIcon()
{
    for (unsigned i = 0; i < 8; i++) {
        for (unsigned j = 0; j < 8; j++) {
            //if(chessboard[i][j].getChessman()
        }
    }
}

void BackEnd::choose(unsigned index)
{
    index++;
    unsigned i = index % 8;
    unsigned j = 0;
    for (; index > 8; j++) {
        index /= 8;
    }
    i--;
    j--;
    //take to cpp
}
