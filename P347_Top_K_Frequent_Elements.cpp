#include<iostream>
#include<queue>
#include<vector>
#include<unordered_map>
#include"print.h"

using namespace std;

typedef pair<int, int> myPair;

// Round 1, Hash + Priority Queue (self define comparison)
struct myCmp {
  bool operator() (const myPair& p1, const myPair& p2) {
    return p1.second < p2.second;
  }
};

vector<int> topKFrequent_1st(vector<int>& nums, int k) {
  unordered_map<int, int> myHash;
  for (auto num : nums) {
    ++myHash[num];
  }
  priority_queue<myPair, std::vector<myPair>, myCmp> myPQ;
  for (auto ele : myHash) {
    // cout<<"push ele "<<ele.first<<", "<<ele.second<<" int myPQ"<<endl;
    myPQ.push(ele);
  }
  vector<int> topKele;
  while (k--) {
    myPair freqEle = myPQ.top();
    topKele.push_back(freqEle.first);
    myPQ.pop();
  }
  return topKele;
}

// Round 2, Hash + Priority Queue (use the built-in comp for pair, aka compare 1st then 2nd ele of pair)
vector<int> topKFrequent_2nd(vector<int>& nums, int k) {
  unordered_map<int, int> myHash;
  for (auto num : nums) {
    ++myHash[num];
  }
  priority_queue<myPair> myPQ;
  for (auto ele : myHash) {
    myPQ.push(make_pair(ele.second, ele.first));
  }
  vector<int> topKele;
  while (k--) {
    myPair freqEle = myPQ.top();
    topKele.push_back(freqEle.second);
    myPQ.pop();
  }
  return topKele;
}

// Round 3, Hash + bucket sort
vector<int> topKFrequent(vector<int>& nums, int k) {
  unordered_map<int, int> myHash;
  for (auto num : nums) {
    ++myHash[num];
  }
  vector<vector<int> > bucket(nums.size()+1);
  for (auto ele : myHash) {
    bucket[ele.second].push_back(ele.first);
  }
  print(bucket);
  vector<int> topKele;
  for (int i = bucket.size()-1; i >=0; --i) {
    for (int j = 0; j != bucket[i].size(); ++j) {
      if (k) {
        topKele.push_back(bucket[i][j]);
        --k;
      } else {
        break;
      }
    }
  }
  return topKele;
}

int main() {
  int a[] = {5,3,1,1,1,3,73,1};
  vector<int> vec(a, end(a));
  vector<int> topEle = topKFrequent(vec, 1);
  print(topEle);
  return 0;
}
