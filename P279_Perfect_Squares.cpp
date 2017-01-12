#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// int coinChange(vector<int>& coins, int amount) {
//   if (coins.empty()) return -1;
//   vector<int> minEx(amount+1, -1);
//   minEx[0] = 0;
//   for (int m = 0; m <= amount; ++m) {
//     for (int i = 0; i != coins.size(); ++i) {
//       if (m - coins[i] >= 0 && minEx[m-coins[i]] > -1) {
//         minEx[m] = minEx[m] > -1 ? min(minEx[m], minEx[m-coins[i]] + 1) : minEx[m - coins[i]] +1; 
//       }
//     }
//   }
//   return minEx[amount];
// }
// 
// int numSquares(int n) {
//   int sqN = 1, max_sqN = sqrt(n);
//   vector<int> squares;
//   while (sqN <= max_sqN) {
//     squares.push_back(sqN * sqN);
//     ++sqN;
//   }
//   return coinChange(squares, n);
// }

int numSquares(int n) {
  vector<int> dp(n+1, INT_MAX);
  dp[0] = 0;
  for (int m = 0; m <= n; ++m) {
    for (int i=1; i*i<=m; ++i)
      dp[m] = min(dp[m], dp[m-i*i] + 1);
  }
  return dp[n];
}

int main() {
  int a[] = {370,417,408,156,143,434,168,83,177,280,117};
  vector<int> coins(a, end(a));
  cout<<coinChange(coins, 9953)<<endl;
  return 0;
}
