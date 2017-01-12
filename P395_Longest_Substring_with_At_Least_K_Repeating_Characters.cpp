#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>

using namespace std;

void print_helper(unordered_map<char, int>::iterator iter) {
  cout<<"("<<iter->first<<", "<<iter->second<<")"<<endl;
}

int longestSubstring(string s, int k) {
  unordered_map<char, int> lt_count;
  for (int i=0; i!=s.size(); ++i)
    ++lt_count[s[i]];
  unordered_set<char> forbidden_set;
  for (auto iter = lt_count.begin(); iter != lt_count.end(); ++iter) {
    if (iter->second < k)
      forbidden_set.insert(iter->first);
  }
  int max_len = 0, ix = 0;
  while (ix != s.size()) {
    cout<<ix<<endl;
    while (ix != s.size() && forbidden_set.count(s[ix])) {
      ++ix;
    }
    unordered_map<char, int> cur_substr;
    while (ix != s.size() && !forbidden_set.count(s[ix])) {
      ++cur_substr[s[ix]];
      ++ix;
    }
    //for_each(cur_substr.begin(), cur_substr.end(), print_helper);
    int cur_len = 0;
    bool valid_substr = true;
    for (auto iter = cur_substr.begin(); iter != cur_substr.end(); ++iter) {
      if (iter->second < k) {
        cout<<iter->first<<" haha "<<iter->second<<endl;
        valid_substr = false;
        break;
      } else {
        cur_len += iter->second;
      }
    }
    cout<<"valid substr "<<valid_substr<<", cur_len "<<cur_len<<endl;
    if (valid_substr && cur_len > max_len)
      max_len = cur_len;
  }
  return max_len;
}


int main() {
  string str("bbaaacbd");
  cout<<longestSubstring(str, 3)<<endl;
  return 0;
}
