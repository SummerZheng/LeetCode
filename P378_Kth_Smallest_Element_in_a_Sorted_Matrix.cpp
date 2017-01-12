#include<iostream>
#include<vector>
#include<queue>
#include"print.h"

using namespace std;

#define SIZE 3

// Method 1. Binary Search O(n * log(max-min)) ~ O(n)
// Refer to P240. Search a 2D Matrix II for inner O(n) search
int kthSmallest(vector<vector<int>>& matrix, int k) {
  int n = matrix.size();

  int left = matrix[0][0];
  int right = matrix[n-1][n-1];

  while (left < right) {
    int midv = (left + right) / 2;
    int count = 0;  // number of elements no bigger than midv
    int r = 0, c = n-1;
    while (r != n && c >= 0) {
      if (matrix[r][c] > midv) {
        --c;
      } else {
        count += c+1;
        ++r;
      }
    }
    if (count < k) {
      left = midv + 1;
    } else {
      right = midv;
    }
  }
  return left;
}

// Method 2. Min Heap, O(k * log(n))
// Refer to P 373. Find K Pairs with Smallest Sums
struct myEle{
  myEle(){}
  myEle(int _num, int _row, int _col):num(_num), row(_row), col(_col){}
  int num;
  int row;
  int col;
};

class myComp{
  public:
    bool operator()(const myEle& n1, const myEle& n2) {return n1.num > n2.num;}
};

int kthSmallest_minHeap(vector<vector<int> >& matrix, int k) {
  int N = matrix.size();
  priority_queue<myEle, std::vector<myEle>, myComp> myPQ;
  for (int c = 0; c != matrix.size(); ++c) {
    myPQ.push(myEle(matrix[0][c], 0, c));
  }
  myEle minEle = myPQ.top();
  while (k--) {
    minEle = myPQ.top();
    cout<<"cur min is "<<minEle.num<<endl;
    myPQ.pop();
    if (minEle.row != N-1) {
      myPQ.push(myEle(matrix[minEle.row+1][minEle.col], minEle.row+1, minEle.col));
    }
  }
  return minEle.num;
}

int main(){
  int matrix[SIZE][SIZE] = {
    {1, 3, 5},
    {6, 7, 12},
    {11, 14, 14}
  };
  vector<vector<int> > mat(SIZE, vector<int>(SIZE));
  for (int i = 0; i != SIZE; i++) {
    for (int j = 0; j != SIZE; j++) {
      mat[i][j] = matrix[i][j];
    }
  }
  print(mat);
  int k = 6;
  cout<<"the "<<k<<"th smallest ele is:"<<endl;
  cout<<kthSmallest(mat, k)<<endl;
  return 0;
}
