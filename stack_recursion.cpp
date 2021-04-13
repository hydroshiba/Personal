#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e7 + 5;
int f[maxn], source[maxn];

int F(int n) {
	stack<int> r;
	memset(f, 255, n * 8);
	f[0] = 0; f[1] = 1; f[2] = 2;
	r.push(n);
	while (true) {
		while (!r.empty() && f[r.top()] > -1) {
			int temp = r.top();
			r.pop();
			if (!r.empty() && r.top() == source[temp]) {
				int temp2 = r.top();
				for (int i = 1; i <= 3; ++i) if (f[temp2 - i] < 0) {
					r.push(temp2 - i);
					source[temp2 - i] = temp;
					break;
				}
				f[temp2] = (f[temp2 - 1] + f[temp2 - 2] + f[temp2 - 3]);
			}
		}
		if (r.empty()) break;
		int num = r.top();
		for (int i = 1; i <= 3; ++i) {
			r.push(num - i);
			source[num - i] = num;
		}
	}
	return f[n];
}

int nonStackF(int n) {
	//if (f[n]) return f[n];
	if (!n) return 0;
	if (n < 3) return 1;
	return (F(n - 2) % 10 + nonStackF(n - 1) % 10) % 10;
}

int main() {
	int n;
	cin >> n;
	//memset(f, 0, n * 4 + 1);
	//f[0] = 0; f[1] = 1; f[2] = 1; f[100] = 1;
	cout << F(n) << '\n';
	for (int i = 0; i <= n; ++i) cout << f[i] << ' ';
}