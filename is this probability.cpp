#include <bits/stdc++.h>
#include <thread>
using namespace std;

const long long maxthread = 1e11;
double win = 0;

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 mt(seed);

bool play(){
     int num = 1;
     while(true){
          int chance = mt() % 2;
          if(chance) ++num;
          else --num;
          if(num == 6) return 1;
          if(num == 0) return 0;
     }
}

void execute(){
     long long rounds = maxthread / 4;
     while(rounds--){
          if(play()) ++win;
     }
}

int main(){
     thread one(execute);
     thread two(execute);
     thread three(execute);
     thread four(execute);

     one.join();
     two.join();
     three.join();
     four.join();

     cout << (win / double(maxthread));
}
