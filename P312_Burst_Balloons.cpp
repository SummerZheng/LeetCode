#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

// DP O(N^3)
// top_down
int maxCoins_topdown(vector<int>& nums, int istart, int iend, int leftPad, int rightPad, vector<vector<int>>& myHash) {
  if (!myHash[istart][iend]) {
    int maxCoin = 0, lastEle;
    if (istart == iend) {
      maxCoin = leftPad * nums[istart] * rightPad;
    } else {
      for (int i = istart; i <= iend; ++i) {
        // nums[i] is the last burst
        int curMax = 0, lMax = 0, rMax = 0;
        if ( i != istart ) {
          lMax = maxCoins_topdown(nums, istart, i-1, leftPad, nums[i], myHash);
        }
        if ( i != iend ) {
          rMax = maxCoins_topdown(nums, i+1, iend, nums[i], rightPad, myHash);
        }
        curMax = lMax + leftPad * nums[i] * rightPad + rMax;
        if (curMax > maxCoin) {
          maxCoin = curMax;
        }
      }
    }
    myHash[istart][iend] = maxCoin;
  }
  return myHash[istart][iend];
}

// bottom_up
int maxCoins_bottomup(vector<int>& nums) {
  int N = nums.size();
  // padded the two ends with 1 respectively, so we can simplify boundary condition
  nums.insert(nums.begin(), 1);
  nums.push_back(1);
  vector<vector<int> > myHash(N+2, vector<int>(N+2, 0));
  for (int len = 1; len <= N; ++len) {
    for (int i = 1; i <= N+1 - len; ++i) {
      int j = i + len - 1; 
      for (int imid = i; imid <=j; ++imid) {
        int challenger = myHash[i][imid-1] + nums[i-1] * nums[imid] * nums[j+1] + myHash[imid+1][j]; 
        myHash[i][j] = max(myHash[i][j], challenger);
      }
    }
  }
  print(myHash);
  return myHash[1][N];
}

int maxCoins(vector<int>& nums) {
  if (nums.empty()) return 0;
  // vector<vector<int> > myHash(nums.size(), vector<int>(nums.size(), 0));
  // return maxCoins_topdown(nums, 0, nums.size()-1, 1, 1, myHash);
  return maxCoins_bottomup(nums);
}

int main() {
  int a[] = {3, 1, 5, 8};
  vector<int> vec(a, end(a));
  cout<<maxCoins(vec)<<endl;
  return 0;
}
