#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

vector<int> countBits(int num) {
  vector<int> bit_ct_vec(num+1, 0);
  for (int power_of_2 = 1; power_of_2 <= num; power_of_2 <<= 1) {
    bit_ct_vec[power_of_2] = 1;
    int max_i = min(num + 1, power_of_2 << 1);
    for (int i = power_of_2 + 1; i < max_i; ++i) {
      bit_ct_vec[i] = bit_ct_vec[i-power_of_2] + 1;
    }
  }
  return bit_ct_vec;
}

int main() {
  print(countBits(0));
  print(countBits(1));
  print(countBits(5));
  print(countBits(17));
  return 0;
}
