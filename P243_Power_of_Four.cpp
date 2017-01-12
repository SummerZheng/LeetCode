#include<iostream>
#include<bitset>

using namespace std;

bool isPowerOfFour(int n) {
  const size_t sz = 33;
  bitset<sz> bitNum(n);
  if (bitNum.count() == 1) {
    for (size_t i = 0; i != sz; ++i) {
      if (bitNum[i])
        return i%2? false : true;
    }
  }
  return false;
}

int main() {
  cout<<bitset<32>(0xAAAAAAAA)<<endl;
  cout<<isPowerOfFour(4)<<endl;
  cout<<isPowerOfFour(5)<<endl;
  cout<<isPowerOfFour(16)<<endl;
  cout<<isPowerOfFour(64)<<endl;
  return 0;
}
