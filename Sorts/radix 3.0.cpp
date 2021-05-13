#include <bits/stdc++.h>
using namespace std;

///Put your CPU's total data cache size (in bytes) here
const int CACHE = 3145728;

///Support for negative integers isn't added yet, so be aware
template<typename _iterator>
void radix(_iterator _begin, _iterator _end){
	///Setting up
	int bytes = sizeof(*_begin);
	int size = _end - _begin;
	int local_size = min(size, CACHE / bytes);
	bool dynamic = 0, turn = 1;

	using type = typename iterator_traits<__typeof(_iterator)>::value_type;
	type Offset[local_size];
	vector<type> dOffset;
	if(size > local_size){
		dOffset.resize(size - local_size);
		dynamic = 1;
	}


	///Histogram creation
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


	///Pass 1
	if(bucket1[num1] == size);
	else{
		for(int i = 1; i < 512; ++i) bucket1[i] += bucket1[i - 1];

		if(turn) for(auto i = _end - 1; i >= _begin; --i){
			int digit = *i & 511;
			--bucket1[digit];

			if(bucket1[digit] >= local_size)
				*(dOffset.begin() + (bucket1[digit] - local_size)) = *i;
			else *(Offset + bucket1[digit]) = *i;
		}
		else{
			if(dynamic) for(auto i = dOffset.end() - 1; i >= dOffset.begin(); --i){
				int digit = *i & 511;
				--bucket1[digit];
				*(_begin + bucket1[digit]) = *i;
			}

			for(auto i = (Offset + (local_size - 1)); i >= Offset; --i){
				int digit = *i & 511;
				--bucket1[digit];
				*(_begin + bucket1[digit]) = *i;
			}
		}

		turn = !turn;
	}


	///Pass 2
	if(bucket2[num2] == size);
	else{
		for(int i = 1; i < 512; ++i) bucket2[i] += bucket2[i - 1];

		if(turn) for(auto i = _end - 1; i >= _begin; --i){
			int digit = (*i >> 9) & 511;
			--bucket2[digit];

			if(bucket2[digit] >= local_size)
				*(dOffset.begin() + (bucket2[digit] - local_size)) = *i;
			else *(Offset + bucket2[digit]) = *i;
		}
		else{
			if(dynamic) for(auto i = dOffset.end() - 1; i >= dOffset.begin(); --i){
				int digit = (*i >> 9) & 511;
				--bucket2[digit];
				*(_begin + bucket2[digit]) = *i;
			}

			for(auto i = (Offset + (local_size - 1)); i >= Offset; --i){
				int digit = (*i >> 9) & 511;
				--bucket2[digit];
				*(_begin + bucket2[digit]) = *i;
			}
		}

		turn = !turn;
	}


	///Pass 3
	if(bucket3[num3] == size);
	else{
		for(int i = 1; i < 512; ++i) bucket3[i] += bucket3[i - 1];

		if(turn) for(auto i = _end - 1; i >= _begin; --i){
			int digit = (*i >> 18) & 511;
			--bucket3[digit];

			if(bucket3[digit] >= local_size)
				*(dOffset.begin() + (bucket3[digit] - local_size)) = *i;
			else *(Offset + bucket3[digit]) = *i;
		}
		else{
			if(dynamic) for(auto i = dOffset.end() - 1; i >= dOffset.begin(); --i){
				int digit = (*i >> 18) & 511;
				--bucket3[digit];
				*(_begin + bucket3[digit]) = *i;
			}

			for(auto i = (Offset + (local_size - 1)); i >= Offset; --i){
				int digit = (*i >> 18) & 511;
				--bucket3[digit];
				*(_begin + bucket3[digit]) = *i;
			}
		}

		turn = !turn;
	}


	///Pass 4
	if(bucket4[num4] == size);
	else{
		for(int i = 1; i < 512; ++i) bucket4[i] += bucket4[i - 1];

		if(turn) for(auto i = _end - 1; i >= _begin; --i){
			int digit = (*i >> 27) & 511;
			--bucket4[digit];

			if(bucket4[digit] >= local_size)
				*(dOffset.begin() + (bucket4[digit] - local_size)) = *i;
			else *(Offset + bucket4[digit]) = *i;
		}
		else{
			if(dynamic) for(auto i = dOffset.end() - 1; i >= dOffset.begin(); --i){
				int digit = (*i >> 27) & 511;
				--bucket4[digit];
				*(_begin + bucket4[digit]) = *i;
			}

			for(auto i = (Offset + (local_size - 1)); i >= Offset; --i){
				int digit = (*i >> 27) & 511;
				--bucket4[digit];
				*(_begin + bucket4[digit]) = *i;
			}
		}

		turn = !turn;
	}


	///If type is 32-bit then stop
	if(bytes == 4){
		if(!turn) for(auto i = _begin; i < _end; ++i){
			if(i - _begin >= local_size) *i = *(dOffset.begin() + ((i - _begin) - local_size));
			else *i = *(Offset + (i - _begin));
		}
		return;
	}


	///Pass 5
	if(bucket5[num5] == size);
	else{
		for(int i = 1; i < 512; ++i) bucket5[i] += bucket5[i - 1];

		if(turn) for(auto i = _end - 1; i >= _begin; --i){
			int digit = (*i >> 36) & 511;
			--bucket5[digit];

			if(bucket5[digit] >= local_size)
				*(dOffset.begin() + (bucket5[digit] - local_size)) = *i;
			else *(Offset + bucket5[digit]) = *i;
		}
		else{
			if(dynamic) for(auto i = dOffset.end() - 1; i >= dOffset.begin(); --i){
				int digit = (*i >> 36) & 511;
				--bucket5[digit];
				*(_begin + bucket5[digit]) = *i;
			}

			for(auto i = (Offset + (local_size - 1)); i >= Offset; --i){
				int digit = (*i >> 36) & 511;
				--bucket5[digit];
				*(_begin + bucket5[digit]) = *i;
			}
		}

		turn = !turn;
	}


	///Pass 6
	if(bucket6[num6] == size);
	else{
		for(int i = 1; i < 512; ++i) bucket6[i] += bucket6[i - 1];

		if(turn) for(auto i = _end - 1; i >= _begin; --i){
			int digit = (*i >> 45) & 511;
			--bucket6[digit];

			if(bucket6[digit] >= local_size)
				*(dOffset.begin() + (bucket6[digit] - local_size)) = *i;
			else *(Offset + bucket6[digit]) = *i;
		}
		else{
			if(dynamic) for(auto i = dOffset.end() - 1; i >= dOffset.begin(); --i){
				int digit = (*i >> 45) & 511;
				--bucket6[digit];
				*(_begin + bucket6[digit]) = *i;
			}

			for(auto i = (Offset + (local_size - 1)); i >= Offset; --i){
				int digit = (*i >> 45) & 511;
				--bucket6[digit];
				*(_begin + bucket6[digit]) = *i;
			}
		}

		turn = !turn;
	}


	///Pass 7
	if(bucket7[num7] == size);
	else{
		for(int i = 1; i < 512; ++i) bucket7[i] += bucket7[i - 1];

		if(turn) for(auto i = _end - 1; i >= _begin; --i){
			int digit = (*i >> 54) & 511;
			--bucket7[digit];

			if(bucket7[digit] >= local_size)
				*(dOffset.begin() + (bucket7[digit] - local_size)) = *i;
			else *(Offset + bucket7[digit]) = *i;
		}
		else{
			if(dynamic) for(auto i = dOffset.end() - 1; i >= dOffset.begin(); --i){
				int digit = (*i >> 54) & 511;
				--bucket7[digit];
				*(_begin + bucket7[digit]) = *i;
			}

			for(auto i = (Offset + (local_size - 1)); i >= Offset; --i){
				int digit = (*i >> 54) & 511;
				--bucket7[digit];
				*(_begin + bucket7[digit]) = *i;
			}
		}

		turn = !turn;
	}


	///Check if the sorted values are in the helper or the original array
	///If in the helper array then swap
	if(!turn) for(auto i = _begin; i < _end; ++i){
		if(i - _begin >= local_size) *i = *(dOffset.begin() + ((i - _begin) - local_size));
		else *i = *(Offset + (i - _begin));
	}
	return;
}

int main(){
	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	mt19937_64 ran(seed);

	int n;
	cin >> n;
	vector<long long> arr(n);
	for(auto &i : arr) i = ran(), i = abs(i);

	clock_t start = clock();
	radix(arr.begin(), arr.end());
	clock_t finish = clock();
	cout << "Time complete: " << (float)(finish-start)/CLOCKS_PER_SEC << endl;
}
