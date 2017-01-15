#include<iostream>
#include<vector>
#include<algorithm>
#include"print.h"

using namespace std;

void combinationSum_util(int target, int startIx, vector<int>& trail, vector<vector<int>>& sol, const vector<int>& candidates) {
  if (target == 0) {
    sol.push_back(trail);
    return;
  }
  if (candidates.size() <= startIx || target < 0) return;
  int curV = candidates[startIx], curCt = 1;
  while (++startIx < candidates.size() && candidates[startIx] == curV) {
    ++curCt;
  }
  for (int ct = 0; ct <= curCt && target >= 0; target-=curV, ++ct) {
    int i = 0;
    while (i++ < ct)
      trail.push_back(curV);
    combinationSum_util(target, startIx, trail, sol, candidates);
    while (--i)
      trail.pop_back();
  }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
  vector<vector<int>> solSet;
  vector<int> trail;
  sort(candidates.begin(), candidates.end());
  combinationSum_util(target, 0, trail, solSet, candidates);
  return solSet;
}


int main() {
  vector<int> mySet{10, 1, 2, 7, 6, 1, 5};
  print(combinationSum2(mySet, 8));
  return 0;
}
