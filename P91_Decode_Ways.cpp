#include<iostream>
#include<vector>
#include<string>
#include"print.h"
using namespace std;


int numDecodings(string s) {
  if (s.empty()) return 0;
  int N = s.size();
  vector<int> dp(N+1, 1);
  dp[1] = s[0] == '0' ? 0 : 1;
  int lastD = s[0] - '0', curD, last2;
  for (int i = 1; i < N; ++i) {
    curD = s[i] - '0';
    last2 = 10 * lastD + curD;
    if (last2 >= 10 && last2 <= 26) {
      if (curD) {
        dp[i+1] = dp[i] + dp[i-1];
      } else {
        dp[i+1] = dp[i-1];
      }
    } else if (curD){
      dp[i+1] = dp[i];
    } else {
      dp[i+1] = 0;
    }
    lastD = curD;
  }
  cout<<"string "<<s<<endl;
  print(dp);
  return dp.back();
}


int main() {
  cout<<numDecodings("")<<endl;
  cout<<numDecodings("0")<<endl;
  cout<<numDecodings("1")<<endl;
  cout<<numDecodings("12")<<endl;
  cout<<numDecodings("10")<<endl;
  cout<<numDecodings("100")<<endl;
  cout<<numDecodings("110")<<endl;
  cout<<numDecodings("12721")<<endl;
  return 0;
}
