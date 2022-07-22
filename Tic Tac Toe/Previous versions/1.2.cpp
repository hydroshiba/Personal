#define ROBOT 0
#define HUMAN 1
#define ROBOTMOVE 'O'
#define HUMANMOVE 'X'

#include <bits/stdc++.h>
using namespace std;

const int SIDE = 3;
char board[SIDE][SIDE];

int x(int cell) {
	return cell / SIDE;
}

int y(int cell) {
	return (cell % SIDE) - 1;
}

void init() {
	for (int i = 0; i < SIDE; ++i) {
		for (int j = 0; j < SIDE; ++j) {
			board[i][j] = ' ';
		}
	}
}

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
}

bool rowCrossed() {
	for (int i = 0; i < SIDE; i++)
	{
		if (board[i][0] == board[i][1] &&
			board[i][1] == board[i][2] &&
			board[i][0] != ' ')
			return 1;
	}
	return 0;
}

bool columnCrossed() {
	for (int i = 0; i < SIDE; i++)
	{
		if (board[0][i] == board[1][i] &&
			board[1][i] == board[2][i] &&
			board[0][i] != ' ')
			return 1;
	}
	return 0;
}

bool diagonalCrossed() {
	if (board[0][0] == board[1][1] &&
		board[1][1] == board[2][2] &&
		board[0][0] != ' ')
		return 1;

	if (board[0][2] == board[1][1] &&
		board[1][1] == board[2][0] &&
		board[0][2] != ' ')
		return 1;

	return 0;
}

bool crossCheck() {
	return (rowCrossed() || columnCrossed() || diagonalCrossed());
}

bool isValid(int move) {
	return (board[x(move)][y(move)] == ' ');
}

void calculate(int& cell) {
	const int cells[] = { 8,6,2,4,7,3,9,1,5 };
	cell = 0;
	int tempcell, lastgoodcell;
	for (int i = 0; i < 9; ++i) {
		tempcell = cells[i];
		while (!isValid(tempcell) && i < 8) {
			++i;
			tempcell = cells[i];
		}
		if (isValid(tempcell)) {
			board[x(tempcell)][y(tempcell)] = ROBOTMOVE;
			if (crossCheck()) {
				cell = tempcell;
				board[x(cell)][y(cell)] = ' ';
				return;
			}
			board[x(tempcell)][y(tempcell)] = HUMANMOVE;
			if (crossCheck()) cell = tempcell;
			board[x(tempcell)][y(tempcell)] = ' ';
			lastgoodcell = tempcell;
		}
	}
	if (!cell) cell = lastgoodcell;
}

void play(int turn) {
	int moves = 0;
	while (!crossCheck() && moves < 9) {
		if (turn == ROBOT) {
			int cell;
			calculate(cell);
			board[x(cell)][y(cell)] = ROBOTMOVE;
			cout << "ROBOT has put an " << ROBOTMOVE << " in cell " << cell << '\n';
			showBoard();
			turn = HUMAN;
		}
		else {
			int cell;
			cin >> cell;
			while (!isValid(cell)) {
				cout << "Outstanding move. We don't do that here, please try again" << '\n';
				cin >> cell;
			}
			board[x(cell)][y(cell)] = HUMANMOVE;
			cout << "HUMAN has put an " << HUMANMOVE << " in cell " << cell << '\n';
			showBoard();
			turn = ROBOT;
		}
		++moves;
	}
	if (crossCheck()) cout << (!turn ? "HUMAN" : "ROBOT") << " has won!" << '\n';
	else cout << "It's a draw!" << '\n';
	system("pause");
}

int main() {
	init();
	string first;
	cout << "Who do you want to start first with? (HUMAN / ROBOT)" << '\n';
	cin >> first;
	showInstructions();
	if (first == "ROBOT") play(ROBOT);
	else play(HUMAN);
}
