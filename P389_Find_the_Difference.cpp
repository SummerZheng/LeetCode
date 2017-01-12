#include<iostream>
#include<string>
#include<vector>
#include<bitset>

using namespace std;

char findTheDifference(string s, string t) {
  vector<int> ct_vec(26, 0);
  for (int i = 0; i != s.size(); ++i) {
    ++ct_vec[s[i] - 'a']; 
  }
  for (int i = 0; i != t.size(); ++i) {
    --ct_vec[t[i] - 'a']; 
  }
  int ix = 0;
  while (ct_vec[ix] == 0) {
    ++ix;
  }
  return static_cast<char>('a' + ix);
}

int main() {
  string str = "abs";
  cout<<static_cast<char>('a' + 25)<<endl;
  return 0;
}
