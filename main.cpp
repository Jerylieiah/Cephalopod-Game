/*********** Declaration*******
I hereby certify that no part of this assignment has been copied from
any other student’s work or from any other source. No part of the code
has been written/produced for me by another person or copied from any
other source.
I hold a copy of this assignment that I can produce if the original is
lost or damaged.
**************************/

#include "board.h"

using namespace std;

int main()
{
    int row, col, gameMode;
    cout << "Input the number of rows: ";
    cin >> row;
    cout << endl;

    cout << "Input the number of columns: ";
    cin >> col;
    cout << endl;

    cout << "Select number for game mode" << endl;
    cout << "1. Human vs Human" << endl;
    cout << "2. Human vs Random" << endl;
    cout << "3. Random vs Random" << endl;
    cin >> gameMode;

    Board board(row, col, gameMode);
    board.play();

    return 0;
}