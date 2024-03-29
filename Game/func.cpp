#include "func.h"
#include <iostream>

//For the purpose of using rand()
#include <cstdlib>
#include <ctime>

bool validMines(int input, size_t matrixSize)
{
	if (input < 1 || input > (3 * matrixSize))
		return false;

	return true;
}

bool validMatrix(int matrixSize)
{
	if (matrixSize < 3 || matrixSize > 10)
		return false;

	return true;
}

bool validCoordinate(int coordinate, size_t matrixSize)
{
	if (coordinate > matrixSize - 1)
		return false;
	if (coordinate < 0)
		return false;

	return true;
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
		if (matrix[x][y] != 9) //If there is no mine in the cell
			matrix[x][y] = 9;
		else
			i--;
	}

	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			if (matrix[i][j] == 9) {

				for (int k = i - 1; k <= i + 1; k++)
				{
					for (int s = j - 1; s <= j + 1; s++)
					{
						if (validCoordinate(k, matrixSize) && validCoordinate(s, matrixSize)) {
							if(matrix[k][s] != 9)
								matrix[k][s]++;
						}
					}
				}
			}
		}

	}
}

bool strCompare(const char* str1, const char* str2)
{
	size_t index = 0;
	while (str1[index] != '\0') {
		if (str1[index] != str2[index])
			return false;

		index++;
	}

	//They didn't have the same length
	if(str2[index] != '\0')
		return false;

	return true;
}

void zeroFound(int x, int y, size_t matrixSize)
{
	matrix[x][y] += 20;

	if (matrix[x][y] != 20)
		return;

	if (validCoordinate(x - 1, matrixSize) && validCoordinate(y - 1, matrixSize)) {
		zeroFound(x - 1, y - 1, matrixSize);
	}

	if (validCoordinate(x, matrixSize) && validCoordinate(y - 1, matrixSize)) {
		zeroFound(x, y - 1, matrixSize);
	}

	if (validCoordinate(x + 1, matrixSize) && validCoordinate(y - 1, matrixSize)) {
		zeroFound(x + 1, y - 1, matrixSize);
	}

	if (validCoordinate(x - 1, matrixSize) && validCoordinate(y + 1, matrixSize)) {
		zeroFound(x - 1, y + 1, matrixSize);
	}

	if (validCoordinate(x, matrixSize) && validCoordinate(y + 1, matrixSize)) {
		zeroFound(x, y + 1, matrixSize);
	}

	if (validCoordinate(x + 1, matrixSize) && validCoordinate(y + 1, matrixSize)) {
		zeroFound(x + 1, y + 1, matrixSize);
	}

	if (validCoordinate(x - 1, matrixSize) && validCoordinate(y, matrixSize)) {
		zeroFound(x - 1, y, matrixSize);
	}

	if (validCoordinate(x + 1, matrixSize) && validCoordinate(y, matrixSize)) {
		zeroFound(x + 1, y, matrixSize);
	}

	return;
}

bool doCommand(char* command, unsigned x, unsigned y, size_t matrixSize, unsigned& foundMines, unsigned &marked)
{
	//Determines whether the cell has undergone a valid command
	bool hasChanged = false;

	if (strCompare(command, open)) {
		if (matrix[x][y] >= 20) //Already opened
			return false;
		if (matrix[x][y] > 10) //Previously marked
			matrix[x][y] += 10;
		else {
			matrix[x][y] += 20;
			if (matrix[x][y] == 29) {
				for (size_t i = 0; i < matrixSize; i++)
				{
					for (size_t j = 0; j < matrixSize; j++)
					{
						if (matrix[i][j] == 9)
							matrix[i][j] += 20;
						if (matrix[i][j] == 19)
							matrix[i][j] += 10;
					}
				}
			}
		}
			

		if (matrix[x][y] == 20) {
			matrix[x][y] -= 20;
			zeroFound(x, y, matrixSize);
		}
		hasChanged = true;
	}
	else if (strCompare(command, mark)) {
		if (matrix[x][y] >= 10) //Already marked/opened
			return false;
		if (matrix[x][y] == 9)
			foundMines++;

		matrix[x][y] += 10;
		marked++;
		hasChanged = true;
	}
	else if (strCompare(command, unmark)) {
		if (matrix[x][y] >= 20) //Already opened
			return false;
		if (matrix[x][y] < 10) //Is not marked
			return false;
		else {
			matrix[x][y] -= 10;
			marked--;
			if (matrix[x][y] == 9)
				foundMines--;
			hasChanged = true;
		}
	}

	if (!hasChanged)
		return false;

	return true;
}

bool printMatrix(size_t matrixSize, unsigned mines, unsigned foundMines, unsigned marked)
{
	bool mineFound = false;

	cout << "\nCurrent state of the board:\n";

	cout << endl << "   ";
	for (size_t i = 0; i < matrixSize; i++)
		cout << i << "  ";

	cout << endl << "  ";

	for (size_t i = 0; i < 3 * matrixSize; i++)
		cout << '_';

	for (size_t i = 0; i < matrixSize; i++)
	{
		cout << endl << i << " |";
		for (size_t j = 0; j < matrixSize; j++)
		{
			//Opened a mine
			if (matrix[i][j] == 29) {
				cout << '*' << "  ";
				mineFound = true;
				continue;
			}

			//It was previously opened
			if (matrix[i][j] >= 20) {
				cout << matrix[i][j] % 20 << "  ";
				
				continue;
			}

			//It was previously marked
			if (matrix[i][j] >= 10) {
				cout << 'x' << "  ";
			}
			else {
				cout << '.' << "  ";
			}
		}
		if(i != matrixSize - 1)
			cout << endl << "  |";
	}

	//There are still cells to open and no mine was found
	if (mineFound) {
		cout << exploded;
		return true;
	}

	if (foundMines == mines && foundMines == marked) {
		cout << win;
		return true;
	}

	return false;
}
