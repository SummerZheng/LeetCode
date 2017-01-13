#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

void combinationSum_util(int target, int startIx, vector<int>& trail, vector<vector<int>>& sol, const vector<int>& candidates) {
  if (candidates.size() <= startIx || target < 0) return;
  if (target == 0) sol.push_back(trail);
  for (int i = startIx; i != candidates.size(); ++i) {
    if (target > candidates[i]) {
      trail.push_back(candidates[i]);
      combinationSum_util(target - candidates[i], i, trail, sol, candidates);
      trail.pop_back();
    }
  }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
  vector<vector<int>> solSet;
  vector<int> trail;
  combinationSum_util(target, 0, trail, solSet, candidates);
  print(solSet);
  return solSet;
}


int main() {
  vector<int> mySet{2, 3, 6, 7};
  combinationSum(mySet, 0);
  return 0;
}
