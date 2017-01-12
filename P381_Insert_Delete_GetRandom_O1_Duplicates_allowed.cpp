#include<iostream>
#include<unordered_set>
#include<unordered_map>
#include<vector>
#include<random>
#include"print.h"

using namespace std;

class RandomizedCollection {
  public:  
    /** Initialize your data structure here. */
    RandomizedCollection(): myMap(unordered_map<int, unordered_set<int> >()), myVec(vector<int>()), generator(default_random_engine()) { }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
      cout<<"inserting ele "<<val<<endl;
      myVec.push_back(val);
      auto iter = myMap.find(val); 
      if (iter == myMap.end()) {
        myMap.insert(make_pair(val, unordered_set<int>()));
        iter = myMap.find(val);
      }
      cout<<"before insertion, ele "<<val<<" locates at:"<<endl;
      printIxes(iter->second);
      cout<<"inserting ix "<<myVec.size()-1<<endl;
      iter->second.insert(myVec.size()-1);
      cout<<"after insertion, ele "<<val<<" locates at:"<<endl;
      printIxes(iter->second);
      cout<<"^^^"<<endl;
      return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
      cout<<"removing ele "<<val<<endl;
      auto iter = myMap.find(val);
      if (iter == myMap.end()) {
        return false;
      } else {
        cout<<"print idxes"<<endl;
        printIxes(iter->second);
        auto ix_iter = iter->second.begin();
        int  lastIx = myVec.size() - 1, lastEle = myVec.back();
        if (*ix_iter != lastIx) {
          auto last_ele_ix_set    = myMap.find(lastEle);
          // cout<<"before swap, ele "<<lastEle<<" locates at:"<<endl;
          // printIxes(last_ele_ix_set->second);
          swap(myVec[*ix_iter], myVec[lastIx]);
          last_ele_ix_set->second.erase(lastIx);
          last_ele_ix_set->second.insert(*ix_iter);
          // cout<<"after swap, ele "<<lastEle<<" locates at:"<<endl;
          // printIxes(last_ele_ix_set->second);
        }
        myVec.pop_back();
        if (*ix_iter == lastIx || val != lastEle) {
          iter->second.erase(ix_iter);
        }
        if (iter->second.empty()) {
          cout<<"remove "<<val<<"from myMap"<<endl;
          myMap.erase(iter);
        }
        // printSet();
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
    
    void printIxes(unordered_set<int>& mySet) {
      cout<<"ix set size is "<<mySet.size()<<endl;
      for (auto i = mySet.begin(); i != mySet.end(); ++i) {
        cout<<*i<<", ";
      }
    }

    void printSet() {
      cout<<"print set"<<endl;
      print(myVec);
      cout<<"end"<<endl;
    }
  private:
    unordered_map<int, unordered_set<int> > myMap;
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
  // int a[] = {0, 1, 2, 3, 3, 2, 3, 0};
  // vector<int> vec(a, end(a));
  RandomizedCollection obj;
  // for (int i = 0; i <=4; ++i) {
  //   obj.insert(vec[i]);
  // }
  // obj.printSet();
  // for (int i = 5; i <=7; ++i) {
  //   obj.remove(vec[i]);
  // }
  // obj.printSet();
  // for (int i = 0; i != 50; ++i) {
  //   cout<<obj.getRandom()<<endl;;
  // }
  int a[] = {0, 0, -1, 0};
  cout<<"inserting ele 0 is successful "<<obj.insert(a[0])<<endl;
  cout<<"removing ele 0 is successful "<<obj.remove(a[1])<<endl;
  cout<<"inserting ele -1 is successful "<<obj.insert(a[2])<<endl;
  cout<<"removing ele 0 is successful "<<obj.remove(a[3])<<endl;
  return 0;
}
