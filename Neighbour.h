//
// Created by jbrogniez on 15/4/2019.
//

#ifndef CEPHALOPOD_NEIGHBOUR_H
#define CEPHALOPOD_NEIGHBOUR_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <cstdlib>

#include "Coordinate.h"

using namespace std;

class Neighbour {
private:
    //unordered_map<string, int> neighbour[4];
    vector<int> neighbourTest;

    int totalPips;
    int counter;
    bool capturedNeighbours[4]{};

public:
    Neighbour()
    {
        totalPips = 0;
        counter = 0;
        for ( int i = 0; i < 4; i++ )
            capturedNeighbours[i] = false;
    }

    void setNeighbour(string*, int*);
    void initialise();
    void printPips();
    int calculatePips();
    bool *removeCapturedNeighbours();
};

void Neighbour::printPips()
{
    if ( neighbourTest[0] != 8 )
        cout << "Up: " << neighbourTest[0] << endl;
    if ( neighbourTest[1] != 8 )
        cout << "Right: " << neighbourTest[1] << endl;
    if ( neighbourTest[2] != 8 )
        cout << "Down: " << neighbourTest[2] << endl;
    if ( neighbourTest[3] != 8 )
        cout << "Left: " << neighbourTest[3] << endl;


    cout << "Total pip count: " << totalPips << endl;
    cout << endl;
}

int Neighbour::calculatePips()
{
    totalPips = 0;
    counter = 0;
    for ( int i = 0; i < 4; i++ )
    {
        if ( neighbourTest[i] != 8 && neighbourTest[i] != 0 )
        {
            totalPips += abs(neighbourTest[i]);
            counter++;
        }
    }

    if ( counter > 1 )
        return totalPips;
    else
        return 0;
}

bool *Neighbour::removeCapturedNeighbours()
{
    for ( int i = 0; i < 4; i++ )
    {
        if ( neighbourTest[i] != 8 && neighbourTest[i] != 0 )
        {
            capturedNeighbours[i] = true;
        }
    }

    return capturedNeighbours;
}

void Neighbour::setNeighbour(string* direction, int* value)
{
    //Hash Table Implementation
    /*
    for ( int i = 0; i < 4; i++ )
        neighbour[direction[i]] = value[i];


    for ( int i = 0; i < 4; i++ )
        neighbour.insert(pair<string, int>(direction[i], value[i]));
    */


    for ( int i = 0; i < 4; i++ )
    {
        if ( direction[i] == "u" )
            neighbourTest[i] = value[i];

        if ( direction[i] == "r" )
            neighbourTest[i] = value[i];

        if ( direction[i] == "d" )
            neighbourTest[i] = value[i];

        if ( direction[i] == "l" )
            neighbourTest[i] = value[i];
    }
}

void Neighbour::initialise()
{
    for ( int i = 0; i < 4; i++ )
    {
        neighbourTest.push_back(0);
    }
}


#endif //CEPHALOPOD_NEIGHBOUR_H
