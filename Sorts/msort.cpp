#include <bits/stdc++.h>
using namespace std;

long long fastpow(long long base, long long expo){
	long long ans = 1;
	long long temp = expo;
	int i = 0;

	while(temp >>= 1) ++i;

	for(i; i > -1; --i){
		ans *= ans;
		if((expo >> i) & 1) ans *= base;
	}

	return ans;
}

void msort(vector<int>::iterator _begin, vector<int>::iterator _end){
	if(_begin == _end) return;
	vector<int> bucket[10];

	int depth = 0;
	int allmin = INT_MAX;
	for(auto it = _begin; it < _end; ++it){
		depth = max(depth, *it);
		allmin = min(allmin, *it);
	}

	if(depth == allmin) return;
	depth = fastpow(10, (int)log10(depth));

	int _max, _min;
	do{
		_max = INT_MIN;
		_min = INT_MAX;
		for(auto it = _begin; it < _end; ++it){
			int temp = *it;
			temp %= depth * 10;
			_max = max(_max, temp / depth);
			_min = min(_min, temp / depth);
		}

		depth /= 10;
	}
	while(_max == _min);

	depth *= 10;
	for(auto it = _begin; it < _end; ++it){
		int digit = *it;
		digit %= (depth ? depth * 10 : 10);
		digit /= (depth ? depth : 1);

		bucket[digit].emplace_back(*it);
	}

	vector<int>::iterator parser = _begin;

	for(int i = 0; i < 10; ++i){
		msort(bucket[i].begin(), bucket[i].end());
		for(int j : bucket[i]) *parser = j, ++parser;
	}
}

void sort_by_log(vector<int>::iterator _begin, vector<int>::iterator _end){
	vector<int> bucket[10];

	for(auto it = _begin; it < _end; ++it){
		int digit = log10(*it);
		if(*it == 0) digit = 0;
		bucket[digit].emplace_back(*it);
	}

	vector<int>::iterator parser = _begin;

	for(int i = 0; i < 10; ++i){
		msort(bucket[i].begin(), bucket[i].end());
		for(int j : bucket[i]) *parser = j, ++parser;
	}
}

int main(){
	ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 ran(seed);

    int n;
    cin >> n;
    vector<int> arr(n);

    for(int &i : arr) i = ran() % 100000000;
    vector<int> vec = arr;

    clock_t start = clock();
    sort(arr.begin(), arr.end());
    clock_t finish = clock();
    cout<<"STD sort: "<<(float)(finish-start)/CLOCKS_PER_SEC<<" s"<<endl;

    start = clock();
    sort_by_log(vec.begin(), vec.end());
    finish = clock();
    cout<<"M Sort: "<<(float)(finish-start)/CLOCKS_PER_SEC<<" s"<<endl;

    for(int i = 0; i < n; ++i){
        if(vec[i] != arr[i]) {
            cout << "Wrong at " << i;
            return 0;
        }
    }

    cout << "OK";
}
