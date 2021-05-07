#include <bits/stdc++.h>
using namespace std;

void radix(vector<long long>::iterator _begin, vector<long long>::iterator _end, int base){
	long long _max = *max_element(_begin, _end);

	vector<long long> power = {1};
	int loops = 0;

	while(*power.rbegin() < _max){
		power.push_back(*power.rbegin() * (long long)base);
		++loops;
	}

	--loops;
	for(int pos = 0; pos <= loops; ++pos){
		vector<long long> bucket[base];
		long long div = power[pos];
		long long mod = power[pos + 1];

		for(auto it = _begin; it < _end; ++it){
			int digit = (*it % mod)	/ div;
			bucket[digit].push_back(*it);
		}

		vector<long long>::iterator parser = _begin;
		for(int i = 0; i < base; ++i){
			for(auto j : bucket[i]){
				*parser = j;
				++parser;
			}
		}
	}
}

void radix(vector<long long>::iterator _begin, vector<long long>::iterator _end){
	long long _max = *max_element(_begin, _end);
	long long ex = 2;

	while(pow(_max, 1.0 / (double)ex) > 20000)
		++ex;
	int base = pow(_max, 1.0 / (double)ex) + 1;

	radix(_begin, _end, base);
}

int main(){
	ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 ran(seed);

    int n;
    cin >> n;
    vector<long long> arr(n);

    for(auto &i : arr) i = ran();

	vector<long long> vec = arr;
	clock_t start = clock();
	radix(vec.begin(), vec.end());
	clock_t finish = clock();
	cout<<"Radix auto base" << ": " << (float)(finish-start)/CLOCKS_PER_SEC<<" s"<<endl;

	vec = arr;
	start = clock();
	radix(vec.begin(), vec.end(), 512);
	finish = clock();
	cout<<"Radix base 512" << ": " << (float)(finish-start)/CLOCKS_PER_SEC<<" s"<<endl;

	vec = arr;
	start = clock();
	sort(vec.begin(), vec.end());
	finish = clock();
	cout<<"STD Sort" << ": " << (float)(finish-start)/CLOCKS_PER_SEC<<" s"<<endl;
}
