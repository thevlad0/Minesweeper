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
				
				//Left upper corner
				if(!i && !j) {
					matrix[i + 1][j]++;
					matrix[i][j + 1]++;
					continue;
				}

				//Left upper corner
				if(!i && j == matrixSize - 1) {
						matrix[i - 1][j]++;
						matrix[i][j - 1]++;
						continue;
				}

				//Right lower corner
				if(i == matrixSize - 1 && !j) {
					matrix[i - 1][j]++;
					matrix[i][j + 1]++;
					continue;
				}

				//Right lower corner
				if(i == matrixSize - 1 && j == matrixSize - 1) {
						matrix[i - 1][j]++;
						matrix[i][j - 1]++;
						continue;
				}

				//Upper contour
				if(!i) {
					matrix[i][j - 1]++;
					matrix[i][j + 1]++;
					for (size_t s = j - 1; s < j + 1; s++)
						matrix[i + 1][s]++;
					continue;
				}

				//Lower contour
				if(i == matrixSize - 1) {
					matrix[i][j - 1]++;
					matrix[i][j + 1]++;
					for (size_t s = j - 1; s < j + 1; s++)
						matrix[i - 1][s]++;
					continue;
				}

				//Left contour
				if(j == matrixSize - 1) {
					matrix[i - 1][j]++;
					matrix[i + 1][j]++;
					for (size_t s = i - 1; s < i + 1; s++)
						matrix[s][j + 1]++;
					continue;
				}

				//Right contour
				if(!j) {
					matrix[i - 1][j]++;
					matrix[i + 1][j]++;
					for (size_t s = i - 1; s < i + 1; s++)
						matrix[s][j - 1]++;
					continue;
				}

				//Any center
				if(i + 1 > 2 && j + 1 > 2) {
					for (size_t s = j - 1; s < j + 1; s++) 
					{
						matrix[i - 1][s]++;
						matrix[i + 1][s]++;
					}
					matrix[i][j - 1]++;
					matrix[i][j + 1]++;
				}

			}
		}
		
	}
}

errorMessage doCommand(char* command, unsigned x, unsigned y)
{
	if(command == open)
		matrix[x][y] += 20;
	if(command == mark)
		matrix[x][y] += 10;
	if(command == unmark) {
		if(matrix[x][y] < 10)
			return displayUnknownCommand;
		else
			matrix[x][y] -= 10;
	}	
}

bool printMatrix(size_t matrixSize)
{
	bool mineFound = false, gameOver = true;

	cout << '\t';
	for (size_t i = 0; i < matrixSize; i++)
		cout << '\t' << i << '\t';

	cout << endl << '\t';
	
	for (size_t i = 0; i < 3*matrixSize; i++)
		cout << '_';

	for (size_t i = 0; i < matrixSize; i++)
	{
		cout << endl << i << "\t |";
		for (size_t j = 0; j < matrixSize; j++)
		{
			//Opened a mine
			if(matrix[i][j] == 29) {
				cout << '*' << '\t';
				mineFound = true;
				continue;
			}

			//It was previously opened
			if(matrix[i][j] > 20) {
				cout << matrix[i][j];
			}

			//It was previously marked
			if(matrix[i][j] > 10) {
				cout << 'x' << '\t';
				gameOver = false; //There is atleast one unopened cell
			}
			else {
				cout << 'o' << '\t';
				gameOver = false; //There is atleast one unopened cell
			}
		}
		cout << endl << " \t |";
	}

	//There are still cells to open and no mine was found
	if(!gameOver && !mineFound)
		return true;
	
	//The game has ended
	return false;
}