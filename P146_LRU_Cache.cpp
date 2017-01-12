#include<iostream>
#include<list>
#include<unordered_map>

using namespace std;

class LRUCache{
  public:
    LRUCache(int capacity):max_sz(capacity), sz(0){
    }

    int get(int key) {
      auto iter = myHash.find(key);
      if (iter != myHash.end()) {
        int value = iter->second->second;
        if (iter->second != cache_list.end()--) {
          remove_key(iter);
          insert_key_at_back(key, value);
        }
        return value;
      } else {
        return -1;
      }
    }

    void set(int key, int value) {
      auto iter = myHash.find(key);
      if (iter != myHash.end()) {
        remove_key(iter);
      } else if (sz < max_sz){
        ++sz;
      } else {
        int del_key = cache_list.front().first;
        remove_key(myHash.find(del_key));
      }
      insert_key_at_back(key, value);
    }

    typedef std::list<std::pair<int, int>>::iterator kv_iter;
    typedef std::unordered_map<int, kv_iter>::iterator hash_iter;
  private:
    int max_sz;
    int sz;
    std::list<std::pair<int, int>> cache_list;
    std::unordered_map<int, kv_iter> myHash;
    void remove_key(hash_iter iter) {
      cache_list.erase(iter->second);
      myHash.erase(iter);
    }
    void insert_key_at_back(int key, int value) {
      kv_iter cache_it = cache_list.insert(cache_list.end(), std::make_pair(key, value));
      myHash.emplace(key, cache_it);
    }
};

int main() {
  LRUCache myCache(2);
  myCache.set(2, 1);
  myCache.set(1, 1);
  cout<<myCache.get(2)<<endl;
  myCache.set(4, 1);
  cout<<myCache.get(1)<<endl;
  cout<<myCache.get(2)<<endl;
  return 0;
}
