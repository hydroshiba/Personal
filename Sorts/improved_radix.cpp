#include <bits/stdc++.h>
using namespace std;

vector<long long> arr;

///The core sorting algorithm
void _radix(vector<long long>::iterator _begin, vector<long long>::iterator _end, int base){
	long long _max = *max_element(_begin, _end);
	_max = max(_max, llabs(*min_element(_begin, _end)));

	int loops = 0;
	vector<unsigned long long> power = {1};
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

///Radix sort with auto calculated base
void radix(vector<long long>::iterator _begin, vector<long long>::iterator _end){
	//Swapping all negative values to the front
	//The code will then sort the negative and the positive segments separately
	auto left = _begin, right = _end, pivot = _begin;
	--right;
	while(true){
		while(left < right && *left < 0LL) ++left;
		while(right >= left && *right > 0LL) --right;
		if(left >= right) break;

		swap(*left, *right);
		++left;
		--right;
	}
	for(pivot = right; pivot <= left; ++pivot) if(*pivot > 0LL) break;

	//Base calculation for the positive segment
	long long posi_max = *max_element(_begin, _end);
	long long ex_posi = 2;
	int dist_posi = _end - pivot;
	while(pow(posi_max, 1.0 / (double)ex_posi) > min(max(2, dist_posi), 20000)) ++ex_posi;
	int base_posi = pow(posi_max, 1.0 / (double)ex_posi) + 1;

	//Base calculation for the negative segment
	long long nega_max = llabs(*min_element(_begin, _end));
	long long ex_nega = 2;
	int dist_nega = pivot - _begin;
	while(pow(nega_max, 1.0 / (double)ex_nega) > min(max(2, dist_nega), 20000)) ++ex_nega;
	int base_nega = pow(nega_max, 1.0 / (double)ex_nega) + 1;

	//Overflow protection
	double _maxval = pow(base_posi, ex_posi);
	if(_maxval > (double)LLONG_MAX) base_posi = 512;
	_maxval = pow(base_nega, ex_nega);
	if(_maxval > (double)LLONG_MAX) base_nega = 512;

	//Sort
	_radix(_begin, pivot, base_nega);
	_radix(pivot, _end, base_posi);
}

///Radix sort with specified base
void radix(vector<long long>::iterator _begin, vector<long long>::iterator _end, int base){
	//Negative elements swapping
	auto left = _begin, right = _end, pivot = _begin;
	--right;
	while(true){
		while(left < right && *left < 0LL) ++left;
		while(right >= left && *right > 0LL) --right;
		if(left >= right) break;

		swap(*left, *right);
		++left;
		--right;
	}
	for(pivot = right; pivot <= left; ++pivot) if(*pivot > 0LL) break;

	//Sort
	_radix(_begin, pivot, base);
	_radix(pivot, _end, base);
}

int main(){
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
	cout<<"Radix auto base: " << (float)(finish-start)/CLOCKS_PER_SEC << " s" << endl;

	vec = arr;
	start = clock();
	radix(vec.begin(), vec.end(), 512);
	finish = clock();
	cout<<"Radix base 512: " << (float)(finish-start)/CLOCKS_PER_SEC << " s" << endl;

	vec = arr;
	start = clock();
	sort(vec.begin(), vec.end());
	finish = clock();
	cout<<"STD Sort: " << (float)(finish-start)/CLOCKS_PER_SEC << " s" << endl;
}
