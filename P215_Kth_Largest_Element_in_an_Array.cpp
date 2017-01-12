#include"print.h"

using namespace std;

int find_pivotal_index(vector<int>& nums, int min_i, int max_i){
  int rix = rand() % (max_i - min_i + 1) + min_i;
  swap(nums[rix], nums[max_i]);
  int key = nums[max_i];
  int p1 = min_i-1, p2 = min_i;
  for (; p2 < max_i; ++p2) {
    if (nums[p2] < key) {
      swap(nums[++p1], nums[p2]);
    }
  }
  swap(nums[++p1], nums[p2]);
  return p1; 
}

int findKthSmallest(vector<int>& nums, int k, int min_i, int max_i) {
  int pix = find_pivotal_index(nums, min_i, max_i);
  int target_ix = k + min_i;
  if (target_ix == pix) {
    return nums[pix];
  } else if (target_ix < pix) {
    return findKthSmallest(nums, k, min_i, pix - 1);    
  } else {
    return findKthSmallest(nums, target_ix - pix - 1, pix+1, max_i);
  }
}

int findKthLargest(vector<int>& nums, int k) {
  return findKthSmallest(nums, nums.size() - k, 0, nums.size()-1);
}

int main() {
  int a[] = {1, 9, 8, 7, 5, 5, 6, 2, 3, 10};
  for (int i = 1; i <= 10; ++i) {
    vector<int> vec(a, end(a));
    cout<<"The "<<i<<"th largest number is "<<findKthLargest(vec, i)<<endl;
  }
  return 0;
}
