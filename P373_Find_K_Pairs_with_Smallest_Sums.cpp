#include<iostream>
#include<vector>
#include<queue>
#include"print.h"

using namespace std;

struct mySum{
  mySum(){}
  mySum(int _sum, int _ix1, int _ix2):sum(_sum), ix1(_ix1), ix2(_ix2){}
  int sum;
  int ix1;
  int ix2;
};

class myComp{
  public:
    bool operator()(const mySum& s1, const mySum& s2) {return s1.sum > s2.sum;}
};

vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
  vector<pair<int, int>> kMinPair;
  if (nums1.empty() || nums2.empty()) return kMinPair;
  if (k > nums1.size() * nums2.size()) k = nums1.size() * nums2.size();
  priority_queue<mySum, std::vector<mySum>, myComp> myPQ;
  for (int i = 0; i != nums1.size(); ++i) {
    myPQ.push(mySum(nums1[i] + nums2[0], i, 0));
  }
  while (k--) {
    mySum minP = myPQ.top();
    myPQ.pop();
    int ix1 = minP.ix1, ix2 = minP.ix2;
    if (ix2 != nums2.size() - 1) {
      myPQ.push(mySum(nums1[ix1] + nums2[ix2+1], ix1, ix2+1));
    }
    kMinPair.push_back(make_pair(nums1[ix1], nums2[ix2]));
  }
  return kMinPair;
}

int main() {
  int a[] = {1,7,11};
  int b[] = {2,4,6};
  vector<int> v1(a, end(a));
  vector<int> v2(b, end(b));
  print(kSmallestPairs(v1, v2, 3));
  return 0;
}

