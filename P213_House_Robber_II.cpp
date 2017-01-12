#include<iostream>
#include<vector>
#include<deque>

using namespace std;

template <typename T>
void print(const std::vector<T>& vec) {
  for (int i=0; i != vec.size(); ++i) {
    std::cout<<vec[i]<<" ";
  }
  std::cout<<std::endl;
}

int rob_vec(vector<int>& nums) {
  if (nums.empty()) return 0;
  if (nums.size() == 1) return nums[0];
  vector<int> maxRob_dp(nums.size(), -1);
  maxRob_dp[0] = nums[0];
  maxRob_dp[1] = max(nums[0], nums[1]);
  for (int i = 2; i != nums.size(); ++i) {
    maxRob_dp[i] = max(maxRob_dp[i-2] + nums[i], maxRob_dp[i-1]);
  }
  // print(nums);
  // print(maxRob_dp);
  return maxRob_dp[nums.size()-1];
}

int rob_circle(vector<int>& nums) {
  if (nums.empty()) return 0;
  if (nums.size() == 1) return nums[0];
  if (nums.size() == 2) return max(nums[0], nums[1]);
  vector<int> vec1(nums.begin() + 2, nums.end()-1);
  int r1 = nums[0] + rob_vec(vec1);
  vector<int> vec2(nums.begin() + 1, nums.end());
  int r2 = rob_vec(vec2); 
  return max(r1, r2);
}

int main() {
  // int a[] = {10, 1, 5, 18, 69, 20};
  // int a[] = {19, 8, 13, 1, 15, 12, 10, 17};
  int a[] = {1,1};
  vector<int> vec(a, end(a));
  cout<<rob_circle(vec)<<endl;
  return 0;
}
