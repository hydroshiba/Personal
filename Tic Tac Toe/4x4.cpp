#include <bits/stdc++.h>
using namespace std;

// ====================================================================================================== //

constexpr int power[] = {1, 3, 9, 27,
					 81, 243, 729, 2187,
					 6561, 19683, 59049, 177147,
					 531441, 1594323, 4782969, 14348907,
					 43046721};

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

// | 0 | 1 | 2 | 3 |
// -----------------
// | 4 | 5 | 6 | 7 |
// -----------------
// | 8 | 9 | 10| 11|
// -----------------
// | 12| 13| 14| 15|

constexpr int clockwise[] = {
	12, 8, 4, 0,
	13, 9, 5, 1,
	14, 10, 6, 2,
	15, 11, 7, 3
};

constexpr int revX[] = {
	3, 2, 1, 0,
	7, 6, 5, 4,
	11, 10, 9, 8,
	15, 14, 13, 12
};

constexpr int revY[] = {
	12, 13, 14, 15,
	8, 9, 10, 11,
	4, 5, 6, 7,
	0, 1, 2, 3
};

inline void reflectX(int &mask){
	int temp = mask;
	for(int i = 0; i < 16; ++i){
		modifyBit(mask, i, getBit(temp, revX[i]));
	}
}

inline void reflectY(int &mask){
	int temp = mask;
	for(int i = 0; i < 16; ++i){
		modifyBit(mask, i, getBit(temp, revY[i]));
	}
}

inline void rotateMask(int &mask){
	int temp = mask;
	for(int i = 0; i < 16; ++i){
		modifyBit(mask, i, getBit(temp, clockwise[i]));
	}
}

inline bool check(const int &mask, const vector<int> &vec){
	bool res = bool(getBit(mask, *vec.begin()));
	for(int i = 1; i < vec.size(); ++i) res &= (getBit(mask, vec[i]) == getBit(mask, vec[i - 1]));
	return res;
}

inline bool colCheck(const int &mask){
	bool res = 0;
	for(int i = 0; i < 4; ++i) res |= check(mask, {i, i + 4, i + 8, i + 12});
	return res;
}

inline bool rowCheck(const int &mask){
	bool res = 0;
	for(int i = 0; i < 16; i += 4) res |= check(mask, {i, i + 1, i + 2, i + 3});
	return res;
}

inline bool crossCheck(const int &mask){
	bool res = 0;
	res |= check(mask, {0, 5, 10, 15});
	res |= check(mask, {3, 6, 9, 12});
	return res;
}

inline bool win(const int &mask){
	return (colCheck(mask) || rowCheck(mask) || crossCheck(mask));
}

inline bool draw(const int &mask){
	bool check = 1;
	for(int i = 0; i < 16; ++i) check &= bool(getBit(mask, i));

	return check;
}

// ====================================================================================================== //

constexpr int X = 1;
constexpr int O = 2;

constexpr int maxn = 43046721;
constexpr int inf = INT_MAX / 2;

int dp[3][maxn], trace[3][maxn];

//0 = X win, 1 = draw, 2 = X lose (higher value = worse)
int DP(int turn, int mask, int alpha = -inf, int beta = inf){
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

	for(int i = 0; i < 16; ++i) if(getBit(mask, i) == 0){
		int new_mask = mask;
		modifyBit(new_mask, i, turn);

		//If X turn then maximize chances of winning (minimize the value)
		if(turn == X){
			int val = DP(O, new_mask, alpha, beta);
			if(val < res){
				res = val;
				cell = i;
			}

			//Alpha - Beta pruning
			if(res <= alpha) return res;
			beta = min(beta, val);
			if(res == 0) return res;
		}
		//If O turn then minimize chances of winning (maximize the value)
		else{
			int val = DP(X, new_mask, alpha, beta);
			if(val > res){
				res = val;
				cell = i;
			}

			//Alpha - Beta pruning
			if(res >= beta) return res;
			alpha = max(alpha, res);
			if(res == 2) return res;
		}
	}

	return res;
}

void showBoard(const int &mask){
	for(int i = 0; i < 16; ++i){
		int val = getBit(mask, i);
		if(val == 0) cout << ". ";
		if(val == 1) cout << "X ";
		if(val == 2) cout << "O ";

		if(i % 4 == 3) cout << '\n';
	}
	cout << '\n';
}

void welcome(){
	cout << "| 0 | 1 | 2 | 3 |\n";
	cout << "-----------------\n";
	cout << "| 4 | 5 | 6 | 7 |\n";
	cout << "-----------------\n";
	cout << "| 8 | 9 | 10| 11|\n";
	cout << "-----------------\n";
	cout << "| 12| 13| 14| 15|\n";

	cout << "\nWho do you want to start the game? ('HUMAN' / 'ROBOT')\n";
}

int main(){
	//Initialization
	for(int i = 1; i < 3; ++i)
		for(int j = 0; j < maxn; ++j) trace[i][j] = -1;

	welcome();
	string choice;
	cin >> choice;

	int mask = 0;
	int turn = (choice == "ROBOT" ? X : O);

	while(!win(mask) && !draw(mask)){
		if(turn == O){
			int cell;
			cin >> cell;

			while(cell < 0 || cell > 15 || getBit(mask, cell) != 0){
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
