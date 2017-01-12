#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

//TODO: need to come up with a more efficient algorithm!!!
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

string getPermutation_slow(int n, int k) {
  vector<int> vec(n);
  for (int i = 0; i != n; ++i) {
    vec[i] = i+1;
  }
  while (--k) {
    nextPermutation(vec);
  }
  string str;
  for (int i = 0; i != n; ++i) {
    str += to_string(vec[i]);
  }
  return str;
}

void swap_and_reorder(vector<int>& vec, int k) {
  if (k == 0) return;
  int permuteN, rightN;
  for (rightN = 0, permuteN = 1; permuteN <= k; ++rightN, permuteN *= rightN);
  int rightP = permuteN / rightN, permute_round = k / rightP;
  k -= rightP * permute_round;
  int ix1 = vec.size() - rightN, ix2 = ix1 + permute_round;
  swap(vec[ix1], vec[ix2]);
  sort(vec.begin() + ix1 + 1, vec.end());
  swap_and_reorder(vec, k);
}

// The more efficient permutation is here
string getPermutation(int n, int k) {
  vector<int> vec(n);
  for (int i = 0; i != n; ++i) {
    vec[i] = i+1;
  }
  swap_and_reorder(vec, k-1);
  string str;
  for (int i = 0; i != n; ++i) {
    str += to_string(vec[i]);
  }
  return str;
}

int main() {
  cout<<getPermutation(1, 1)<<endl;
  for (int i = 1; i <= 6; ++ i) {
    cout<<getPermutation(3, i)<<endl;
  }
  return 0;
}

