#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

int findMin(vector<int>& nums) {
  int istart = 0, iend = nums.size()-1, imid;
  while (istart + 1 < iend) {
    imid = (istart + iend) / 2;
    if (nums[imid] > nums[istart] && nums[iend] < nums[imid])
      istart = imid;
    else
      iend = imid;
  }
  return min(nums[istart], nums[iend]);
}

int main() {
  // int a[] = {4, 5, 6, 7, 0, 1, 2};
  // int a[] = {1, 2, 3};
  int a[] = {7, 8, 9, 0, 1, 2, 3, 5, 6};
  vector<int> vec(a, end(a));
  cout<<findMin(vec)<<endl;
  return 0;
}
