#include <bits/stdc++.h>
using namespace std;

typedef long long lol;
typedef pair<int, int> ii;
typedef pair<lol, lol> ll;

const int inf = INT_MAX;
const lol inf64 = LLONG_MAX;
const int maxn = 1e3 + 5;
const int mod = 1e9 + 7;

string toString(int a){
     string ans;
     while(a > 0){
          ans = char(a % 10 + 48) + ans;
          a /= 10;
     }
     return ans;
}

bool operator <(string a, string b){
     if(a.size() != b.size()) return(a.size() < b.size());
     for(int i = 0; i < a.size(); ++i)
          if(a[i] - 48 < b[i] - 48) return true;
     return false;
}

string operator +(string a, string b){
     reverse(a.begin(), a.end());
     reverse(b.begin(), b.end());
     if(a.size() < b.size()) swap(a, b);
     string ans;
     bool mem = 0;
     for(int i = 0; i < a.size(); ++i){
          int c = (a[i] - 48) + (i >= b.size() ? 0 : b[i] - 48) + mem;
          if(c > 9) c -= 10, mem = 1; else mem = 0;
          ans = char(c + 48) + ans;
     }
     if(mem) ans = "1" + ans;
     return ans;
}

string operator -(string a, string b){
     if(a < b) swap(a, b);
     reverse(a.begin(), a.end());
     reverse(b.begin(), b.end());
     string ans;
     bool mem = 0; int zero = 0;
     for(int i = 0; i < a.size(); ++i){
          int c = (a[i] - 48) - (i >= b.size() ? 0 : b[i] - 48) - mem;
          if(c < 0) c += 10, mem = 1; else mem = 0;
          if(!c) ++zero;
          ans = char(c + 48) + ans;
     }
     if(zero == ans.size()) return "0";
     return ans;
}

string operator *(string a, lol b){
     if(b == 0) return "0";
     if(b == 1) return a;
     string ans = a;
     lol step = 2;
     while(b >= step){
          ans = ans + ans;
          step *= 2;
     }
     step /= 2;
     cout << step << '\n';
     return ans + (a * (b - step));
}

int main(){
     freopen("bignum.inp", "r", stdin);
	string a; lol b;
	cin >> a >> b;
	cout << a * b;
}
