#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<unordered_set>
#include"print.h"

using namespace std;

class Solution {
  public:
    Solution(){}

    void add_valid_paren(string& s, int ix, int remL, int remR, string& trail, unordered_set<string>& validset) {
      if (ix == s.size() && !remL && !remR) {
        validset.insert(trail);
        return;
      }
      if (remL > remR || remL < 0 || remR < 0 || remL > lparenCt[ix] || remR > rparenCt[ix]) return;
      trail += s[ix];
      if (s[ix] == '(') {
        add_valid_paren(s, ix+1, remL-1, remR, trail, validset);
      } else if (s[ix] == ')') {
        add_valid_paren(s, ix+1, remL, remR-1, trail, validset);
      } else {
        add_valid_paren(s, ix+1, remL, remR, trail, validset);
      }
      trail.pop_back();
      if (s[ix] == '(' || s[ix] == ')')
        add_valid_paren(s, ix+1, remL, remR, trail, validset);
    }

    void count_paren_from_right(string& s) {
      lparenCt.assign(s.size(), 0);
      rparenCt.assign(s.size(), 0);
      if (s.back() == ')') rparenCt[s.size()-1] = 1;
      if (s.back() == '(') lparenCt[s.size()-1] = 1;
      for (int i = s.size()-2; i>=0; --i ) {
        s[i] == '(' ? lparenCt[i] = lparenCt[i+1]+1 : lparenCt[i] = lparenCt[i+1];
        s[i] == ')' ? rparenCt[i] = rparenCt[i+1]+1 : rparenCt[i] = rparenCt[i+1];
      }
    }

    int count_valid_parentheses_pair(string& s) {
      int ct = 0;
      stack<char> lparen;
      for (auto& c : s) {
        if (c == '(') {
          lparen.push(c);
        } else if (c == ')') {
          if (!lparen.empty()) {
            lparen.pop();
            ++ct;
          }
        }
      }
      return ct;
    }

    vector<string> removeInvalidParentheses(string s) {
      vector<string> validstrs;
      int pCt = count_valid_parentheses_pair(s);
      cout<<"pCt is "<<pCt<<endl;
      count_paren_from_right(s);
      print(lparenCt);
      print(rparenCt);
      cout<<"parent initilization complete"<<endl;
      string trail;
      int remL = pCt, remR = pCt;
      unordered_set<string> validset;
      add_valid_paren(s, 0, remL, remR, trail, validset);
      validstrs.assign(validset.begin(), validset.end());
      cout<<"valid strs size is "<<validstrs.size()<<endl;
      return validstrs;
    }

  private:
    vector<int> lparenCt;
    vector<int> rparenCt;
};

int main() {
  Solution sol;
  //string s("");
  //string s("()())()");
  //string s("(a)())()");
  string s("");
  print(sol.removeInvalidParentheses(s));
  return 0;
}
