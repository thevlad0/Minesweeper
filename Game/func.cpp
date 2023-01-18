#include "func.h"
#include <iostream>

//For the purpose of using rand()
#include <cstdlib>
#include <ctime>

void displayUnderMines()
{
	cout << underMines;
}

void displayOverMines()
{
	cout << overMines;
}

void displayNegativeSize()
{
	cout << negativeSize;
}

void displayInvalidSize()
{
	cout << invalidSize;
}

void displayUnknownCommand()
{
	cout << unknownCommand;
}

errorMessage validMines(int input, size_t matrixSize)
{
	if (input < 1)
		return displayUnderMines;
	if(input > (3 * matrixSize))
		return displayOverMines;
}

errorMessage validMatrix(int matrixSize)
{
	if(matrixSize < 0)
		return displayNegativeSize;
	if (matrixSize < 3 || matrixSize > 10)
		return displayInvalidSize;
}

errorMessage validCommand(const char* command, unsigned x, unsigned y, size_t commandLen)
{
	if(commandLen > 10)
		return displayUnknownCommand;
	
}

size_t getLen(const char* str)
{
	size_t index = 0;

	while(str[index] != '\0')
		index++;

	return index;
}

unsigned getRand(size_t matrixSize)
{
	srand(time(0));
	return rand() % matrixSize; //[0, matrixSize - 1]
}

void initializeGame(size_t matrixSize, unsigned mines)
{
	for (size_t i = 0; i < mines; i++)
	{
		unsigned x = getRand(matrixSize);
		unsigned y = getRand(matrixSize);

		//'9' will mean there is a mine in the cell
		if(matrix[x][y] != 9)
			matrix[x][y] = 9;
		else
			i--;
	}

	for (size_t i = 0; i < matrixSize; i++)
	{
		for (size_t j = 0; j < matrixSize; j++)
		{
			if(matrix[i][j] == 9) {
				if(!i && !j) {
					matrix[i + 1][j]++;
					matrix[i][j + 1]++;
					continue;
				}

				if(i == matrixSize - 1 || j == matrixSize - 1) {
					if(i == matrixSize - 1) {
						matrix[i - 1][j]++;
						matrix[i][j + 1]++;
					}
				}

				if(i + 1 > 2 && j + 1 > 2) {
					for (size_t s = j - 1; s < j + 1; s++) 
					{
						matrix[i - 1][j]++;
						matrix[i + 1][j]++;
					}
					matrix[i][j - 1]++;
					matrix[i][j + 1]++;
				}

			}
		}
		
	}
	
	
}

void printMatrix(size_t matrixSize, bool &gameOver)
{

}