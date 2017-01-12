#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

bool containsNearbyDuplicate(vector<int>& nums, int k) {
  unordered_multimap<int, int> myMap;
  for (int i = 0; i != nums.size(); ++i) {
    auto iters = myMap.equal_range(nums[i]);
    while (iters.first != iters.second) {
      if (i - iters.first->second <= k) return true;
      ++iters.first;
    }
    myMap.emplace(nums[i], i);
  }
  return false;
}

int main() {
  return 0;
}
