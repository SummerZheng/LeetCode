#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

int DFS(int i, int j, vector<vector<int>>& DPmat, vector<vector<int>>& matrix) {
  if (DPmat[i][j] == -1) {
    DPmat[i][j] = 1;
    if (i > 0 && matrix[i][j] < matrix[i-1][j])
      DPmat[i][j] = max(DPmat[i][j], 1 + DFS(i-1, j, DPmat, matrix));
    if (i < matrix.size()-1 && matrix[i][j] < matrix[i+1][j])
      DPmat[i][j] = max(DPmat[i][j], 1 + DFS(i+1, j, DPmat, matrix));
    if (j > 0 && matrix[i][j] < matrix[i][j-1])
      DPmat[i][j] = max(DPmat[i][j], 1 + DFS(i, j-1, DPmat, matrix));
    if (j < matrix[0].size()-1 && matrix[i][j] < matrix[i][j+1])
      DPmat[i][j] = max(DPmat[i][j], 1 + DFS(i, j+1, DPmat, matrix));
  }
  return DPmat[i][j];
}

int longestIncreasingPath(vector<vector<int> >& matrix) {
  if (matrix.size() == 0) return 0;
  int R = matrix.size(), C = matrix[0].size();
  vector<vector<int>> DPmat(R, vector<int>(C, -1));
  int max_len = 0, cur_len;
  for (int r = 0; r != R; ++r) {
    for (int c = 0; c != C; ++c) {
      cur_len = DFS(r, c, DPmat, matrix);
      max_len = max(max_len, cur_len);
    }
  }
  return max_len;
}

template <size_t R, size_t C>
vector<vector<int> > convert_2dArray_to_matrix(int (&arr)[R][C]) {
  vector<vector<int> > matrix(R, vector<int>(C, 0));
  for (int i = 0; i != R; i++) {
    for (int j = 0; j != C; j++) {
      matrix[i][j] = arr[i][j];
    }
  }
  return matrix;
}

int main() {
  //int a[2][2] = {{1, 2}, {2, 3}};
  int a[4][4] = {{1, 4, 7, 9},
                 {0, 3, 8, 5},
                 {3, 6, 0, 6},
                 {1, 4, 5, 6}};
  vector<vector<int> > mat = convert_2dArray_to_matrix(a);  
  print(mat);
  cout<<longestIncreasingPath(mat)<<endl;
  return 0;
}
