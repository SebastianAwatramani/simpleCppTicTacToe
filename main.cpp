#include <iostream>
#include <string>
#include <windows.h>//::SetConsoleTextAttribute
using namespace std;

const int ROW_SIZE = 3;
const int COL_SIZE = 3;
const int PRIMARY_COLOR = 7;
const int SECONDARY_COLOR = 2;

//Function prototypes
bool checkWin(string board[][COL_SIZE], bool& tie);
void getMove(char& playerTurn, string board[][COL_SIZE]);
void printGameBoard(string board[][COL_SIZE]);
bool quitProgram();
void switchPlayer(char &playerTurn);


int main()
{
	bool quit = false; //Init
	bool tie = true; //Init
	
	do {
		char playerTurn = 'X'; //Init
		bool gameOver = false; //Init

		string board[ROW_SIZE][COL_SIZE] = 
			{
			{"*","*","*"},
			{"*","*","*"},
			{"*","*","*"}
			}; //Init array
		do
		{
			printGameBoard(board); //Function to print the game board
			getMove(playerTurn, board); //Get player move
			gameOver = checkWin(board, tie); //Check for win or tie
			
			if (gameOver == false)
			{ //End if
				switchPlayer(playerTurn); //Switch player after turn if game isn't over
			}
			else 
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SECONDARY_COLOR); //When game is over, print last iteration of the board in a different color just for effect
				printGameBoard(board);
			} //End else
		} while (gameOver == false); //End do...while

		if (tie == false) 
		{
			cout << "Player " << playerTurn << " Wins!\n"; //Player win output
		} //End if
		
		quit = quitProgram(); //Function to quit program

	} while (quit == false); //End do...while
	
	system("pause");
	return 0;
} //End main()

bool checkWin(string board[][COL_SIZE], bool& tie) //Function to check for win or tie
{
	const int PRIMARY_INDEX = 0;
	const int SECONARY_INDEX = 1;
	const int TERTIARY_INDEX = 2;

	//Checks rows for win
	for (int y = 0; y < ROW_SIZE; y++) 
	{
		if (board[PRIMARY_INDEX][y] != "*")
		{
			if (board[PRIMARY_INDEX][y] == board[SECONARY_INDEX][y] && board[SECONARY_INDEX][y] == board[TERTIARY_INDEX][y]) 
			{
			  return true;
			} //End if
		} //End if
	} //End for
	//Check cols for win
    for (int x = 0; x < COL_SIZE; x++) 
	{
		if (board[x][PRIMARY_INDEX] != "*")
		{
			if (board[x][PRIMARY_INDEX] == board[x][SECONARY_INDEX] && board[x][SECONARY_INDEX] == board[x][TERTIARY_INDEX]) 
			{
			  return true;
			} //End if
		} //End if
    } //End for

	//Check diagonals for win
	if (board[PRIMARY_INDEX][PRIMARY_INDEX] != "*")
	{
		if (board[PRIMARY_INDEX][PRIMARY_INDEX] == board[SECONARY_INDEX][SECONARY_INDEX] && board[SECONARY_INDEX][SECONARY_INDEX] == board[TERTIARY_INDEX][TERTIARY_INDEX]) 
		{
			return true;
		} //End if
	} //End if
	if (board[TERTIARY_INDEX][PRIMARY_INDEX] != "*")
	{
		if (board[TERTIARY_INDEX][PRIMARY_INDEX] == board[SECONARY_INDEX][SECONARY_INDEX] && board[SECONARY_INDEX][SECONARY_INDEX] == board[PRIMARY_INDEX][TERTIARY_INDEX]) 
		{
			return true;
		} //End if
	} //End if

	//Check for tie
	tie = true; //Set/reset tie to true, and it will be set to false if there is still a * left on the board
	
	for (int row = 0; row < ROW_SIZE; row++)
	{
		for (int col = 0; col < COL_SIZE; col++)
		{
			if (board[row][col] == "*")
			{
				tie = false;
			} //End if
		} //End for
	} //End for

	if (tie == true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SECONDARY_COLOR);
		cout << "It's a TIE\n";
		return true;
	} //End if

	return false; //Default
} //End checkWin()

//Function to get and validate the player's move
void getMove(char& playerTurn, string board[][COL_SIZE]) 
{
	int row, col; //Init local variable
	const int MINROW = 1; //Dec const
	
	do {
		cout << "Enter row for player " << playerTurn << "\n"; //Request row
		cin >> row; //Get input for row

		while(row > ROW_SIZE || row < MINROW) //Make sure input is a valid row
		{
			cout << "You entered an invalid row.  Please enter a row between 1 and 3";
			cin >> row;
		} //End while

		cout << "Enter col for player " << playerTurn << "\n"; //Request column
		cin >> col; //Get column input

		while(col > COL_SIZE || col < MINROW) //Make sure input is a valid column
		{
			cout << "You entered an invalid column.  Please enter a column between 1 and 3";
			cin >> col;
		} //End while

		if (board[row -MINROW][col - MINROW] != "*") //Check to see that space was free
		{
			cout << "You entered a space that was already occupied.  Try again.\n";
		} //End if
	} while (board[row - MINROW][col - MINROW] != "*"); //End do...while
		
	board[row - MINROW][col - MINROW] = playerTurn; //If input is good, update board
} //End getMove()

void printGameBoard(string board[][COL_SIZE]) //Function to print gameboard
{
	const int PLUSONE = 1; //dec const

	cout << "     1 2 3\n"; //Print top header
	for (int row = 0; row < ROW_SIZE; row++)
	{
		cout << row + PLUSONE << "   "; //Print side header

		for (int col = 0; col < COL_SIZE; col++)
		{
			cout << "|" << board[row][col]; //Print columns
		} //End for
		cout << "|" << "\n";
	} //End for
} //End printGameBoard()

bool quitProgram() //Function to quit program, if user desires
{
	string quit; //Local variable
	const int QUITMAX = 1;
	const int QUIT_INDEX = 0;
	
	do { //While input is not equal to c or q, or while input length greater than 1
		cout << "Coninue? Enter c to continue or q to quit\n";
		cin >> quit;
		quit[QUIT_INDEX] = tolower(quit[QUIT_INDEX]); //To lower, for case insensitve comparison.  Only first character because we will only accept 1 anyway.

	} while (((quit != "c") && (quit != "q")) || (quit.length() > QUITMAX)); //End do...while

	if (quit == "q")
	{
		return true; //If quit
	} //End if
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PRIMARY_COLOR);
		cout << "***NEW GAME***\n";
		return false; //If continue
	} //End else
} //end quitProgram()

void switchPlayer(char& playerTurn) //Function to switch the player after each turn
{
	switch(playerTurn)
	{
	case 'X':
		playerTurn = 'O';
		break;
	case 'O':
		playerTurn = 'X';
		break;
	} //End switch
} //End switchPlayer()
