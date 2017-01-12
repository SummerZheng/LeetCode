#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

int firstMissingPositive(vector<int>& nums) {
  int i, rix, n = nums.size();
  for (i = 0; i != n ; ++i) {
    while ((nums[i] > 0 && nums[i] <= n) && nums[i] != i+1 && nums[i] != nums[nums[i]-1]) {
      swap(nums[i], nums[nums[i]-1]);
    }
    print(nums);
  }
  print(nums);
  for (i = 0; i != nums.size() && nums[i] == i+1; ++i) {
  }
  return i+1;
}

int main() {
  // int a[] = {3, 10, 7, 8, 1, 2, -8};
  int a[] = {3, 4, -1, 1};
  // int a[] = {0};
  vector<int> vec(a, end(a));
  cout<<firstMissingPositive(vec)<<endl;
  return 0;
}
