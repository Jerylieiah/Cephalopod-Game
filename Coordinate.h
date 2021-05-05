//
// Created by jbrogniez on 16/4/2019.
//

#ifndef CEPHALOPOD_COORDINATE_H
#define CEPHALOPOD_COORDINATE_H

class Coordinate {
private:
    int element[2]{};

public:
    Coordinate() = default;

    Coordinate(int x, int y) {
        element[0] = x;
        element[1] = y;
    };

    int getX() {return element[0];};
    int getY() {return element[1];};
};

#endif //CEPHALOPOD_COORDINATE_H
