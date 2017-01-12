#include<iostream>
#include<vector>
#include<string>
// #include"../DataStruc_Algo/EleDataStruc_Round2/Trie/Trie.h"
// #include"../DataStruc_Algo/EleDataStruc_Round2/Trie/Trie.cpp"

using namespace std;

class TrieNode {
  public:
    // Initialize your data structure here.
    TrieNode():wordCount(0), prefixCount(0), children(27, nullptr){}
    std::vector<TrieNode*> children;
    int wordCount;
    int prefixCount;
};

class Trie {
  public:
    Trie() {
      root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
      insert(word, 0, root);
    }

    // Returns if the word is in the trie.
    bool search(string word) {
      return search_fullword(word, 0, root, true);
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
      return search_fullword(prefix, 0, root, false);
    }

  private:
    int char_to_index(char c) {
      return c == '\0'? 26 : static_cast<int>(c) - static_cast<int>('a');
    }
    
    void insert(std::string word, int ix, TrieNode* node){
      ++node->prefixCount;
      if (word[ix] == '\0') {
        ++node->wordCount;
      } else {
        int ix_next = char_to_index(word[ix]);
        if (node->children[ix_next] == nullptr) {
          node->children[ix_next] = new TrieNode(word[ix]);
        }
        insert(word, ix+1, node->children[ix_next]);
      }
    }

    bool search_fullword(std::string word, int ix, TrieNode* node, bool fullword){
      if (word[ix] == '\0') {
        if (fullword) {
          return static_cast<bool>(node->wordCount);
        } else {
          return static_cast<bool>(node->prefixCount);
        }
      } else {
        int ix_next = char_to_index(word[ix]);
        if (node->children[ix_next] == nullptr) {
          return false;
        } else {
          return search_fullword(word, ix+1, node->children[ix_next], fullword);
        }
      }
    }

    TrieNode* root;
};


int main() {
  Trie trie;
  trie.insert("somestring");
  cout<<trie.search("key")<<endl;
  cout<<trie.search("somestring")<<endl;
  cout<<trie.search("somes")<<endl;
  cout<<trie.startsWith("somes")<<endl;
  return 0;
}
