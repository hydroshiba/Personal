#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;
vector<string> students; vector<int> points;

int columns(int n) {
	if (n % 4) return max(sqrt(n), n / 4 + 1);
	else return max(sqrt(n), n / 4);
}

void goToXY(int a, int b) {
	COORD coord;
	coord.X = a;
	coord.Y = b;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool getName(ifstream& file, string& s) {
	s = "";
	char c;
	file.get(c);
	while (c != 10 && c >= 0) {
		s.push_back(c);
		file.get(c);
	}
	return s.size();
}

void readList() {
	ifstream listFile;
	listFile.open("list.txt");
	string name;
	while (getName(listFile, name)) students.push_back(name);
	listFile.close();
}

void displayList() {
	int x = 0, y = 0, maxcolumn = 0;
	for (int i = 0; i < students.size(); ++i) {
		goToXY(x, y);
		cout << i + 1 << ". " << students[i] << '\n';
		maxcolumn = max(maxcolumn, students[i].size());
		++y;
		if ((i + 1) % columns(students.size()) == 0) {
			x += maxcolumn + 10;
			y = 0;
			maxcolumn = 0;
		}
	}
	goToXY(0, columns(students.size()) + 1);
}

void readData(string subject) {
	ifstream data;
	data.open("subjects/" + subject + ".txt");
	int point;
	while (data >> point) points.push_back(point);
	if (points.empty()) for (int i = 0; i < students.size(); ++i) points.push_back(0);
	data.close();
}

void saveData(string subject) {
	ofstream data;
	data.open("subjects/" + subject + ".txt");
	for (int i : points) data << i << ' ';
	data.close();
}

int main() {
	readList();
	displayList();
	string subject;
	cout << "Enter subject: ";
	cin >> subject;
	readData(subject);
	cout << '\n';
	while (true) {
		int studentID, value;
		cin >> studentID;
		if (!studentID) break;
		cin >> value;
		if (!value) cout << "Current points: " << points[studentID - 1] << '\n'; 
		else points[studentID - 1] += value;
	}
	saveData(subject);
}
