#include<iostream>

using namespace std;

int missingNumber(vector<int>& nums) {
  int Xor_indicator = nums.size();
  for (int i = 0; i!= nums.size(); ++i) {
    Xor_indicator ^= nums[i] ^ i; 
  }
  return Xor_indicator;
}

int main() {
  return 0;
}
