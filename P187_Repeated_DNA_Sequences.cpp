#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include"print.h"

using namespace std;

vector<string> findRepeatedDnaSequences(string s) {
  vector<string> repeat_str;
  unordered_map<string, int> my_hash;
  int len = 10, str_sz = static_cast<int>(s.size());
  for (int i = 0; i <= str_sz - len; ++i) {
    ++my_hash[s.substr(i, len)]; 
  }  
  for (auto iter = my_hash.begin(); iter != my_hash.end(); ++iter) {
    if (iter->second > 1)
      repeat_str.push_back(iter->first);
  }
  return repeat_str;
}

int main() {
  //string s("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
  string s("AAAAAAAAAAA");
  vector<string> vec = findRepeatedDnaSequences(s);
  print(vec);
  return 0;
}
