/*
	PROPERTY OF MARK PHAN - 10CTin OF GIA DINH HIGHSCHOOL
	THE GOTOXY PROCEDURE (LINE 86) BELONGS TO USER "RON" ON STACK OVERFLOW
		AUTHOR'S PAGE ON STACK OVERFLOW: https://stackoverflow.com/users/8751754/ron
		WHERE THIS PROCEDURE CAN BE FOUND: 
		https://stackoverflow.com/questions/1670891/how-can-i-print-a-string-to-the-console-at-specific-coordinates-in-c
	THIS PROGRAM WAS COMPLETED ON 30/12/2019
	HAPPY BIRTHDAY!
*/

#pragma warning(disable : 4996)

#define _CRT_SECURE_NO_WARNINGS
#define north 1
#define south 2
#define east 3
#define west 4
#define x first
#define y second

#include <Windows.h>
#include <iostream>
#include <chrono>
#include <queue>

using namespace std;
typedef pair<int, int> ii;

const int mapsize = 20;
const int width = (mapsize * 4) - 1;
const int height = mapsize;
char wall = '^', diff = 'E', body = 'o', food = '$', showStats = 'N';
char map[1000][1000];
int record, score = 0, direction = north;
float sleep;
bool esc = false, pref_from_keyboard = false;
queue<ii> snake;
ii coordinate = ii(width / 2, height / 2);

void loadFiles() {
	freopen("preferences.txt", "r", stdin);
	cin >> wall;
	cin >> diff;
	cin >> body;
	cin >> showStats;
	freopen("highscores.txt", "r", stdin);
	cin >> record;
}

void init() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int i = 1; i <= width; ++i) {
		putchar((i % 2 != 0) ? wall : ' ');
		map[i][1] = ((i % 2 != 0) ? wall : ' ');
		_sleep(0);
	}
	putchar('\n');
	for (int i = 1; i <= height - 2; ++i) {
		putchar(wall);
		map[1][i + 1] = wall;
		for (int j = 1; j <= width - 2; ++j) {
			putchar(' ');
			map[1][i + 1] = ' ';
		}
		putchar(wall);
		map[1][i + 1] = wall;
		putchar('\n');
		_sleep(60);
	}
	for (int i = 1; i <= width; ++i) {
		putchar((i % 2 != 0) ? wall : ' ');
		map[i][height] = ((i % 2 != 0) ? wall : ' ');
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
}

void saveFiles() {
	freopen("preferences.txt", "w", stdout);
	cout << wall << '\n' << diff << '\n' << body << '\n' << showStats;
	if (score > record) {
		freopen("highscores.txt", "w", stdout);
		cout << score;
	}
}

void goToXY(int a, int b) {
	COORD coord;
	coord.X = a;
	coord.Y = b;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void putPixel(ii pos, char c) {
	goToXY(pos.x, pos.y);
	putchar(c);
	map[pos.x][pos.y] = c;
}

void makeFood() {
	int a = rand() % (width - 2) + 1;
	int b = rand() % (height - 2) + 1;
	while (map[a][b] == body || map[a][b] == wall || a % 2 == 0) {
		a = rand() % (width - 2) + 1;
		b = rand() % (height - 2) + 1;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (score > 0 ? (score - 1) % 14 + 1 : 15));
	putPixel(ii(a, b), food);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
}

void drawSnake() {
	snake.push(coordinate);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), score % 14 + 1);
	putPixel(snake.front(), ' ');
	snake.pop();
	putPixel(coordinate, body);
}

void writeStats() {
	goToXY(1, height + 1);
	cout << "                                                                    " << '\n';
	cout << "                                                                    ";
	goToXY(1, height);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Speed: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), score % 14 + 1);
	cout << fixed << (diff == 'E' ? 0.5 : 51 - sleep) << '\n';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " Score: ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), score % 14 + 1);
	cout << score;
}

