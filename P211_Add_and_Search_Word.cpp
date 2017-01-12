#include<iostream>
#include<vector>
#include<string>

using namespace std;

const int sz = 26;

class TrieNode{
  friend class WordDictionary;
  public:
    TrieNode():word_ct(0), children(vector<TrieNode*>(sz+1, nullptr)){}
  private:
    int word_ct;
    vector<TrieNode*> children;
};

class WordDictionary{
  public:
    WordDictionary():root(new TrieNode()){}

    // Adds a word into the data structure.
    void addWord(string word) {
      insert(word, 0, root);
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
      return search(word, 0, root);
    }

  private:
    inline int char_to_ix(char c) { return c == '\0'? sz : static_cast<int>(c) - static_cast<int>('a'); }
    void insert(string str, int ix, TrieNode* p);
    bool search(string word, int ix, TrieNode* p);
    TrieNode* root;
};

bool WordDictionary::search(string word, int ix, TrieNode* p) {
  if (p == nullptr)
    return false;
  if (word[ix] == '\0') {
    return static_cast<bool>(p->word_ct);
  } else if (word[ix] != '.') {
    int child_ix = char_to_ix(word[ix]);
    return search(word, ix+1, p->children[child_ix]);
  } else {
    for (int i = 0; i <= sz; ++i) {
        if (search(word, ix+1, p->children[i])) return true;
    }
    return false;
  }
}

void WordDictionary::insert(string str, int ix, TrieNode* p) {
  if (str[ix] == '\0') {
    ++p->word_ct;
  } else {
    int child_ix = char_to_ix(str[ix]);
    if (p->children[child_ix] == nullptr) {
      p->children[child_ix] = new TrieNode();
    }
    insert(str, ix+1, p->children[child_ix]);
  } 
}

int main() {
  WordDictionary wordDictionary; 
  wordDictionary.addWord("word");
  cout<<wordDictionary.search("word")<<endl;
  cout<<wordDictionary.search("world")<<endl;
  cout<<wordDictionary.search("wor")<<endl;
  cout<<wordDictionary.search("wo.d")<<endl;
  cout<<wordDictionary.search("wo..")<<endl;
  cout<<wordDictionary.search("we..")<<endl;
  return 0;
}
