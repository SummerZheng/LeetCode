#include<iostream>
#include<vector>
#include<bitset>
#include"print.h"

using namespace std;

const int sz = 31;

struct TrieNode {
  TrieNode(int d = 0): digit(d), children(vector<TrieNode*>(2, nullptr)){}
  int digit;
  vector<TrieNode*> children;
};

struct Trie {
  Trie():root(new TrieNode()){}
  void insert(int num) {
    bitset<sz> bitN(num);
    TrieNode *p = root;
    for (int i = sz; i >= 0; --i) {
      int bit = bitN[i];
      if (p->children[bit] == nullptr) {
        p->children[bit] = new TrieNode(bit);
      }
      p = p->children[bit];
    }
  }
  int find_max_xor(int num) {
    bitset<sz> bitN(num), max_xor(0);
    TrieNode *p = root;
    for (int i = sz; i >= 0; --i) {
      int bit = bitN[i];
      if (p->children[1^bit]) {
        max_xor[i] = 1;
        p = p->children[1^bit];
      } else {
        max_xor[i] = 0;
        p = p->children[bit];
      }
    }
    cout<<"The maximun xor for "<<num<<" is "<<max_xor.to_ulong()<<endl;
    return max_xor.to_ulong();
  }
  TrieNode* root;
};

// construct a trie, using higher bit as higher nodes
Trie* build_trie(vector<int>& nums) {
  Trie *myTrie = new Trie();
  for (int i = 0; i != nums.size(); ++i) {
    myTrie->insert(nums[i]); 
  }
  return myTrie;
}

int findMaximumXOR(vector<int>& nums) {
  Trie* root = build_trie(nums);
  int max_xor = -1, cur_max_xor;
  for (int i = 0; i != nums.size(); ++i) {
    cur_max_xor = root->find_max_xor(nums[i]); 
    if (cur_max_xor > max_xor)
      max_xor = cur_max_xor;
  }
  return max_xor;
}

int main() {
  int a[] = {3, 10, 5, 25, 2, 8};
  vector<int> vec(a, end(a));
  cout<<findMaximumXOR(vec)<<endl;
  return 0;
}
