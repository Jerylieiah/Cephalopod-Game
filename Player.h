//
// Created by jbrogniez on 8/4/2019.
//

#ifndef CEPHALOPOD_PLAYER_H
#define CEPHALOPOD_PLAYER_H

#include "Coordinate.h"


class Player {
private:
    Coordinate xy;

    int playerNum;

public:
    Player() = default;

    Player(int p, int x, int y) : playerNum(p), xy(x, y) {};
    Coordinate getCor(int, int, int);
};

Coordinate Player::getCor(int x, int y, int playerNum_)
{
    if ( playerNum = 1 )
    {

    }

    else if ( playerNum = -1 )
    {

    }
}

#endif //CEPHALOPOD_PLAYER_H
