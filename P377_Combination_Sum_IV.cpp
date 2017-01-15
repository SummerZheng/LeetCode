#include<iostream>
#include<vector>
#include<algorithm>
#include"print.h"

using namespace std;

int combinationSum4(vector<int>& nums, int target) {
  sort(nums.begin(), nums.end()); 
  vector<int> dpVec(target+1, 0);
  dpVec[0] = 1;
  for (int n = 1; n <= target; ++n) {
    for (int i = 0; i != nums.size() && nums[i] <= n; ++i) {
      dpVec[n] += dpVec[n-nums[i]];
    }
  } 
  print(dpVec);
  return dpVec[target];
}

int main() {
  vector<int> nums{3, 33, 333};
  cout<<combinationSum4(nums, 100)<<endl;
  return 0;
}
