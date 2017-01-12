#include<iostream>
#include<set>
#include<unordered_map>

using namespace std;

struct classcomp {
  bool operator() (const pair<int, int>& lhs, const pair<int, int>& rhs) const
  {return lhs.first<rhs.first;}
};

class LFUCache{
  public:
    LFUCache(int capacity):max_sz(capacity), sz(0){
    }

    int get(int key) {
      auto iter = cache.find(key);
      if (iter != cache.end()) {
        int value = iter->second.first;
        int freq  = iter->second.second++;
        // cout<<"the freq for "<<key<<" now is "<<iter->second.second<<endl;
        PQ.erase(make_pair(freq++, key));
        //cout<<"make nPair ("<<freq<<", "<<key<<")"<<endl;
        std::pair<int, int> nPair = make_pair(freq, key);
        PQ.insert(PQ.upper_bound(nPair),  nPair);
        print();
        return value;
      } else {
        return -1;
      }
    }

    void set(int key, int value) {
      auto iter = cache.find(key);
      int freq = 1;
      if (iter != cache.end()) {
        freq  = iter->second.second;
        PQ.erase(make_pair(freq++, key));
      } else if (sz < max_sz){
        ++sz;
      } else {
        int del_key = PQ.begin()->second;
        cout<<"deleting key "<<del_key<<" with freq "<<PQ.begin()->first<<endl;
        PQ.erase(PQ.begin());
        cache.erase(del_key);
      }
      std::pair<int, int> nPair = make_pair(freq, key);
      PQ.insert(PQ.upper_bound(nPair),  nPair);
      cache[key] = make_pair(value, freq); 
    }

    void print() {
      cout<<"print PQ: "<<endl;
      for (const auto& ele : PQ) {
        cout<<"freq "<<ele.first<<", key "<<ele.second<<endl;
      }
    }
  private:
    int max_sz;
    int sz;
    std::unordered_map<int, pair<int, int>> cache; // hash of <key, <value, freq>>
    std::multiset<pair<int, int>, classcomp> PQ; // a multiset based priority queue of pair<freq, key> to manage least freq ele
};

int main() {
  LFUCache cache(2);
  cache.set(1, 1);
  cache.set(2, 2);
  cache.print();
  cout<<cache.get(1)<<endl;       // returns 1
  cache.print();
  //cache.set(3, 3);    // evicts key 2
  //cout<<cache.get(2)<<endl;       // returns -1 (not found)
  //cout<<cache.get(3)<<endl;       // returns 3.
  //cache.set(4, 4);    // evicts key 1.
  //cout<<cache.get(1)<<endl;       // returns -1 (not found)
  //cout<<cache.get(3)<<endl;       // returns 3
  //cout<<cache.get(4)<<endl;       // returns 4
  return 0;
}
