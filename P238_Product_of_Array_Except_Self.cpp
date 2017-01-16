#include<iostream>
#include<vector>
#include"print.h"
using namespace std;

vector<int> productExceptSelf(const vector<int>& nums) {
  int fromRight = 1;
  vector<int> output(nums.size(), 1);
  for (int i = 1; i < nums.size(); ++i) {
    output[i] = output[i-1] * nums[i-1];
  }
  for (int i = nums.size()-1; i >=0; --i) {
    output[i] = output[i] * fromRight;
    fromRight *= nums[i];
  }
  return output;
}

int main() {
  vector<int> result(productExceptSelf({1, 2, 3, 4}));
  print(result);
  return 0;
}
