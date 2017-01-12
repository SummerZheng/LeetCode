#include"print.h"

using namespace std;

int calculateMinimumHP(vector<vector<int> >& dungeon) {
  if (dungeon.empty()) return 1;
  int row = dungeon.size(), col = dungeon[0].size();
  matrix<int> min_health_dp(row, vector<int>(col, 0));
  min_health_dp[row-1][col-1] = max(1, 1 - dungeon[row-1][col-1]);
  for (int j = col - 2; j >= 0; --j) {
    min_health_dp[row - 1][j] = max(1, min_health_dp[row - 1][j + 1] - dungeon[row - 1][j]);
  }
  for (int i = row - 2; i >= 0; --i) {
    min_health_dp[i][col - 1] = max(1, min_health_dp[i + 1][col - 1] - dungeon[i][col - 1]);
  }
  for (int i = row - 2; i >= 0; --i) {
    for (int j = col - 2; j >= 0; --j) {
      min_health_dp[i][j] = max(1, min(min_health_dp[i + 1][j], min_health_dp[i][j+1]) - dungeon[i][j]);
    }
  }
  cout<<"min_health_dp is:"<<endl;
  print(min_health_dp);
  return min_health_dp[0][0];
}


int main() {
  const int R = 3, C = 3;
  int a[R][C] = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
  matrix<int> dungeon(R, vector<int>(C));
  for (int r = 0; r != R; ++r) {
    for (int c = 0; c != C; ++c) {
      dungeon[r][c] = a[r][c];
    }
  }
  cout<<"dungeon is:"<<endl;
  print(dungeon);
  cout<<"min heath needed is "<<calculateMinimumHP(dungeon)<<endl;
  return 0;
}
