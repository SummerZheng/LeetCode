#include<iostream>
#include<vector>
#include<random>
#include"print.h"

using namespace std;

int construct_DP_bottom_up(vector<vector<int> >& matrix) {
  int max_size = 0;
  int R = matrix.size(), C = matrix[0].size();
  vector<vector<int> > DPmat(R+1, vector<int>(C+1, 0));
  for (int i = 1; i <= R; ++i) {
    for (int j = 1; j <= C; ++j) {
      DPmat[i][j] = matrix[i-1][j-1] ? min(DPmat[i-1][j-1], min(DPmat[i-1][j], DPmat[i][j-1])) + 1 : 0;
      if (DPmat[i][j] > max_size)
        max_size = DPmat[i][j];
    }
  }
  return max_size * max_size;
}

int maximalSquare(vector<vector<int> >& matrix) {
  if (matrix.empty()) return 0;
  return construct_DP_bottom_up(matrix);
}



int main() {
  int R = 5, C = 4;
  vector<vector<int> > matrix(R, vector<int>(C, 0));
  std::default_random_engine generator(10);
  std::bernoulli_distribution distribution(0.8);
  for (int i = 0; i != R; ++i) {
    for (int j = 0; j != C; ++j) {
      matrix[i][j] = distribution(generator); 
    }
  }
  print(matrix);
  cout<<maximalSquare(matrix)<<endl;
  return 0;
}
