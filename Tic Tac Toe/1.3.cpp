#include <bits/stdc++.h>
using namespace std;

// ====================================================================================================== //

constexpr int power[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683};

inline int shr(const int &mask, const int &num){
	return mask / power[num];
}

inline int shl(const int &mask, const int &num){
	return mask * power[num];
}

inline int getBit(const int &mask, const int &pos){
	return shr(mask, pos) % 3;
}

inline void modifyBit(int &mask, const int &pos, const int &val){
	mask -= shl(getBit(mask, pos), pos);
	mask += shl(val, pos);
}

// ====================================================================================================== //

// | 0 | 1 | 2 |
// -------------
// | 3 | 4 | 5 |
// -------------
// | 6 | 7 | 8 |

constexpr int revX[] = {
	2, 1, 0,
	5, 4, 3,
	8, 7, 6
};

constexpr int revY[] = {
	6, 7, 8,
	3, 4, 5,
	0, 1, 2
};

constexpr int clockwise[] = {
	6, 3, 0,
	7, 4, 1,
	8, 5, 2,
};

inline void reflectX(int &mask){
	int temp = mask;
	for(int i = 0; i < 9; ++i){
		modifyBit(mask, i, getBit(temp, revX[i]));
	}
}

inline void reflectY(int &mask){
	int temp = mask;
	for(int i = 0; i < 9; ++i){
		modifyBit(mask, i, getBit(temp, revY[i]));
	}
}

inline void rotateMask(int &mask){
	int temp = mask;
	for(int i = 0; i < 9; ++i){
		modifyBit(mask, i, getBit(temp, clockwise[i]));
	}
}

inline bool colCheck(const int &mask){
	bool res = 0;
	res |= (getBit(mask, 0) && getBit(mask, 0) == getBit(mask, 3) && getBit(mask, 3) == getBit(mask, 6));
	res |= (getBit(mask, 1) && getBit(mask, 1) == getBit(mask, 4) && getBit(mask, 4) == getBit(mask, 7));
	res |= (getBit(mask, 2) && getBit(mask, 2) == getBit(mask, 5) && getBit(mask, 5) == getBit(mask, 8));

	return res;
}

inline bool rowCheck(const int &mask){
	bool res = 0;
	res |= (getBit(mask, 0) && getBit(mask, 0) == getBit(mask, 1) && getBit(mask, 1) == getBit(mask, 2));
	res |= (getBit(mask, 3) && getBit(mask, 3) == getBit(mask, 4) && getBit(mask, 4) == getBit(mask, 5));
	res |= (getBit(mask, 6) && getBit(mask, 6) == getBit(mask, 7) && getBit(mask, 7) == getBit(mask, 8));

	return res;
}

inline bool crossCheck(const int &mask){
	bool res = 0;
	res |= (getBit(mask, 0) && getBit(mask, 0) == getBit(mask, 4) && getBit(mask, 4) == getBit(mask, 8));
	res |= (getBit(mask, 2) && getBit(mask, 2) == getBit(mask, 4) && getBit(mask, 4) == getBit(mask, 6));

	return res;
}

inline bool win(const int &mask){
	return (colCheck(mask) || rowCheck(mask) || crossCheck(mask));
}

inline bool draw(const int &mask){
	bool check = 1;
	for(int i = 0; i < 9; ++i) check &= bool(getBit(mask, i));

	return check;
}

// ====================================================================================================== //

constexpr int X = 1;
constexpr int O = 2;

constexpr int maxn = 19683;
constexpr int inf = INT_MAX / 2;

int dp[3][maxn], trace[3][maxn];

//0 = X win, 1 = draw, 2 = X lose (higher value = worse)
int DP(int turn, int mask){
	//Win
	if(win(mask)) return (turn == X ? 2 : 0);

	//Draw
	if(draw(mask)) return 1;

	int &res = dp[turn][mask];
	int &cell = trace[turn][mask];
	if(cell != -1) return res;

	//Mirror check
	reflectX(mask);
	if(trace[turn][mask] != -1){
		cell = revX[trace[turn][mask]];
		return res = dp[turn][mask];
	}

	reflectY(mask);
	if(trace[turn][mask] != -1){
		cell = revY[revX[trace[turn][mask]]];
		return res = dp[turn][mask];
	}

	reflectX(mask);
	if(trace[turn][mask] != -1){
		cell = revY[trace[turn][mask]];
		return res = dp[turn][mask];
	}
	reflectY(mask);

	//Rotation check
	rotateMask(mask);
	if(trace[turn][mask] != -1){
		cell = clockwise[trace[turn][mask]];
		return res = dp[turn][mask];
	}

	rotateMask(mask);
	if(trace[turn][mask] != -1){
		cell = clockwise[clockwise[trace[turn][mask]]];
		return res = dp[turn][mask];
	}

	rotateMask(mask);
	if(trace[turn][mask] != -1){
		cell = clockwise[clockwise[clockwise[trace[turn][mask]]]];
		return res = dp[turn][mask];
	}

	rotateMask(mask);

	//Dynamic programming part
	if(turn == X) res = 3;
	else res = -1;

	for(int i = 0; i < 9; ++i) if(getBit(mask, i) == 0){
		int new_mask = mask;
		modifyBit(new_mask, i, turn);

		//If X turn then maximize chances of winning (minimize the value)
		if(turn == X){
			int val = DP(O, new_mask);
			if(val < res){
				res = val;
				cell = i;
			}
		}
		//If O turn then minimize chances of winning (maximize the value)
		else{
			int val = DP(X, new_mask);
			if(val > res){
				res = val;
				cell = i;
			}
		}
	}

	return res;
}

void showBoard(const int &mask){
	for(int i = 0; i < 9; ++i){
		int val = getBit(mask, i);
		if(val == 0) cout << ". ";
		if(val == 1) cout << "X ";
		if(val == 2) cout << "O ";

		if(i % 3 == 2) cout << '\n';
	}
	cout << '\n';
}

void welcome(){
	cout << "| 0 | 1 | 2 |\n";
	cout << "-------------\n";
	cout << "| 3 | 4 | 5 |\n";
	cout << "-------------\n";
	cout << "| 6 | 7 | 8 |\n";

	cout << "\nWho do you want to start the game? ('HUMAN' / 'ROBOT')\n";
}

int main(){
	//Initialization
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 19683; ++j) trace[i][j] = -1;

	welcome();
	string choice;
	cin >> choice;

	int mask = 0;
	int turn = (choice == "ROBOT" ? X : O);

	while(!win(mask) && !draw(mask)){
		if(turn == O){
			int cell;
			cin >> cell;

			while(cell < 0 || cell > 8 || getBit(mask, cell) != 0){
				cout << "Invalid move!\n";
				cin >> cell;
			}

			modifyBit(mask, cell, O);
			showBoard(mask);
		}
		else{
			int cur = DP(turn, mask);

			cout << '\n' << trace[turn][mask] << '\n';
			modifyBit(mask, trace[turn][mask], X);
			showBoard(mask);
		}

		if(turn == X) turn = O;
		else turn = X;
	}

	if(win(mask)){
		if(turn == O) cout << "COMPUTER WON THE GAME\n";
		else cout << "HUMAN WON THE GAME\n";
	}
	else cout << "IT'S A DRAW!\n";

	system("pause");
}
