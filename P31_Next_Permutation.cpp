#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

void nextPermutation(vector<int>& nums) {
  int i, j;
  for (i = nums.size()-1; i > 0 && nums[i-1] >= nums[i]; --i); 
  if (i == 0) {
    reverse(nums.begin(), nums.end());
  } else {
    for (j = nums.size()-1; nums[j] <= nums[i-1]; --j);
    swap(nums[i-1], nums[j]);
    for (int ix1 = i, ix2 = nums.size()-1; ix1 < ix2; ++ix1, --ix2) {
      swap(nums[ix1], nums[ix2]);
    }
  }
}

int main() {
  int a[] = {1, 2, 2, 4};
  vector<int> vec(a, end(a));
  int ct = 24;
  while (ct--) {
    nextPermutation(vec);
    print(vec);
  }
  return 0;
}

