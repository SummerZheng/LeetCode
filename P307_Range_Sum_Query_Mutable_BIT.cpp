#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

// Binary Indexed Tree 63ms
class NumArray {
  public:
    NumArray(vector<int> &nums):N(nums.size()), BITree(N+1, 0){
      for (int i = 0; i != nums.size(); ++i)
        update(i, nums[i]);
      cout<<"the BITree is"<<endl;
      print(BITree);
    }

    void update(int i, int val) {
      // cout<<"update idx "<<i<<" with val "<<val<<endl;
      int diff = val - sumRange(i, i);
      // cout<<"diff is "<<diff<<endl;
      i += 1;
      while (i <= N) {
        BITree[i] += diff;
        i += getLastDigit1(i);
      }
      // print(BITree);
      // cout<<"update finished for idx "<<endl;
    }

    int sumRange(int i, int j) {
      return cumSum(j+1) - cumSum(i);
    }

    int cumSum(int i) {
      int sum = 0;
      while (i) {
        sum += BITree[i];
        i -= getLastDigit1(i);
      }
      return sum;
    }

  private:
    int N;
    vector<int> BITree;
    inline int getLastDigit1(int ix) { return ix & (-ix); }
};

int main() {
  // Your NumArray object will be instantiated and called as such:
  // int a[] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
  int a[] = {-28,-39,53,65,11,-56,-65,-39,-43,97};
  vector<int> nums(a, end(a));
  cout<<"the vector is :"<<endl;
  print(nums);
  NumArray numArray(nums);
  cout<<numArray.sumRange(5,6)<<endl;
  numArray.update(9,27);
  cout<<numArray.sumRange(2,3)<<endl;
  cout<<numArray.sumRange(6,7)<<endl;
  numArray.update(1,-82);
  numArray.update(3,-72);
  cout<<numArray.sumRange(3,7)<<endl;
  cout<<numArray.sumRange(1,8)<<endl;
  numArray.update(5,13);
  numArray.update(4,-67);
  cout<<numArray.sumRange(0, 9)<<endl;
  return 0;
}
