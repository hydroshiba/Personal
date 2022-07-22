#include<bits/stdc++.h>
using namespace std;

#define COMPUTER 0
#define HUMAN 1

#define SIDE 3 // Length of the board

// Computer will move with 'O'
// and human with 'X'
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

bool checked[SIDE * SIDE + 1] = { 0,0,0,0,0,1,0,0,0,0 };
int c = 1;
char board[SIDE][SIDE];

// A function to show the current board status
void showBoard() {
	printf("\n\n");

	printf("\t\t\t  %c | %c  | %c  \n", board[0][0],
		board[0][1], board[0][2]);
	printf("\t\t\t--------------\n");
	printf("\t\t\t  %c | %c  | %c  \n", board[1][0],
		board[1][1], board[1][2]);
	printf("\t\t\t--------------\n");
	printf("\t\t\t  %c | %c  | %c  \n\n", board[2][0],
		board[2][1], board[2][2]);

	return;
}

// A function to show the instructions
void showInstructions()
{
	printf("\t\t\t  Tic-Tac-Toe\n\n");
	printf("Choose a cell numbered from 1 to 9 as below"
		" and play\n\n");
	printf("\t\t\t  1 | 2  | 3  \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t  4 | 5  | 6  \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t  7 | 8  | 9  \n\n");
	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
	return;
}


// A function to initialize the game
void initialize(int moves[]) {
	// Initiate the random number generator so that
	// the same configuration doesn't arises
	srand(time(NULL));
	// Initially the board is empty
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++)
			board[i][j] = ' ';
	}
	// Fill the moves with numbers
	for (int i = 0; i < SIDE * SIDE; i++)
		moves[i] = i;

	// randomise the moves
	random_shuffle(moves, moves + SIDE * SIDE);
	return;
}

// A function to declare the winner of the game
void declareWinner(int whoseTurn) {
	if (whoseTurn == COMPUTER)
		printf("COMPUTER has won\n");
	else
		printf("HUMAN has won\n");
	system("pause");
	return;
}

// A function that returns true if any of the row
// is crossed with the same player's move
bool rowCrossed() {
	for (int i = 0; i < SIDE; i++)
	{
		if (board[i][0] == board[i][1] &&
			board[i][1] == board[i][2] &&
			board[i][0] != ' ')
			return (true);
	}
	return(false);
}

// A function that returns true if any of the column
// is crossed with the same player's move
bool columnCrossed() {
	for (int i = 0; i < SIDE; i++)
	{
		if (board[0][i] == board[1][i] &&
			board[1][i] == board[2][i] &&
			board[0][i] != ' ')
			return (true);
	}
	return(false);
}

// A function that returns true if any of the diagonal
// is crossed with the same player's move
bool diagonalCrossed() {
	if (board[0][0] == board[1][1] &&
		board[1][1] == board[2][2] &&
		board[0][0] != ' ')
		return(true);

	if (board[0][2] == board[1][1] &&
		board[1][1] == board[2][0] &&
		board[0][2] != ' ')
		return(true);

	return(false);
}

// A function that returns true if the game is over
// else it returns a false
bool gameOver()
{
	return(rowCrossed() || columnCrossed()
		|| diagonalCrossed());
}

// A function that checks if human move is valid
bool isValid(int move) {
	if (move > 9 || move < 1) return false;
	int x = move / SIDE, y = (move % SIDE) - 1;
	return !((board[x][y] == COMPUTERMOVE || board[x][y] == HUMANMOVE));
}

void calculate(int& cell) {
	int tempcell = 5;
	cell = tempcell;
	int x = tempcell / SIDE;
	int y = (tempcell % SIDE) - 1;
	if (board[x][y] != COMPUTERMOVE && board[x][y] != HUMANMOVE) return;
	tempcell = int(rand()) % (SIDE * SIDE) + 1;
	x = tempcell / SIDE;
	y = (tempcell % SIDE) - 1;
	if (isValid(tempcell) && !checked[tempcell]) {
		cell = tempcell;
		board[x][y] = HUMANMOVE;
		if (rowCrossed() || columnCrossed() || diagonalCrossed()) {
			board[x][y] = ' ';
			return;
		}
		board[x][y] = COMPUTERMOVE;
		if (rowCrossed() || columnCrossed() || diagonalCrossed()) {
			board[x][y] = ' ';
			return;
		}
		board[x][y] = ' ';
	}
	if (!checked[tempcell]) {
		checked[tempcell] = true;
		++c;
	}
	if (c < 9) calculate(cell);
}

void resetCheck() {
	for (int i = 1; i < 10; ++i) {
		checked[i] = 0;
	}
	checked[5] = 1;
	c = 1;
}

// A function to play Tic-Tac-Toe
void playTicTacToe(int whoseTurn) {
	// A 3*3 Tic-Tac-Toe board for playing
	int moves[SIDE * SIDE];
	// Initialise the game
	initialize(moves);
	// Show the instructions before playing
	showInstructions();
	int moveIndex = 0, x, y;
	// Keep playing till the game is over or it is a draw
	while (gameOver() == false &&
		moveIndex != SIDE * SIDE) {
		if (whoseTurn == COMPUTER)
		{
			int cell = 0;
			resetCheck();
			while (!isValid(cell)) {
				calculate(cell);
				resetCheck();
			}
			x = cell / SIDE;
			y = (cell % SIDE) - 1;
			board[x][y] = COMPUTERMOVE;
			printf("COMPUTER has put a %c in cell %d\n",
				COMPUTERMOVE, cell);
			showBoard();
			moveIndex++;
			whoseTurn = HUMAN;
		}

		else if (whoseTurn == HUMAN)
		{
			int cell = 0;
			cin >> cell;
			while (!isValid(cell)) {
				cout << "Outstanding move. We don't do that here, please try again" << '\n';
				cin >> cell;
			}
			x = cell / SIDE;
			y = (cell % SIDE) - 1;
			board[x][y] = HUMANMOVE;
			printf("HUMAN has put an %c in cell %d\n",
				HUMANMOVE, cell);
			showBoard();
			moveIndex++;
			whoseTurn = COMPUTER;
		}
	}
	// If the game has drawn
	if (gameOver() == false && moveIndex == SIDE * SIDE) {
		printf("It's a draw!\n");
		system("pause");
	}
	else
	{
		// Toggling the user to declare the actual
		// winner
		whoseTurn = !whoseTurn;
		// Declare the winner
		declareWinner(whoseTurn);
	}
	return;
}

// Driver program
int main() {
	// Let us play the game with COMPUTER starting first
	srand(NULL);
	playTicTacToe(COMPUTER);
	return (0);
}
