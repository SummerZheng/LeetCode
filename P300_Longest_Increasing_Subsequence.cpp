// A similar problem is 354. Russian Doll Envelopes
#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

// DP, O(N^2) time complexity, O(N) space complexity
int lengthOfLIS_DP(vector<int>& nums) {
  vector<int> DPvec(nums.size(), 1);
  int maxL = nums.empty()?0:1, len;
  for (int i = nums.size()-2; i >=0; --i) {
    for (int j = nums.size()-1; j>i; --j) {
      if (nums[j] > nums[i]) {
        DPvec[i] = max(DPvec[i], DPvec[j] + 1);
      }
    }
    if (DPvec[i] > maxL)
      maxL = DPvec[i];
  }
  return maxL;
}

// Patience Sorting, O(NlogN) time complexity, O(N) space complexity
// The best explanation for patience sorting!!!
// https://www.cs.princeton.edu/courses/archive/spring13/cos423/lectures/LongestIncreasingSubsequence.pdf
void BSinsert(int n, vector<int>& cardPile, int istart, int iend) {
  if (istart == iend) {
    cardPile[istart] = n;
  } else {
    int imid = (istart + iend) / 2;
    if (cardPile[imid] >= n) {
      BSinsert(n, cardPile, istart, imid);
    } else{
      BSinsert(n, cardPile, imid+1, iend);
    }
  }
}

int lengthOfLIS(vector<int>& nums) {
  if (nums.empty()) return 0;
  vector<int> cardPile(1, nums[0]);
  for (int i = 1; i != nums.size(); ++i) {
    if (nums[i] > cardPile.back()) {
      cardPile.push_back(nums[i]);
    } else {
      BSinsert(nums[i], cardPile, 0, cardPile.size());
    }
  }
  print(cardPile);
  return cardPile.size();
}

int main() {
  int a[] = {10, 9, 2, 5, 3, 7, 101, 18};
  vector<int> vec(a, end(a));
  cout<<lengthOfLIS(vec)<<endl;
  return 0;
}
