//
// Created by jbrogniez on 8/4/2019.
//

#ifndef CEPHALOPOD_BOARD_H
#define CEPHALOPOD_BOARD_H

#include <iostream>
#include <list>
#include <vector>
#include <time.h>

#include "Coordinate.h"
#include "Player.h"
#include "Neighbour.h"

using namespace std;

class Board {
private:
    //Player hPlayer;
    //Player rPlayer;
    //Coordinate pair;
    Neighbour **neighbour;

    int row, col;
    int **grid; // 1 = black; -1 = white; 0 = empty
    int turn;
    int gameMode;
    bool checkValid;
    string directions[4]{"u", "r", "d", "l"};
    int values[4];
    vector<int> gamePositions;

public:
    Board(int r, int c, int gM) : row(r), col(c), checkValid(false), gameMode(gM), turn(1) {

        grid = new int*[row];

        for ( int i = 0; i < row; i++ )
        {
            grid[i] = new int[col];
            for ( int j = 0; j < col; j++ )
            {
                grid[i][j] = 0;
            }
        }

        neighbour = new Neighbour*[row];

        for ( int i = 0; i < row; i++ )
        {
            neighbour[i] = new Neighbour[col];
            for ( int j = 0; j < col; j++ )
                neighbour[i][j].initialise();
        }
    }

    ~Board() {
        for (int i = 0; i < row; i++)
            delete[] grid[i];

        delete[] grid;
    }

    bool addMove(int x, int y);
    void setNeighbours(int, int);
    void printBoard();
    void play();
    bool checkFullBoard();
    void checkWinner();
    void randomiseMoves();
};

bool Board::addMove(int x, int y)
{
    if ( x >= 0 && x < col && y >= 0 && y < row )
    {
        if ( grid[x][y] == 0 )
        {
            grid[x][y] = turn;
            if ( turn == 1 )
                turn = -1;
            else if ( turn == -1 )
                turn = 1;

            setNeighbours(x, y);
            return true;
        }
        else
            return false;
    } else
        return false;
}

void Board::setNeighbours(int x, int y)
{
    if ( x != 0 && x != row - 1 ) {
        values[0] = grid[x-1][y];
        values[2] = grid[x+1][y];
    }

    else if ( x == 0 ) {
        values[0] = 8;
        values[2] = grid[x+1][y];
    }

    else if ( x == row - 1 ) {
        values[0] = grid[x-1][y];
        values[2] = 8;
    }


    if ( y != 0 && y != col - 1 ) {
        values[1] = grid[x][y+1];
        values[3] = grid[x][y-1];
    }

    else if ( y == 0 ) {
        values[1] = grid[x][y+1];
        values[3] = 8;
    }

    else if ( y == col - 1 ) {
        values[1] = 8;
        values[3] = grid[x][y-1];
    }

    neighbour[x][y].setNeighbour(directions, values);
}

void Board::play() {
    int x, y;
    int counter = 0;
    srand(time(nullptr));

    for ( int i = 0; i < row * col; i++)
        gamePositions.push_back(i);

    if ( gameMode == 2 || gameMode == 3 )
        randomiseMoves();


    do {
        cout << "Game board:" << endl;

        if ( gameMode == 1 )
        {
            do
            {
                cout << "Input your move with row and column numbers:" << endl;
                cin >> x >> y;
                x--;
                y--;
                checkValid = addMove(x, y);
                if ( !checkValid )
                {
                    cout << "Invalid move. Try again." << endl;
                    this->printBoard();
                }
            } while ( !checkValid );
        }

        else if ( gameMode == 2 )
        {
            do
            {
                if ( turn == 1 )
                {
                    cout << "Input your move with row and column numbers:" << endl;
                    cin >> x >> y;
                    x--;
                    y--;
                    checkValid = addMove(x, y);
                    if ( !checkValid )
                    {
                        cout << "Invalid move. Try again." << endl;
                        this->printBoard();
                    }
                }

                else if ( turn == -1 )
                {
                    x = gamePositions[counter] / col;
                    y = gamePositions[counter] % col;
                    checkValid = addMove(x, y);
                    counter++;
                    if ( counter == gamePositions.size() )
                    {
                        randomiseMoves();
                        counter = 0;
                    }
                }
            } while ( !checkValid );
        }

        else if ( gameMode == 3 )
        {
            do
            {

                x = gamePositions[counter] / col;
                y = gamePositions[counter] % col;
                checkValid = addMove(x, y);
                counter++;
                if ( counter == gamePositions.size() )
                {
                    randomiseMoves();
                    counter = 0;
                }
            } while ( !checkValid );
        }

        if ( neighbour[x][y].calculatePips() != 0 && neighbour[x][y].calculatePips() <= 6 )
        {
            if ( turn == -1 )
            {
                grid[x][y] = neighbour[x][y].calculatePips();
            }
            else if ( turn == 1 )
            {
                grid[x][y] = -(neighbour[x][y].calculatePips());
            }

            bool *capturedNeighbours;
            capturedNeighbours = neighbour[x][y].removeCapturedNeighbours();

            if ( capturedNeighbours[0] == true )
                grid[x-1][y] = 0;
            if ( capturedNeighbours[1] == true )
                grid[x][y+1] = 0;
            if ( capturedNeighbours[2] == true )
                grid[x+1][y] = 0;
            if ( capturedNeighbours[3] == true )
                grid[x][y-1] = 0;
        }
        this->printBoard();
        neighbour[x][y].printPips();

    } while (!checkFullBoard());

    cout << "Game board:" << endl;
    this->printBoard();
    checkWinner();
}

void Board::randomiseMoves()
{
    int firstNo, secondNo, tempNo;
    for ( int i = 0; i < row * col; i++)
    {
        firstNo = gamePositions[i];
        secondNo = rand() % gamePositions.size();

        tempNo = gamePositions[firstNo];
        gamePositions[firstNo] = gamePositions[secondNo];
        gamePositions[secondNo] = tempNo;
    }
}

bool Board::checkFullBoard()
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 0)
                return false;
        }
    }
    return true;
}

void Board::checkWinner()
{
    int counter1, counter2;
    counter1 = counter2 = 0;

    for ( int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j] > 0)
                counter1++;

            else if (grid[i][j] < 0)
                counter2++;
        }
    }

    if ( counter1 > counter2 )
        cout << "Player 1 wins!" << endl;
    else if ( counter1 < counter2 )
        cout << "Player 2 wins!" << endl;
    else if ( counter1 == counter2 )
        cout << "Its a draw..." << endl;
}

void Board::printBoard() {
    cout << "     ";
    for (int j = 0; j < col; j++) {
        if ( j > 8 )
            cout << j + 1 << "  ";
        else
            cout << j + 1 << "   ";
    }
    cout << endl;

    for (int i = 0; i < row; i++) {
        cout << "   ";
        for (int j = 0; j < col; j++) {
            cout << " ---";
        }
        cout << endl;
        if ( i > 8 )
            cout << (i + 1) << " |";
        else
            cout << (i + 1) << "  |";

        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 0)
                cout << "   |";
            else if (grid[i][j] > 0)
                cout << " " << grid[i][j] << " |";
            else if (grid[i][j] < 0)
                cout << "" << grid[i][j] << " |";

        }
        cout << endl;
    }
    cout << "   ";

    for (int j = 0; j < col; j++) {
        cout << " ---";
    }
    cout << endl << endl;
}



#endif //CEPHALOPOD_BOARD_H