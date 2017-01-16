#include<iostream>
#include<vector>
#include"print.h"
using namespace std;

int maxProduct(const vector<int>& nums) {
  if (nums.empty()) return 0;
  vector<int> maxPos(nums);
  vector<int> minNeg(nums);
  int maxP = nums[0];
  for (int i = 1; i != nums.size(); ++i) {
    if (nums[i] > 0) {
      maxPos[i] = maxPos[i-1] > 0 ? maxPos[i-1] * nums[i] : nums[i];
      minNeg[i] = minNeg[i-1] < 0 ? minNeg[i-1] * nums[i] : nums[i];
    } else {
      maxPos[i] = minNeg[i-1] < 0 ? minNeg[i-1] * nums[i] : nums[i];
      minNeg[i] = maxPos[i-1] > 0 ? maxPos[i-1] * nums[i] : nums[i];
    }
    maxP = max(maxP, maxPos[i]);
  }
  print(maxPos);
  print(minNeg);
  return maxP;
}


int main() {
  // cout<<maxProduct({-2})<<endl;
  // cout<<maxProduct({2, 3, -2, 4})<<endl;
  cout<<maxProduct({-5, 0, 2})<<endl;
  return 0;
}
