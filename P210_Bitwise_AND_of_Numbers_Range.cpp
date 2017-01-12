#include<iostream>
#include<vector>
#include<bitset>

using namespace std;

// int rangeBitwiseAnd(int m, int n) {
//   const int bits = 32;
//   bitset<bits> bitNum1(m);
//   bitset<bits> bitNum2(n);
//   bitset<bits> bitAnd(n);
//   int i = bits;
//   while ( i >= 0 && bitNum1[i] == bitNum2[i] ) {
//     bitAnd[i] = bitNum1[i];
//     --i;
//   }
//   while ( i >= 0) {
//     bitAnd[i--] = 0;
//   } 
//   return bitAnd.to_ulong();
// }

int rangeBitwiseAnd(int m, int n) {
  int shift_digits = 0;
  while (m != n) {
    m >>= 1; n >>= 1;
    ++shift_digits;
  }
  return m<<shift_digits;
}

int main() {
  cout<<rangeBitwiseAnd(5, 7)<<endl;
  cout<<rangeBitwiseAnd(7, 7)<<endl;
  return 0;
}
