#include "func.cpp"
#include <iostream>

int main()
{
    cout << welcome;
    cout << sizeOfMatrix;
    
    int matrixSize;
    cin >> matrixSize;
    while(!validMatrix(matrixSize)) {
        if(matrixSize < 0)
            cout << negativeSize;

        cout << invalidSize;
        cin >> matrixSize;
    }

    int mines;
    cin >> mines;
    while(!validMines(matrixSize, mines)) {
        if(mines < 1)
            cout << underMines;

        cout << overMines;
        cin >> mines;
    }
    
    cout << goodLuck;
    unsigned foundMines = 0;
    do
    {
        cout << gamePlay;

        char command[5];
        unsigned x, y;
        cin >> command >> x >> y;
        if(!doCommand) {
            cout << unknownCommand;
            continue;
        }

    } while (printMatrix(matrixSize, mines, foundMines));
    
}