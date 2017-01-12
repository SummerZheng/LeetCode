#include<iostream>
#include<vector>
#include<random>
#include"print.h"

using namespace std;

// One method is refer to P84. Largest Rectangle in Histogram
// Calculate the maximum height for each row
// And use stack to calculate the maximum rectangle for each row
// The time complexity is O(M * N)

// Another more inherent DP way is refer to https://discuss.leetcode.com/topic/6650/share-my-dp-solution/2
// We still calculate the maximum height for each row
// We also record what's the most left and right extendable index for the maximum height
// And compute the max Area from max(ht * (right_most - left_most))
int construct_DP_bottom_up(vector<vector<char> >& matrix) {
  int max_size = 0, area_with_ht;
  int R = matrix.size(), C = matrix[0].size();
  vector<int> left(C, 0), right(C, C), height(C, 0);
  for (int i = 0; i != R; ++i) {
    int left_ix = 0, right_ix = C;
    for (int j = 0; j != C; ++j) {
      height[j] = matrix[i][j] == '1' ? height[j] + 1: 0;
    }
    for (int j = 0; j != C; ++j) {
      if (matrix[i][j] == '1') {
        left[j] = max(left[j], left_ix);
      } else {
        left[j] = 0; left_ix = j + 1;
      }
    }
    for (int j = C-1; j >= 0; --j) {
      if (matrix[i][j] == '1') {
        right[j] = min(right[j], right_ix);
      } else {
        right[j] = C; right_ix = j;
      }
    }
    for (int j = 0; j != C; ++j) {
      area_with_ht = height[j] * (right[j] - left[j]);
      if (area_with_ht > max_size)
        max_size = area_with_ht;      
    }
    cout<<"For row "<<i<<endl;
    cout<<"left  ix vec is : ";
    print(left);
    cout<<"right ix vec is : ";
    print(right);
    cout<<"height vec is   : ";
    print(height);
  }
  return max_size;
}

int maximalSquare(vector<vector<char> >& matrix) {
  if (matrix.empty()) return 0;
  return construct_DP_bottom_up(matrix);
}



int main() {
  int R = 5, C = 4;
  vector<vector<char> > matrix(R, vector<char>(C, 0));
  std::default_random_engine generator(10);
  std::bernoulli_distribution distribution(0.8);
  for (int i = 0; i != R; ++i) {
    for (int j = 0; j != C; ++j) {
      matrix[i][j] = static_cast<char>('0' + distribution(generator)); 
    }
  }
  print(matrix);
  cout<<maximalSquare(matrix)<<endl;
  return 0;
}
