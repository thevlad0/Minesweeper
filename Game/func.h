#pragma once

//The matrix we're going to use as the play field
static unsigned matrix[10][10] = { 0 };

//The max symbol length of a command
const unsigned MAX_COMMAND_LEN = 10;

using namespace std;

//In-game messages:
const char welcome[] = "Hello and welcome to Minesweeper! First let's give you some info:\n"
					   "\nIn this game you will be given the opportunity to choose your matrix\n"
					   "size and the number of mines in the game. To give a command type in:\n"
					   "	   [command] [coordinate x] [coordinate y]\n\nRemember that x and y correspond to the row"
					   " and column of each cell on \nthe field and the only commands available are: open, mark and unmark.\n"
					   "\nAlso you should keep in mind the following: '.' means the cell is unmarked,\n'x' means the cell"
					   " has been marked and '*' means you've found a bomb."
					   "\n\nSo what are you waiting for, let's start already ;)\n";
const char sizeOfMatrix[] = "\nPlease choose the size of your field: ";
const char numberOfMines[] = "\nPlease choose the number of mines you want to be hidden: ";
const char goodLuck[] = "We're all set to go! Please wait for the game to start, this may take a few seconds!\n";
const char gamePlay[] = "\n\nPlease type in your command: ";
const char exploded[] = "\nOops, looks like you exploded and now the game is over :(\n"
						"Please exit the game and open it again to restart.\n";
const char win[] = "\n\nWow, wow, wow, looks like you actually managed to beat the game!\n"
				   "The odds were stacked against you but you really pushed through. Congratulations :)\n";

//Error messages:
const char unknownCommand[] = "Oops, seems like I ran into a problem completing your request."
							  "\nPlease check your input and try again.\n";
const char invalidSize[] = "Ooops, forgot to mention, the field can only go up to 10 and cannot be below 3 :)"
						   "\nNow that you know that, try again.\n";
const char overMines[] = "Ooops, seems you're trying put too many mines on the field.\n"
						 "Let's try this once again.\n";
const char underMines[] = "Ooops, the game won't be any fun if there are no mines\n"
						  "Please try once more.\n";
const char negativeSize[] = "Have you ever heard of a square with a negative side "
							"length?\nWell neither have I, so let's try again!\n";
const char invalidCoordinates[] = "Don't try to access the infinite darkness of the console.\n"
								  "You don't know what's hiding there :)))\nLet's try again!\n";

//In-game commands:
const char mark[] = "mark";
const char unmark[] = "unmark";
const char open[] = "open";

//Checks if the number of mines entered is valid
bool validMines(int input, size_t matrixSize);

//Checks if the matrix size is valid
bool validMatrix(int matrixSize);

//Checks if the coordinate entered is within the matrix
bool validCoordinate(int coordinate, size_t matrixSize);

//Compares two strings
bool strCompare(const char* str1, const char* str2);

//Returns a random integer in a specified range
unsigned getRand(size_t matrixSize);

//Initializes the mines on the field
void initializeGame(size_t size, unsigned mines);

void zeroFound(int x, int y, size_t matrixSize);

//Checks and completes whichever command has been called
bool doCommand(char* command, unsigned x, unsigned y, size_t matrixSize, unsigned& foundMines, unsigned& marked);

//Prints out the current state of the playfield and determines whether the game is over
bool printMatrix(size_t size, unsigned mines, unsigned foundMines, unsigned marked);
