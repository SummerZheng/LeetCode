#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

class NumMatrix {
  public:
    NumMatrix(vector<vector<int>> &matrix) {
      if (!matrix.empty()) {
        int R = matrix.size(), C = matrix[0].size(); 
        DPmat = vector<vector<int>>(R+1, vector<int>(C+1, 0));
        for (int r = 1; r <= R; ++r) {
          for (int c = 1; c <= C; ++c) {
            DPmat[r][c] = DPmat[r-1][c] + DPmat[r][c-1] - DPmat[r-1][c-1] + matrix[r-1][c-1];
          }
        }
      }
      cout<<"CumSum matrix is: "<<endl;
      print(DPmat);
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
      if (DPmat.empty()) return 0;
      cout<<DPmat[row2+1][col2+1]<<" - "<<DPmat[row1][col2+1]<<" - "<<DPmat[row2+1][col2]<<" + "<<DPmat[row1][col1]<<endl;
      return DPmat[row2+1][col2+1] - DPmat[row1][col2+1] - DPmat[row2+1][col1] + DPmat[row1][col1];
    }
 
  private:
    vector<vector<int> > DPmat;
};

int main() {
  const int R = 5, C = 5; 
  int a[][C] = {
     {3, 0, 1, 4, 2},
     {5, 6, 3, 2, 1},
     {1, 2, 0, 1, 5},
     {4, 1, 0, 1, 7},
     {1, 0, 3, 0, 5}
   };
   vector<vector<int> > mat(R, vector<int>(C));
   for (int i = 0; i != R; ++i) {
     for (int j = 0; j != C; ++j) {
       mat[i][j] = a[i][j];
     }
   }
   cout<<"Input matrix is: "<<endl;
   print(mat);
   NumMatrix testMat(mat);
   cout<<testMat.sumRegion(2, 1, 4, 3)<<endl;
   cout<<testMat.sumRegion(1, 1, 2, 2)<<endl;
   cout<<testMat.sumRegion(1, 2, 2, 4)<<endl;
   return 0;
}
