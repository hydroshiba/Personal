///hydroshiba

///BEFORE YOU CODE:
///     Switch to C++11 or higher in Compiler options.
///     Turn off "Disable startup scripts" in Debugger options.
///     Adjust appropriate value of maxn and r.
///     Set appropriate task name.

#if __cplusplus >= 201402L
    #define sieve static constexpr Sieve
#else
    #define sieve Sieve
#endif

#define DONLINE_JUDGE
#define task ""
#define flash ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define exact(n) fixed << setprecision(n)

#define top front ///This looks stupid to be honest
#define give push
#define steal pop

#define low lower_bound
#define upp upper_bound
#define x first
#define y second

#include <bits/stdc++.h>
using namespace std;

using lol = long long;
using ii = pair<int, int>;
using ll = pair<long long, long long>;

template<class type> using graph = vector<vector<type>>;

const string yes = "YES";
const string no = "NO";

const int inf = INT_MAX;
const long long inf64 = LLONG_MAX;

const int r = 1e9 + 7;
const double pi = 3.1415926535897932384;
const int maxn = 2e5 + 6;

///Random generator
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937_64 ran(seed);

///64 bit integer type but with ceil division
class int64_c{
public:
    long long num;
    template<class type> int64_c(const type& _num){ num = int(_num); }

    template<class type> int64_c& operator =(const type& _num){
        num = (long long) _num;
        return *this;
    }

    operator int() const{ return num; }
    operator long long() const{ return num; }
    operator float() const{ return num; }
    operator double() const{ return num; }
};

istream& operator >>(istream &inp, int64_c &val){
    inp >> val.num;
    return inp;
}

ostream& operator <<(ostream &out, int64_c &val){
    out << val.num;
    return out;
}

int64_c operator +(const int64_c& a, const int64_c& b){ return a.num + b.num; }
int64_c operator -(const int64_c& a, const int64_c& b){ return a.num - b.num; }
int64_c operator *(const int64_c& a, const int64_c& b){ return a.num * b.num; }
int64_c operator /(const int64_c& a, const int64_c& b){
    return a.num / b.num + bool(a.num % b.num);
}

///0 - indexed segment tree
///Unfortunately it can't use types other than integer
template<class type, type (*func)(type, type), type null>
class segment_tree{
private:
    int _size;
    vector<type> _tree;

public:
    int size;

    segment_tree(int n){
        size = n;
        _size = 1 << int(ceil(log2(size)));
        _tree.assign(_size << 1, null);
    }

    segment_tree(const vector<type> &arr){
        size = arr.size();
        _size = 1 << int(ceil(log2(size)));
        _tree.assign(_size << 1, null);

        for(int i = size - 1; i > -1; --i)
            _tree[i + _size] = arr[i];

        for(int i = _size - 1; i > 0; --i)
            _tree[i] = func(_tree[i << 1], _tree[(i << 1) + 1]);
    }

    type& operator [](int pos){
        return _tree[pos + _size];
    }

    void update(int pos, type val){
        pos += _size;
        _tree[pos] = val;

        for(pos >>= 1; pos > 0; pos >>= 1)
            _tree[pos] = func(_tree[pos << 1], _tree[(pos << 1) + 1]);
    }

    type get(int l, int r){
        l += _size;
        r += _size;
        type ans = null;

        while(l <= r){
            if((l & 1) == 1) ans = func(ans, _tree[l++]);
            if((r & 1) == 0) ans = func(ans, _tree[r--]);
            l >>= 1;
            r >>= 1;
        }

        return ans;
    }
};

///Sieve of Eratosthene
template <int size> struct Sieve {
    bool isPrime[size];
    int prime[size];

    #if __cplusplus >= 201402L
        constexpr Sieve() : isPrime(), prime() {
    #else
        Sieve(){
    #endif
        int pos = 0;

        isPrime[2] = true;
        isPrime[3] = true;
        prime[pos++] = 2;
        prime[pos++] = 3;

        for(int i = 5; i < size; i += 6){
            isPrime[i] = true;
            isPrime[i + 2] = true;
        }

        for(long long i = 5; i < size; i += 6){
            if(isPrime[i]){
                prime[pos++] = i;
                for(long long j = i * i; j < size; j += i * 2) isPrime[j] = false;
            }
            long long x = i + 2;
            if(isPrime[x]){
                prime[pos++] = x;
                for(long long j = x * x; j < size; j += x * 2) isPrime[j] = false;
            }
        }
    }
};

///Square root for integers. If no root is found, 0 is returned
long long sqrt(long long n){
    if(n == 1) return 1;

    long long approx = ceil(sqrt((double)n));
    for(long long i = 0; i < 2; ++i)
        if((approx + i) * (approx + i) == n) return approx + i;

    return 0;
}

///END OF TEMPLATE

void solve(){

}

int main(){
    #ifndef DEBUG
        flash;
        #ifndef DONLINE_JUDGE
            freopen(task".inp", "r", stdin);
            freopen(task".out", "w", stdout);
        #endif
    #endif

    int t;
    cin >> t;

    while(t--) solve();
}

///WHILE YOU CODE:

///     Make sure your algorithm and code is clear and easy to understand.
///     PLEASE, check for the bounds (0, maxn, etc).

///     If you got stuck, don't give up. Expand all of your ideas. Try a different approach also!
///     If you got a WA, don't panic. Try to look for bugs and think. Even rewriting the code helps!
///     If you got a TLE, don't panic either. Try to optimize as much as possible:
///         Use static arrays instead of vectors.
///         PLEASE don't pass large types as a reference, especially arrays.
///         Try to determine if you can apply binary search or not. Do the same thing with prefix sum.
///         Also make sure that you've got flash!
///     Try to brute if you got really stuck, especially with small limits and Div 3 problems.

///     Finally, if you've solved enough problems for a rating increase but still have plenty of time,
///     don't just sit there! Try to solve the next problem, your brain may amazes you!

///HAPPY CODING!
