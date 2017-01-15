#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>

using namespace std;

typedef pair<int, int> myPair;

const int special_val = -10;

int minExchange_DP_topdown(int amount, int max_ix, vector<vector<int> >& DPmat, vector<int>& coins) {
  if (amount < 0 || max_ix < 0) return -1;
  if (DPmat[amount][max_ix] == special_val) {
    if (amount < coins[0]) {
      DPmat[amount][max_ix] = amount ? -1 : 0;
    } else {
      int n1 = minExchange_DP_topdown(amount, max_ix - 1, DPmat, coins);
      int n2 = minExchange_DP_topdown(amount - coins[max_ix], max_ix, DPmat, coins);
      if (n1 == -1) { 
        DPmat[amount][max_ix] = (n2 == -1)? -1 : n2+1;
      } else {
        DPmat[amount][max_ix] = (n2 == -1)? n1 : min(n1, n2+1);
      }
    } 
  }
  return DPmat[amount][max_ix];
}

// int coinChange(vector<int>& coins, int amount) {
//   if (coins.empty()) return -1;
//   // sort(coins.begin(), coins.end());
//   // vector<vector<int> > minExchange(amount+1, vector<int>(coins.size(), special_val));
//   // return minExchange_DP_topdown(amount, coins.size()-1, minExchange, coins);
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

int coinChange(vector<int>& coins, int amount) {
  const int max_int = numeric_limits<int>::max();
  vector<int> minEx(amount+1, max_int); 
  minEx[0] = 0;
  for (int m = 0; m <= amount; ++m) {
    for (int i = 0; i != coins.size(); ++i) {
      if (m - coins[i] >= 0 && minEx[m-coins[i]] != max_int) {
        minEx[m] = min(minEx[m], minEx[m-coins[i]] + 1); 
      }
    }
  }
  return minEx[amount] == max_int? -1: minEx[amount];
}
int main() {
  int a[] = {370,417,408,156,143,434,168,83,177,280,117};
  vector<int> coins(a, end(a));
  cout<<coinChange(coins, 9953)<<endl;
  return 0;
}
