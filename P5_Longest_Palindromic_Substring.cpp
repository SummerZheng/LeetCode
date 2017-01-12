#include<iostream>
#include<vector>
#include<string>
#include"print.h"

using namespace std;

// Time Limit Exceeds
string longestPalindrome(string s) {
  if (s.empty()) return s;
  int N = s.size();
  vector<vector<bool> > DPmat(N, vector<bool>(N, true));
  int i1 = 0, maxL = 0;
  for (int l = 1; l <= s.size(); ++l) {
    for (int i = 0; i < s.size()-l; ++i) {
      int j = i + l;
      DPmat[i][j] = s[i] == s[j] && DPmat[i+1][j-1];
      if (DPmat[i][j] && l > maxL) {
        maxL = l;
        i1 = i;
      }
    }
  }
  return s.substr(i1, maxL+1);
}

int main() {
  cout<<longestPalindrome("babad")<<endl;
  cout<<longestPalindrome("cbbd")<<endl;
  return 0;
}
