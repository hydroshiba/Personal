#include <bits/stdc++.h>
using namespace std;

struct segment_tree{
     int n, depth;
     vector<int> tree;
     vector<int> arr;

     int minpos(int i, int j){
        if(arr[i] < arr[j]) return i;
        else return j;
     }

     segment_tree(const vector<int> &vec){
        arr = vec;
        arr.push_back(INT_MAX);

        n = (arr.size() << 1) + 1;
        tree.assign(n, arr.size() - 1);

        for(int i = 0; i < arr.size(); ++i) tree[i + arr.size()] = i;
        for(int i = arr.size() - 1; i > 0; --i)
            tree[i] = minpos(tree[i << 1], tree[(i << 1) + 1]);
     }

     void update(int pos, const int &val){
        arr[pos] = val;
        pos += arr.size();

        for(pos >>= 1; pos > 0; pos >>= 1)
            tree[pos] = minpos(tree[pos << 1], tree[(pos << 1) + 1]);
     }

     int get(int l, int r){
        int ans = l;
        l += arr.size();
        r += arr.size();

        while(l <= r){
            if(l & 1) ans = minpos(ans, tree[l]), ++l;
            if(!(r & 1)) ans = minpos(ans, tree[r]), --r;

            l >>= 1;
            r >>= 1;
        }

        return ans;
     }

     int modified_get(int l, int r){
        if(l == r) return l;
        if(l > r) swap(l, r);

        l += arr.size();
        r += arr.size();
        if(l + 1 == r) return minpos(tree[l], tree[r]);

        int ans = arr.size() - 1;
        if(l & 1) ans = minpos(ans, tree[l]), ++l;
        if(!(r & 1)) ans = minpos(ans, tree[r]), --r;
        if(l + 1 == r) return minpos(ans, minpos(tree[l], tree[r]));

        int sl = l & -l;
        int sr = (~r) & -(~r);

        while(l / sl <= 1) sl >>= 1;
        while(r / sr <= 1) sr >>= 1;
        ans = minpos(ans, minpos(tree[l / sl], tree[r / sr]));

        return ans;
     }
};

void fss(vector<int> &vec){
    segment_tree it(vec);

    for(int i = 0; i < vec.size(); ++i){
        int pos = it.modified_get(i, vec.size() - 1);
        swap(vec[pos], vec[i]);
        it.update(pos, vec[pos]);
        //it.update(i, vec[i]);
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

    for(int &i : arr) i = ran() % 50;

    clock_t start = clock();
    sort(arr.begin(), arr.end());
    clock_t finish = clock();
    cout<<"STD sort: "<<(float)(finish-start)/CLOCKS_PER_SEC<<" s"<<endl;

    random_shuffle(arr.begin(), arr.end());

    start = clock();
    fss(arr);
    finish = clock();
    cout<<"Fast Selection Sort: "<<(float)(finish-start)/CLOCKS_PER_SEC<<" s"<<endl;
    for(int i : arr) cout << i << ' ';

    vector<int> vec = arr;
    sort(vec.begin(), vec.end());
    for(int i = 0; i < n; ++i){
        if(vec[i] != arr[i]) {
            cout << "Wrong at " << i;
            return 0;
        }
    }

    cout << "OK";
}
