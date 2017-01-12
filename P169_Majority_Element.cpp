#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int majorityElement_count(vector<int>& nums) {
  if (nums.empty()) return 0;
  int ele = nums[0], count = 1;
  for (int i = 1; i != nums.size(); ++i) {
    if (nums[i] == ele) {
      ++count; 
    } else if (count == 1) {
      ele = nums[i];
    } else {
      --count;
    }
  }
  return ele;
}

int majorityElement_sort(vector<int>& nums) {
  int idx = nums.size()/2;
  sort(nums.begin(), nums.end());
  return nums[idx];
}

int majorityElement_hash(vector<int>& nums) {
  unordered_map<int, int> myHash;
  int num = nums.size()/2;
  for (int i=0; i != nums.size(); ++i) {
    ++myHash[nums[i]];
  }
  for (auto iter = myHash.begin(); iter != myHash.end(); ++iter) {
    if (iter->second > num)
      return iter->first;
  }
  return 0;
}

int main() {
  int a[] = {1, 1, 4, 5, 7, 1, 8, 1, 1};
  vector<int> vec(a, end(a));
  cout<<majorityElement_count(vec)<<endl;
  cout<<majorityElement_sort(vec)<<endl;
  return 0;
}
