#include<iostream>
#include<bitset>

using namespace std;

uint32_t reverseBits(uint32_t n) {
  const size_t bits = 32;
  bitset<bits> bitNum(n);
  for (size_t i = 0; i != bits / 2; ++i) {
    if (bitNum[i] != bitNum[bits - 1 - i]) {
      bitNum.flip(i); bitNum.flip(bits - 1 -i);
    }
  }
  return bitNum.to_ulong();
}

int main() {
  cout<<reverseBits(43261596)<<endl;
  return 0;
}
