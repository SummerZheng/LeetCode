#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

// DP like the last cut problem in CLRS
int integerBreak_DP(int n) {
  vector<int> DPvec(n+1, 0);
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j < i; ++j) {
      DPvec[i] = max(DPvec[i], max(j, DPvec[j]) * (i - j));
    }
  }
  print(DPvec);
  return DPvec[n];
}
// actually, we can prove for integer n >= 7 we always prefer breaking n into (n-3) and 3
// then we can use a iterative method, O(N) time, O(1) space method to solve
int integerBreak(int n) {
  vector<int> DPvec(n+1, 0);
  for (int i = 2; i <= min(n, 6); ++i) {
    for (int j = 1; j < i; ++j) {
      DPvec[i] = max(DPvec[i], max(j, DPvec[j]) * (i - j));
    }
  }
  for (int i = 7; i <=n; ++i) {
    DPvec[i] = DPvec[i-3] * 3;
  }
  print(DPvec);
  return DPvec[n];
}


int main() {
  cout<<integerBreak(2)<<endl;
  cout<<integerBreak(6)<<endl;
  cout<<integerBreak(10)<<endl;
  cout<<integerBreak(58)<<endl;
  cout<<integerBreak_DP(58)<<endl;
  return 0;
}
