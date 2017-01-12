#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

// if we can modify the array
// O(N) time complexity, O(1) extra space
int findDuplicate_modifyArr(vector<int>& nums) {
  int n = nums.size()-1, i;
  for (i = 0; i != nums.size(); ++i) {
    while (nums[i] != i+1) {
      if (nums[i] == nums[nums[i]-1])
        return nums[i];
      swap(nums[i], nums[nums[i]-1]);
      print(nums);
    }
  }
  return i+1;
}

// if we don't modify the array
//
// O(N) time complexity, O(1) extra space
int findDuplicate(vector<int>& nums) {
}

int main() {
  // int a[] = {4, 6, 3, 1, 5, 5, 2};
  int a[] = {4, 6, 3, 1, 2, 5, 2};
  vector<int> vec(a, end(a));
  print(vec);
  cout<<"Duplicate in the arr is :"<<endl;
  cout<<findDuplicate(vec)<<endl;
  return 0;
}
