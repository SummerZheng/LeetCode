#include<iostream>
#include<vector>
using namespace std;

int maxSubArray(const vector<int>& nums) {
  if (nums.empty()) return 0;
  vector<int> dp(nums);
  int maxSum = dp[0];
  for (int i = 1; i != nums.size(); ++i) {
    dp[i] = dp[i-1] <= 0? nums[i] : dp[i-1] + nums[i];
    maxSum = max(maxSum, dp[i]);
  }
  return maxSum;
}


int main() {
  cout<<maxSubArray({-2,1,-3,4,-1,2,1,-5,4})<<endl;
  return 0;
}
