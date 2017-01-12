#include<iostream>
#include<vector>
#include<string>
#include"print.h"

using namespace std;

string make_string(const vector<int>& vec) {
  if (vec.size() == 1) {
    return to_string(vec[0]);
  } else {
    return to_string(vec[0]) + "->" + to_string(vec[1]);
  }
}

vector<string> summaryRanges(vector<int>& nums) {
  vector<string> ranges;
  if (nums.empty()) return ranges;
  vector<int> streak;
  streak.push_back(nums[0]);
  for (int i = 1; i < nums.size(); ++i) {
    if (nums[i] == nums[i-1] + 1) {
      if (streak.size() == 1)
        streak.push_back(nums[i]);
      else
        streak[1] = nums[i];
    } else {
      ranges.push_back(make_string(streak));
      streak.clear();
      streak.push_back(nums[i]);
    }
  }
  if (!streak.empty()) {
    ranges.push_back(make_string(streak));
  }
  return ranges;
}

int main() {
  int a[] = {0,1,2,4,5,7};
  vector<int> vec(a, end(a));
  print(summaryRanges(vec));
  return 0;
}
