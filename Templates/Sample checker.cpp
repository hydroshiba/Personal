#include <bits/stdc++.h>
#define taskname "" // Enter the name of the task between the double quotation marks
using namespace std;
typedef char directory[1000];

void OpenFlie(ifstream& file, string s) {
	file.open(s);
}

int main() {
	directory inpDir, outDir, ansDir;
	fgets(inpDir, 1000, stdin); 
	inpDir[strlen(inpDir) - 1] = 0;
	fgets(outDir, 1000, stdin); 
	outDir[strlen(outDir) - 1] = 0;
	strcpy_s(ansDir, inpDir);

	strcat_s(inpDir, taskname".inp"); // Input directory
	strcat_s(outDir, taskname".out"); // Output directory
	strcat_s(ansDir, taskname".ans"); // Jury's answer directory
	ifstream inp, out, ans;

	OpenFlie(inp, inpDir);
	OpenFlie(out, outDir);
	OpenFlie(ans, ansDir);

	int inpVal, outVal, ansVal;
	inp >> inpVal; // Read the value of the input
	out >> outVal; // Read the value of the contestant's output
	ans >> ansVal; // Read the value of the jury's answer

	int point = 0;
	// Write the checker's logic from here

	cout << point;

	inp.close();
	out.close();
	ans.close();
}