#include<iostream>
#include<vector>

using namespace std;

int trap(vector<int>& height) {
  if (height.empty()) return 0;
  int N = height.size();
  vector<int> lmax(N, 0), rmax(N, 0);
  lmax[0] = height[0];
  rmax[N-1] = height[N-1];
  for (int i = 1; i < N; ++i) {
    lmax[i] = height[i] > lmax[i-1] ? height[i] : lmax[i-1];
    rmax[N-1-i] = height[N-1-i] > rmax[N-i] ? height[N-1-i] : rmax[N-i];
  }
  int wt = 0;
  for (int i = 0; i < N; ++i) {
    wt += min(lmax[i], rmax[i]) - height[i];
  }
  return wt;
}
