#include<iostream>
#include<bitset>

using namespace std;

bool isPowerOfTwo(int n) {
  const size_t sz = 33;
  bitset<sz> bitNum(n);
  cout<<bitNum<<endl;
  cout<<bitNum.to_ulong()<<endl;
  return bitNum.count() == 1;
}

int main() {
  cout<<isPowerOfTwo(-2147483648)<<endl;
  return 0;
}
