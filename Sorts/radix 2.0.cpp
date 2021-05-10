#include <bits/stdc++.h>
using namespace std;

vector<long long> arr;

///The core sorting algorithm
void _radix(vector<long long>::iterator _begin, vector<long long>::iterator _end, int base){
	long long _max = LLONG_MIN;
	for(auto i = _begin; i < _end; ++i) _max = max(_max, llabs(*i));

	int loops = 0;
	vector<unsigned long long> power = {1};
	while(*power.rbegin() < _max){
		power.push_back(*power.rbegin() * (unsigned long long)base);
		++loops;
	}

	--loops;
	int bucket[base];
	vector<long long> helper(_end - _begin);

	for(int pos = 0; pos <= loops; ++pos){
		unsigned long long div = power[pos];
		unsigned long long mod = power[pos + 1];
		memset(bucket, 0, base * sizeof(int));

		for(auto it = _begin; it < _end; ++it){
			int digit = (llabs((unsigned long long)*it) % mod) / div;
			++bucket[digit];
		}

		for(int i = 1; i < base; ++i) bucket[i] += bucket[i - 1];

		vector<long long>::iterator parser = (_end - 1);
		while(parser >= _begin){
			int digit = (llabs((unsigned long long)*parser) % mod) / div;
			int i = bucket[digit] - 1;

			helper[i] = *parser;
			--bucket[digit];
			--parser;
		}

		for(int i = 0; i < (_end - _begin); ++i) *(_begin + i) = dest[i];
	}
}

///Radix sort with auto calculated base
void radix(vector<long long>::iterator _begin, vector<long long>::iterator _end){
	//Base calculation
	long long _max = max(*max_element(_begin, _end), llabs(*min_element(_begin, _end)));
	long long ex = 2;
	int dist = _end - _begin;
	while(pow(_max, 1.0 / (double)ex) > min(max(2, dist), 20000)) ++ex;
	int base = pow(_max, 1.0 / (double)ex) + 1;

	//Overflow protection
	double _maxval = pow(base, ex);
	if(_maxval > (double)LLONG_MAX) base = 512;

	//Sort
	_radix(_begin, _end, base);
}

///Radix sort with specified base
void radix(vector<long long>::iterator _begin, vector<long long>::iterator _end, int base){
	_radix(_begin, _end, base);
}

///Negative elements radix sort
void negative_radix(vector<long long>::iterator _begin, vector<long long>::iterator _end){
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
	for(pivot = right; pivot <= left; ++pivot)
		if(pivot >= _begin && *pivot > 0LL) break;

	//Sort
	radix(_begin, pivot);
	radix(pivot, _end);
}

///Negative elements radix sort with specified base
void negative_radix(vector<long long>::iterator _begin, vector<long long>::iterator _end, int base){
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
	for(pivot = right; pivot <= left; ++pivot)
		if(pivot >= _begin && *pivot > 0LL) break;

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
