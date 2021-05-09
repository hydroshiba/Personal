#include <bits/stdc++.h>
using namespace std;

vector<long long> arr;

void radix(vector<long long>::iterator _begin, vector<long long>::iterator _end, int base){
	long long _max = *max_element(_begin, _end);
	_max = max(_max, llabs(*min_element(_begin, _end)));

	vector<unsigned long long> power = {1};
	int loops = 0;

	while(*power.rbegin() < _max){
		power.push_back(*power.rbegin() * (unsigned long long)base);
		++loops;
	}

	--loops;
	for(int pos = 0; pos <= loops; ++pos){
		vector<long long> bucket[base];
		unsigned long long div = power[pos];
		unsigned long long mod = power[pos + 1];

		for(auto it = _begin; it < _end; ++it){
			int digit = (llabs((unsigned long long)*it) % mod) / div;
			bucket[digit].push_back(*it);
		}

		vector<long long>::iterator parser = _begin;
		for(int i = 0; i < base; ++i){
			int k = i;
			if(*_begin < 0) k = base - i - 1;

			for(auto j : bucket[k]){
				*parser = j;
				++parser;
			}
		}
	}
}

void radix(vector<long long>::iterator _begin, vector<long long>::iterator _end){
	///Negative elements handling
	auto left = _begin, right = _end;
	--right;
	while(true){
		while(left < right && *left < 0) ++left;
		while(right >= left && *right > 0) --right;
		if(left >= right) break;

		swap(*left, *right);
		++left;
		--right;
	}

	
	///Base calculation
	long long posi_max = *max_element(_begin, _end);
	long long nega_max = llabs(*min_element(_begin, _end));

	long long ex_posi = 2;
	int dist_posi = _end - left;
	while(pow(posi_max, 1.0 / (double)ex_posi) > min(dist_posi, 20000)) ++ex_posi;
	int base_posi = pow(posi_max, 1.0 / (double)ex_posi) + 1;

	long long ex_nega = 2;
	int dist_nega = ++right - _begin;
	while(pow(nega_max, 1.0 / (double)ex_nega) > min(dist_nega, 20000)) ++ex_nega;
	int base_nega = pow(nega_max, 1.0 / (double)ex_nega) + 1;


	///Overflow protection
	double _maxval = pow(base_posi, ex_posi);
	if(_maxval > (double)LLONG_MAX) base_posi = 512;
	_maxval = pow(base_nega, ex_nega);
	if(_maxval > (double)LLONG_MAX) base_nega = 512;


	///Sort
	auto pivot = _begin;
	while(*pivot < 0) ++pivot;
	radix(_begin, pivot, base_nega);
	radix(pivot, _end, base_posi);
}

int main(){
	ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 ran(seed);

    int n;
    cin >> n;
    arr.resize(n);
    for(auto &i : arr){
		i = ran();
		if(ran() % 2) i = -i;
    }

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
