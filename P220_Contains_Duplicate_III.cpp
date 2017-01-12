#include<iostream>
#include<vector>
#include<set>

using namespace std;

// abs(nums[i] - nums[j]) <= t and (j-i+1) <= k
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
  if (t < 0 || k <= 0) return false;
  set<long long> mySet;
  set<long long>::iterator itlow, itup;
  for (int i = 0; i != nums.size(); ++i) {
    if (i > k) mySet.erase(nums[i-k-1]);
    if (!mySet.insert(nums[i]).second) return true;
    itlow = mySet.lower_bound(nums[i]);
    if (itlow != mySet.begin() && (nums[i] - *(--itlow)) <= t) {
      cout<<"the inserted value "<<nums[i]<<" and "<<*itlow<<" are closer than "<<t<<endl;
      return true;
    }
    itup = mySet.upper_bound(nums[i]);
    if (itup != mySet.end() && (*itup - nums[i]) <= t) {
      cout<<*itup<<" and the inserted value "<<nums[i]<<" are closer than "<<t<<endl;
      return true;
    }
  }
  return false;
}

bool containsNearbyAlmostDuplicate_v2(vector<int>& nums, int k, int t) {
  if (t < 0 || k <= 0) return false;
  set<int> mySet;
  set<int>::iterator iter;
  for (int i = 0; i != nums.size(); ++i) {
    if (i > k) mySet.erase(nums[i-k-1]);
    iter = mySet.lower_bound(nums[i]-t);
    if (iter != mySet.end() && *iter - t <= nums[i]) return true;
    mySet.insert(nums[i]);
  }
  return false;
}

int main(){
  int a[] = {7, 1, 3};
  vector<int> vec(a, end(a));
  cout<<containsNearbyAlmostDuplicate(vec, 2, 3)<<endl;
  return 0;
}
