#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include"print.h"

using namespace std;

// Define N = max(num1.size(), nums2.size()) 

// Two pointer method
// complexity O(NlogN + N) ~ O(NlogN) 
// if the two vectors are presorted, then O(N)
vector<int> intersect_2ptr(vector<int>& nums1, vector<int>& nums2) {
  sort(nums1.begin(), nums1.end());
  sort(nums2.begin(), nums2.end());
  vector<int> intersect_vec;
  for (int i1 = 0, i2 = 0; i1 != nums1.size() && i2 != nums2.size(); ) {
    if (nums1[i1] == nums2[i2]) {
      intersect_vec.push_back(nums1[i1]);
      ++i1; ++i2;
    } else if (nums1[i1] < nums2[i2]) {
      ++i1;
    } else {
      ++i2;
    } 
  }
  return intersect_vec;
}

// hash map
// complexity O(N)
vector<int> intersect_hash(vector<int>& nums1, vector<int>& nums2) {
  unordered_map<int, int> hash1;
  for (int i = 0; i != nums1.size(); ++i) {
    ++hash1[nums1[i]];
  }
  vector<int> intersect_vec;
  for (int i = 0; i != nums2.size(); ++i) {
    auto iter = hash1.find(nums2[i]);
    if (iter != hash1.end()) {
      intersect_vec.push_back(iter->first);
      --iter->second;
      if (iter->second == 0) {
        hash1.erase(iter);
      }
    }
  }
  return intersect_vec;
}

int main() {
  int a[] = {1, 2, 2, 1};
  int b[] = {2, 2};
  vector<int> nums1(a, end(a));
  vector<int> nums2(b, end(b));
  vector<int> intersect_vec(intersect_2ptr(nums1, nums2));
  print(intersect_vec);
  return 0;
}
