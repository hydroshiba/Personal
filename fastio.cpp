#define _CRT_SECURE_NO_WARNINGS
#define digit(a) trunc(log10(a)) 
#include <bits/stdc++.h>
using namespace std;
typedef long long lol;
void read(lol& ans) {
	int c = getchar();
	bool neg = false;
	if (char(c) == '-') {
		neg = true;
		c = getchar();
	}
	ans = 0;
	while (47 < c && c < 58) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	if (neg) ans = -ans;
}
void write(lol ans) {
	if (ans < 0) putchar('-');
	ans = abs(ans);
	int n = digit(ans), c;
	if (!ans) putchar(48); else for(int i = 0; i <= n; ++i) {
		if (digit(ans) < n - i) putchar(48);
		else {
			c = trunc(ans / pow(10, digit(ans)));
			putchar(c + 48);
			ans -= c * pow(10, digit(ans));
		}
	}
	putchar(' ');
}
int main() {
	lol a, n;
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("fastio.inp", "r", stdin);
	freopen("fastio.out", "w", stdout);
	clock_t begin = clock();
	read(n);
	for (lol i = 1; i <= n; ++i) {
		read(a); 
		write(a);
	}
	clock_t end = clock();
	cerr << "Time run: " << (float)(end - begin) / CLOCKS_PER_SEC << " s" << endl;
	return 0;
}