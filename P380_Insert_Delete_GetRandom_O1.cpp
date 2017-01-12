#include<iostream>
#include<unordered_map>
#include<vector>
#include<random>
#include"print.h"

using namespace std;

class RandomizedSet {
  public:
    /** Initialize your data structure here. */
    RandomizedSet(): myMap(unordered_map<int, int>()), myVec(vector<int>()), generator(default_random_engine()) { 
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
      if (myMap.count(val)) return false;
      myVec.push_back(val);
      myMap.insert(make_pair(val, myVec.size()-1));
      return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
      unordered_map<int, int>::iterator iter = myMap.find(val);
      if (iter == myMap.end()) {
        return false;
      } else {
        int ix = iter->second;
        if (ix != myVec.size()-1) {
          int lastEle = myVec.back();
          unordered_map<int, int>::iterator last_ele_iter = myMap.find(lastEle);
          int last_ele_ix = last_ele_iter->second;
          swap(myVec[ix], myVec[last_ele_ix]);
          last_ele_iter->second = ix;
        }
        myVec.pop_back();
        myMap.erase(iter);
        return true;
      }
    }

    /** Get a random element from the set. */
    int getRandom() {
      if (myVec.empty())
        return -1;
      std::uniform_int_distribution<int> distribution(1,myVec.size());
      int randN =  distribution(generator);
      return myVec[randN-1];
    }
    void printSet() {
      print(myVec);
    }
  private:
    unordered_map<int, int> myMap;
    vector<int> myVec;
    std::default_random_engine generator;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */

int main() {
  RandomizedSet obj;
  // bool param_1 = obj.insert(0);
  // obj.printSet();
  // bool param_2 = obj.remove(0);
  // obj.printSet();
  // bool param_3 = obj.insert(2);
  // obj.printSet();
  // bool param_4 = obj.remove(0);
  // obj.printSet();
  // //cout<<param_1<<" "<<param_2<<" "<<param_3<<" "<<param_4<<" "<<endl;
  // //obj.printSet();
  // vector<int> ct(5, 0);
  // for (int i = 0; i != 1000; ++i) {
  //   ++ct[obj.getRandom()];
  // }
  // print(ct);
  // cout<<numeric_limits<int>::max()<<endl;
  // cout<<numeric_limits<int>::min()<<endl;
  for (int i = 1; i <=10; ++i) {
    obj.insert(i);
  }
  obj.printSet();
  for (int i = -1; i >= -10; --i) {
    obj.insert(i);
  }
  obj.printSet();
  for (int i = 0; i != 50; ++i) {
    cout<<obj.getRandom()<<endl;;
  }
  for (int i = 1; i <=10; ++i) {
    obj.remove(i);
  }
  obj.printSet();
  for (int i = -1; i >= -10; --i) {
    obj.remove(i);
  }
  obj.printSet();
  return 0;
}
