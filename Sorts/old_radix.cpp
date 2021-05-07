#define _CRT_SECURE_NO_WARNINGS
#define digit(a) trunc(log10(a))
#define tron(a) int(trunc(a))
#include <bits/stdc++.h>
using namespace std;
typedef long long lol;
const int maxn = 1e6;
int a[maxn];
void radix(int begin, int end) {
	int m = 0;
	for (int i = begin; i <= end; ++i) {
		m = max(a[i], m);
	}
	int n = tron(log10(m)) + 1, r[10][maxn / 100], c[10] = { 0 };
	for (int temp = 1; temp <= n; ++temp) {
		for (int i = begin; i <= end; ++i) {
			int digit = (a[i] % tron(pow(10, temp))) - (a[i] % tron(pow(10, temp - 1)));
			digit = digit / tron(pow(10, temp - 1));
			r[digit][c[digit]] = a[i];
			++c[digit];
		}
		for (int i = begin; i <= end; ++i) {
			for (int j = 0; j < 10; ++j) {
				for (int k = 0; k < c[j]; ++k) {
					a[i] = r[j][k];
					++i;
				}
				c[j] = 0;
			}
		}
	}
}
void read(int& ans) {
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
void write(int ans) {
	if (ans < 0) putchar('-');
	ans = abs(ans);
	int n = digit(ans), c;
	if (!ans) putchar(48); else for (int i = 0; i <= n; ++i) {
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
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("sort.inp", "r", stdin);
	freopen("sort.out", "w", stdout);
	int n, i;
	read(n);
	for (int i = 0; i < n; ++i) {
		read(a[i]);
	}
	clock_t time = clock();
	radix(0, n - 1);
	cerr << setprecision(10) << float(clock() - time) / CLOCKS_PER_SEC << '\n';
	time = clock();
	sort(a, a + n);
	cerr << setprecision(10) << float(clock() - time) / CLOCKS_PER_SEC;
	for (int i = 0; i < n; ++i) {
		cout << a[i] << ' ';
	}
}