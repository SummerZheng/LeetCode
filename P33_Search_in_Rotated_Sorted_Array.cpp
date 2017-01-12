#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

int search(vector<int>& nums, int target) {
  int istart = 0, iend = nums.size()-1, imid;
  while (istart < iend) {
    // cout<<endl;
    // cout<<"istart "<<istart<<", iend "<<iend<<endl;
    imid = (istart + iend) / 2;
    bool flag1 = nums[istart] <= nums[imid] && (target >= nums[istart] && target <= nums[imid]);
    bool flag2 = nums[imid] < nums[istart] && (target >= nums[istart] ||target <= nums[imid]);
    if (flag1 || flag2)
      iend = imid;
    else
      istart = imid+1;
  }
  // cout<<"target "<<target<<", cp with nums[istart] "<<nums[istart]<<endl;
  return target == nums[istart]? istart : -1;
}

int main() {
  // int a[] = {4, 5, 6, 7, 0, 1, 2};
  // int a[] = {1, 2, 3};
  int a[] = {7, 8, 9, 0, 1, 2, 3, 5, 6};
  // int a[] = {1};
  vector<int> vec(a, end(a));
  print(vec);
  for (int i = 0; i !=20; ++i) {
    cout<<i<<" is in the arr "<<search(vec, i)<<endl;
  }
  return 0;
}
