/**
*  
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Vladimir Velikov
* @idnumber 0MI0600204
* @compiler VS
*
* <file that contains the main function>
*
*/

#include "func.h"
#include <iostream>

int main()
{
    cout << welcome;
    cout << sizeOfMatrix;

    int matrixSize;
    cin >> matrixSize;
    while (!validMatrix(matrixSize)) {
        if (matrixSize < 0)
            cout << negativeSize;
        else
            cout << invalidSize;

        cout << sizeOfMatrix;
        cin >> matrixSize;
    }

    cout << numberOfMines;
    int mines;
    cin >> mines;
    while (!validMines(mines, matrixSize)) {
        if (mines < 1)
            cout << underMines;
        else
            cout << overMines;

        cout << numberOfMines;
        cin >> mines;
    }

    cout << goodLuck;
    unsigned foundMines = 0, marked = 0;
    initializeGame(matrixSize, mines);
    while (!printMatrix(matrixSize, mines, foundMines, marked)) {
        cout << gamePlay;

        char command[11];
        unsigned x, y;
        cin >> command >> x >> y;
        if (!validCoordinate(x, matrixSize) || !validCoordinate(y, matrixSize)) {
            cout << invalidCoordinates;
            continue;
        }
        if (!doCommand(command, x, y, matrixSize, foundMines, marked)) {
            cout << unknownCommand;
            continue;
        }
    }
}
