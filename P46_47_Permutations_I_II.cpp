#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

bool nextPermutation(vector<int>& nums) {
  int i, j;
  for (i = nums.size()-1; i > 0 && nums[i-1] >= nums[i]; --i); 
  if (i == 0) {
    return false;
  } else {
    for (j = nums.size()-1; nums[j] <= nums[i-1]; --j);
    swap(nums[i-1], nums[j]);
    for (int ix1 = i, ix2 = nums.size()-1; ix1 < ix2; ++ix1, --ix2) {
      swap(nums[ix1], nums[ix2]);
    }
    return true;
  }
}

vector<vector<int> > permute(vector<int>& nums) {
  std::sort(nums.begin(), nums.end());
  vector<vector<int> > permute_ensemble;
  permute_ensemble.push_back(nums);
  while (nextPermutation(nums)) {
    permute_ensemble.push_back(nums);
  }
  // print(permute_ensemble);
  return permute_ensemble;
}

int main() {
  int a[] = {1, 2, 2, 4};
  vector<int> nums(a, end(a));
  permute(nums);
  return 0;
}

