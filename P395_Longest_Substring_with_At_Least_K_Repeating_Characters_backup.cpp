#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<unordered_map>

using namespace std;

typedef pair<int, int> key_idx_pair;

struct myComp{
  bool operator()(const key_idx_pair& lhs, const key_idx_pair& rhs) const {
    return lhs.second > rhs.second;
  }
};

typedef priority_queue<key_idx_pair, vector<key_idx_pair>, myComp> myHeap;

void enheap_dequeue(int key, myHeap& my_heap, queue<int>& my_queue) {
  my_heap.push(make_pair(key, my_queue.front()));
  cout<<"before pop top of my_queue is "<<my_queue.front()<<endl;
  my_queue.pop();
  if (my_queue.empty()) {
    cout<<"after pop top of my_queue is empty"<<endl;
  } else {
    cout<<"after pop top of my_queue is "<<my_queue.front()<<endl;
  }
}

int longestSubstring(string s, int k) {
  int a_int = static_cast<int>('a');
  int z_int = static_cast<int>('z');
  vector<queue<int> > idx_ct(z_int - a_int + 1, queue<int>());
  for (int i = 0; i!=s.size(); ++i) {
    idx_ct[static_cast<int>(s[i]) - a_int].push(i);
  }
  myHeap min_block_heap;
  myHeap min_candidate_heap;
  for (int i=0; i!=idx_ct.size(); ++i) {
    if (idx_ct[i].size() ) {
     if (idx_ct[i].size() < k) {
      enheap_dequeue(i, min_block_heap, idx_ct[i]);
     } else {
      enheap_dequeue(i, min_candidate_heap, idx_ct[i]);
     } 
    }
  }
  if (min_block_heap.empty()) return s.size();
  int last_idx = -1, max_len = 0;
  while (!min_block_heap.empty()) {
    key_idx_pair min_pair = min_block_heap.top();
    min_block_heap.pop();
    int key = min_pair.first, cur_idx = min_pair.second;
    cout<<"min_pair with key "<<static_cast<char>(key+a_int)<<", cur_idx "<<cur_idx<<endl;
    if (!idx_ct[key].empty()) {
      enheap_dequeue(key, min_block_heap, idx_ct[key]); 
    }
    unordered_map<int, int> candidate_ct;
    key_idx_pair candidate = min_candidate_heap.top();
    while (candidate.second < cur_idx) {
      cout<<"candidate is key "<<candidate.first<<", idx "<<candidate.second<<endl;
      ++candidate_ct[candidate.first];
      min_candidate_heap.pop();
      if (!idx_ct[key].empty()) {
        enheap_dequeue(candidate.first, min_candidate_heap, idx_ct[key]); 
      }
      candidate = min_candidate_heap.top();
    }
    bool update_flag = true;
    for (auto iter = candidate_ct.begin(); iter != candidate_ct.end(); ++iter) {
      if (iter->second < k){
        update_flag = false;
        break;
      }
    }
    if (update_flag && cur_idx - 1 - last_idx > max_len) {
      max_len = cur_idx-1-last_idx;
      cout<<"update max_len to "<<max_len<<" from cur_idx "<<cur_idx<<", last_idx "<<last_idx<<endl;
    }
    last_idx = cur_idx;
  }
  return max_len;
}


int main() {
  string str("ababacb");
  cout<<longestSubstring(str, 3)<<endl;
  return 0;
}
