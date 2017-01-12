#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

int firstUniqChar(string s) {
  const int sz = 26;
  vector<int> my_hash(sz, 0);
  for (int i = 0; i != s.size(); ++i) {
    ++my_hash[s[i] - 'a'];
  }
  int ix;
  for (ix = 0; ix != s.size() && my_hash[s[ix] - 'a'] != 1; ++ix){
    cout<<s[ix]<<" appeared "<<my_hash[s[ix] - 'a']<<" times"<<endl;
  }
  return ix == s.size() ? -1 : ix;
}

int main() {
  cout<<firstUniqChar("cc")<<endl;
  cout<<firstUniqChar("leetcode")<<endl;
  cout<<firstUniqChar("loveleetcode")<<endl;
  return 0;
}
