#include<iostream>
#include<vector>

using namespace std;

template <typename T>
void print(const std::vector<T>& vec) {
  for (int i=0; i != vec.size(); ++i) {
    std::cout<<vec[i]<<" ";
  }
  std::cout<<std::endl;
}

int rob(vector<int>& nums) {
  if (nums.empty()) return 0;
  if (nums.size() == 1) return nums[0];
  vector<int> maxRob_dp(nums.size(), -1);
  maxRob_dp[0] = nums[0];
  maxRob_dp[1] = max(nums[0], nums[1]);
  for (int i = 2; i != nums.size(); ++i) {
    maxRob_dp[i] = max(maxRob_dp[i-2] + nums[i], maxRob_dp[i-1]);
  }
  print(nums);
  print(maxRob_dp);
  return maxRob_dp[nums.size()-1];
}

int main() {
  int a[] = {10, 1, 5, 18, 69, 20};
  vector<int> vec(a, end(a));
  cout<<rob(vec)<<endl;
  return 0;
}
