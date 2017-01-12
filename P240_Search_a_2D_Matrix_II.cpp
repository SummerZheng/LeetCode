#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

bool searchMatrix(vector<vector<int>>& matrix, int target) {
  if (matrix.empty()) return false;
  int Row = matrix.size(), Col = matrix[0].size();
  int r = 0, c = matrix[0].size()-1;
  while (r != Row && c >= 0) {
    if (matrix[r][c] == target) {
      return true;
    } else if (matrix[r][c] < target) {
      ++r;
    } else {
      --c;
    }
  }
  return false;
}

int main() {
  const int R = 5, C = 5;
  int a[][C] = {
    {1,   4,  7, 11, 15},
    {2,   5,  8, 12, 19},
    {3,   6,  9, 16, 22},
    {10, 13, 14, 17, 24},
    {18, 21, 23, 26, 30}
  };
  vector<vector<int> > mat(R, vector<int>(C));
  for (int i = 0; i != R; ++i) {
    for (int j = 0; j != C; ++j) {
      mat[i][j] = a[i][j];
    }
  }
  cout<<"the input matrix is:"<<endl;
  print(mat);
  int t1 = 3, t2 = 25;
  cout<<"search for target "<<t1<<endl;
  cout<<searchMatrix(mat, t1)<<endl;
  cout<<"search for target "<<t2<<endl;
  cout<<searchMatrix(mat, t2)<<endl;
  return 0;
}
