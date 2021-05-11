#include <bits/stdc++.h>
using namespace std;

vector<int> arr = {0, 3, 1000000, 5, 7, 214748367, 4, 6, 2, 8};
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 ran(seed);

template<typename _iterator>
void radix(_iterator _begin, _iterator _end){
	//Setting up
	int bytes = sizeof(*_begin);
	int size = _end - _begin;
	bool dynamic = 0, turn = 1;

	using type = typename iterator_traits<__typeof(_iterator)>::value_type;
	vector<type> dOffset;
	type *sOffset;

	if(size * bytes < 1048576) sOffset = new type[size]{1, 2, 3, 4, 5};
	else{
		dynamic = 1;
		dOffset.resize(size);
	}


	//Histogram creation
	int bucket1[512] = {0};
	int bucket2[512] = {0};
	int bucket3[512] = {0};
	int bucket4[512] = {0};
	int bucket5[512] = {0};
	int bucket6[512] = {0};
	int bucket7[512] = {0};

	int num1 = (*_begin & 511);
	int num2 = (*_begin >> 9) & 511;
	int num3 = (*_begin >> 18) & 511;
	int num4 = (*_begin >> 27) & 511;
	int num5 = (*_begin >> 36) & 511;
	int num6 = (*_begin >> 45) & 511;
	int num7 = (*_begin >> 54) & 511;

	for(auto i = _begin; i < _end; ++i){
		++bucket1[*i & 511];
		++bucket2[(*i >> 9) & 511];
		++bucket3[(*i >> 18) & 511];
		++bucket4[(*i >> 27) & 511];

		if(bytes > 4){
			++bucket5[(*i >> 36) & 511];
			++bucket6[(*i >> 45) & 511];
			++bucket7[(*i >> 54) & 511];
		}
	}


	//Pass 1
	if(bucket1[num1] == size);
	else{
		for(int i = 1; i < 512; ++i) bucket1[i] += bucket1[i - 1];

		if(turn) for(auto i = _end - 1; i >= _begin; --i){
			int digit = *i & 511;
			--bucket1[digit];

			if(dynamic) dOffset[bucket1[digit]] = *i;
			else *(sOffset + bucket1[digit]) = *i;
		}
		else{
			if(dynamic) for(auto i = dOffset.end() - 1; i >= dOffset.begin(); --i){
				int digit = *i & 511;
				--bucket1[digit];
				*(_begin + bucket1[digit]) = *i;
			}
			else for(auto i = (sOffset + (size - 1)); i >= sOffset; --i){
				int digit = *i & 511;
				--bucket1[digit];
				*(_begin + bucket1[digit]) = *i;
			}
		}

		turn = !turn;
	}


	//Pass 2
	if(bucket2[num2] == size);
	else{
		for(int i = 1; i < 512; ++i) bucket2[i] += bucket2[i - 1];

		if(turn) for(auto i = _end - 1; i >= _begin; --i){
			int digit = (*i >> 9) & 511;
			--bucket2[digit];

			if(dynamic) dOffset[bucket2[digit]] = *i;
			else *(sOffset + bucket2[digit]) = *i;
		}
		else{
			if(dynamic) for(auto i = dOffset.end() - 1; i >= dOffset.begin(); --i){
				int digit = (*i >> 9) & 511;
				--bucket2[digit];
				*(_begin + bucket2[digit]) = *i;
			}
			else for(auto i = (sOffset + (size - 1)); i >= sOffset; --i){
				int digit = (*i >> 9) & 511;
				--bucket2[digit];
				*(_begin + bucket2[digit]) = *i;
			}
		}

		turn = !turn;
	}


	//Pass 3
	if(bucket3[num3] == size);
	else{
		for(int i = 1; i < 512; ++i) bucket3[i] += bucket3[i - 1];

		if(turn) for(auto i = _end - 1; i >= _begin; --i){
			int digit = (*i >> 18) & 511;
			--bucket3[digit];

			if(dynamic) dOffset[bucket3[digit]] = *i;
			else *(sOffset + bucket3[digit]) = *i;
		}
		else{
			if(dynamic) for(auto i = dOffset.end() - 1; i >= dOffset.begin(); --i){
				int digit = (*i >> 18) & 511;
				--bucket3[digit];
				*(_begin + bucket3[digit]) = *i;
			}
			else for(auto i = (sOffset + (size - 1)); i >= sOffset; --i){
				int digit = (*i >> 18) & 511;
				--bucket3[digit];
				*(_begin + bucket3[digit]) = *i;
			}
		}

		turn = !turn;
	}


	//Pass 4
	if(bucket4[num4] == size);
	else{
		for(int i = 1; i < 512; ++i) bucket4[i] += bucket4[i - 1];

		if(turn) for(auto i = _end - 1; i >= _begin; --i){
			int digit = (*i >> 27) & 511;
			--bucket4[digit];

			if(dynamic) dOffset[bucket4[digit]] = *i;
			else *(sOffset + bucket4[digit]) = *i;
		}
		else{
			if(dynamic) for(auto i = dOffset.end() - 1; i >= dOffset.begin(); --i){
				int digit = (*i >> 27) & 511;
				--bucket4[digit];
				*(_begin + bucket4[digit]) = *i;
			}
			else for(auto i = (sOffset + (size - 1)); i >= sOffset; --i){
				int digit = (*i >> 27) & 511;
				--bucket4[digit];
				*(_begin + bucket4[digit]) = *i;
			}
		}

		turn = !turn;
	}


	//If type is 32-bit then stop
	if(bytes = 4){
		if(!turn) for(auto i = _begin; i < _end; ++i){
			if(dynamic) *i = dOffset[(i - _begin)];
			else *i = *(sOffset + (i - _begin));
		}
		if(!dynamic) delete sOffset;

		return;
	}
}

int main(){
	int n;
    cin >> n;
    arr.resize(n);
	for(auto &i : arr) i = ran() % 1000000000, i = abs(i);

	clock_t start = clock();
	radix(arr.begin(), arr.end());
	clock_t finish = clock();
	cout << (float)(finish-start)/CLOCKS_PER_SEC;
}