void pause() {
	goToXY(1, height);
	cout << "                    ";
	goToXY(1, height + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "  Press ENTER to continue, ESC to exit (YOUR GAME WILL NOT BE SAVED)";
	_sleep(100);
	while (true) {
		if (GetAsyncKeyState(VK_RETURN)) break;
		else if (GetAsyncKeyState(VK_ESCAPE)) {
			esc = true;
			goToXY(2, height + 1);
			cout << "                                                                  ";
			return;
		}
	}
	if (showStats - 78) writeStats();
}

void getKey() {
	if (GetAsyncKeyState(VK_UP) && direction != south) direction = north;
	else if (GetAsyncKeyState(VK_DOWN) && direction != north) direction = south;
	else if (GetAsyncKeyState(VK_LEFT) && direction != west) direction = east;
	else if (GetAsyncKeyState(VK_RIGHT) && direction != east) direction = west;
	else if (GetAsyncKeyState(VK_ESCAPE)) pause();
}

void locate() {
	if (direction == north) --coordinate.y;
	if (direction == west) coordinate.x += 2;
	if (direction == south) ++coordinate.y;
	if (direction == east) coordinate.x -= 2;
	if (coordinate.x == -1) coordinate.x = width - 2;
	else if (coordinate.x == width) coordinate.x = 1;
	else if (coordinate.y == 0) coordinate.y = height - 2;
	else if (coordinate.y == height - 1) coordinate.y = 1;
}

void gameOver() {
	goToXY((width - 15) / 2, height + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "Game over!                               ";
	int color = (score > record ? score % 14 + 1 : 15);
	string end = (score > record ? "NEW HIGHSCORE: " : "Your score is: ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	goToXY((width - 21) / 2, height + 2);
	cout << end << score << '\n';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	goToXY((width - 26) / 2, height + 3);
	cout << "Press ENTER to continue";
	while (!GetAsyncKeyState(VK_RETURN));
}

void control() {
	makeFood();
	snake.push(coordinate);
	if (diff == 'E') sleep = 75; else sleep = 50;
	if (showStats - 78) writeStats();
	while (true) {
		drawSnake();
		getKey();
		if (esc) break;
		locate();
		if (map[coordinate.x][coordinate.y] == body) break;
		if (map[coordinate.x][coordinate.y] == food) {
			++score;
			makeFood();
			sleep /= (diff == 'H' ? 1.007 : 1);
			if (showStats - 78) writeStats();
			snake.push(coordinate);
		}
		_sleep(sleep);
	}
	gameOver();
}

void pref() {
	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Enter the character you want to display for the wall:" << '\n';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cin >> wall;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Enter the character you want to display for the snake's body" << '\n';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cin >> body;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Enter the difficulty of the game that you want to play:" << '\n';
	cout << "E for Easy (speed is slow), M for Medium (speed is faster), H for Hard (speed increases over time)" << '\n';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cin >> diff;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Do you want to show statistics? (Y / N for Yes / No)" << '\n';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cin >> showStats;
	pref_from_keyboard = true;
}

void welcomeScreen() {
	system("CLS");
	cout << "                                     WELCOME TO " << '\n';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "                         SSS   N   N      A      K   K  EEEEE" << '\n';
	cout << "                        S      NN  N     A A     K  K   E" << '\n';
	cout << "                         SSS   N N N    A   A    KK     EEEEE" << '\n';
	cout << "                            S  N  NN   A A A A   K  K   E" << '\n';
	cout << "                        SSSS   N   N  A       A  K   K  EEEEE" << '\n';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Press ENTER to play, ESC to exit, F3 to change preferences, F11 to enter / exit fullscreen";
	while (true) {
		if (GetAsyncKeyState(VK_RETURN)) {
			break;
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			return;
		}
		if (GetAsyncKeyState(VK_F3)) {
			pref();
		}
	}
	system("CLS");
	if (!pref_from_keyboard) loadFiles();
	init();
	control();
}

int main() {
	srand(time(NULL));
	welcomeScreen();
	saveFiles();
}
