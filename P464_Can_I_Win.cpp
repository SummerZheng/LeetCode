#include<iostream>
#include<bitset>
#include<string>
#include<unordered_map>
#include"print.h"

using namespace std;

const int sz = 20;

template<size_t sz>
bool canIWin_util(unordered_map<string, bool>& slate, bitset<sz>& available_pool, int total, int maxInt) {
  if (total <= 0)  return false;
  string key = available_pool.to_string();
  if (!slate.count(key)) {
    bool flag = false;
    for (int i = maxInt; i > 0; --i) {
      if (available_pool.test(i-1)) {
        available_pool.reset(i-1);
        flag = !canIWin_util(slate, available_pool, total - i, maxInt);
        available_pool.set(i-1);
        if (flag) {
          break;
        }
      }
    }
    slate.emplace(key, flag);
  }
  return slate[key];
}

bool canIWin(const int maxChoosableInteger, int desiredTotal) {
  if ((1 + maxChoosableInteger) * maxChoosableInteger < desiredTotal) return false;
  if (desiredTotal <= 0) return true;
  bitset<sz> pool;
  pool.set();
  unordered_map<string, bool> slate;
  vector<string> trail;
  return canIWin_util(slate, pool, desiredTotal, maxChoosableInteger);
}

int main() {
  int a = 18, b = 188;
  cout<<"beat total "<<b<<" with max choosable integer "<<a<<endl;
  cout<<canIWin(a, b)<<endl;
  a = 10, b = 11;
  cout<<"beat total "<<b<<" with max choosable integer "<<a<<endl;
  cout<<canIWin(a, b)<<endl;
  a = 10, b = 40;
  cout<<"beat total "<<b<<" with max choosable integer "<<a<<endl;
  cout<<canIWin(a, b)<<endl;
  a = 5, b = 50;
  cout<<"beat total "<<b<<" with max choosable integer "<<a<<endl;
  cout<<canIWin(a, b)<<endl;
  return 0;
}
