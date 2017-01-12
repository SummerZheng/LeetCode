#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
  unordered_set<int> hash1;
  for (int i = 0; i != nums1.size(); ++i) {
    hash1.insert(nums1[i]);
  }
  vector<int> intersect_vec;
  for (int i = 0; i != nums2.size(); ++i) {
    auto iter = hash1.find(nums2[i]);
    if (iter != hash1.end()) {
      intersect_vec.push_back(*iter);
      hash1.erase(iter);
    }
  }
  return intersect_vec;
}

int main() {
  return 0;
}
