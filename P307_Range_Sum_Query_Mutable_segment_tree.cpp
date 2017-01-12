#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

// Segment tree 82ms
class NumArray {
  public:
    NumArray(vector<int> &nums):N(nums.size()) {
      if (N) {
        int capacity = 1;
        while (capacity <  N) {
          capacity <<= 1;
        }
        segment_tree = vector<int>(capacity * 2 - 1, 0);
        construct_segment_util(nums, 0, N-1, 0);
        cout<<"the segment tree is: "<<endl;
        print(segment_tree);
      }
    }

    void update(int i, int val) {
      update_util(0, 0, N-1, i, val);
    }

    int sumRange(int i, int j) {
      return sumRange_util(0, 0, N-1, i, j);
    }

  private:
    int N;
    vector<int> segment_tree;
    int construct_segment_util(vector<int>& nums, int istart, int iend, int iseg);
    int sumRange_util(int iseg, int istart, int iend, int i, int j);
    int update_util(int iseg, int istart, int iend, int i, int val);
    inline int get_mid (int i, int j)  {return (i + j)>>1;}
    inline int left_child (int i)  {return (i<<1) + 1;}
    inline int right_child(int i)  {return (i<<1) + 2;}
    inline bool intersect(int i1_left, int i1_right, int i2_left, int i2_right) {
      return (i1_left > i2_right || i1_right < i2_left)  ? false: true;}
    inline bool inclusive(int i1_left, int i1_right, int i2_left, int i2_right) {
      return (i1_left >= i2_left && i1_right <= i2_right)? true: false;}
};

int NumArray::construct_segment_util(vector<int>& nums, int istart, int iend, int iseg) {
  // cout<<"istart "<<istart<<", iend "<<iend<<", iseg "<<iseg<<endl;
  if (istart == iend) {
    segment_tree[iseg] = nums[istart];
  } else {
    int imid = get_mid(istart, iend);
    segment_tree[iseg] = construct_segment_util(nums, istart, imid, left_child(iseg)) +
                         construct_segment_util(nums, imid+1, iend, right_child(iseg));
  }
  return segment_tree[iseg];
}

int NumArray::sumRange_util(int iseg, int istart, int iend, int i, int j) {
  // cout<<"iseg "<<iseg<<", istart "<<istart<<", iend "<<iend<<", i "<<i<<", j "<<j<<endl;
  if (intersect(istart, iend, i, j)) {
    if (inclusive(istart, iend, i, j)) {
      return segment_tree[iseg];
    } else {
      int imid = get_mid(istart, iend);
      return sumRange_util(left_child(iseg), istart, imid, i, j) + sumRange_util(right_child(iseg), imid+1, iend, i, j);
    }
  } else {
    return 0;
  }
}

int NumArray::update_util(int iseg, int istart, int iend, int i, int val){
  int diff;
  if (istart != iend) {
    int imid = get_mid(istart, iend);
    if (i <= imid)
      diff = update_util(left_child(iseg), istart, imid, i, val);
    else
      diff = update_util(right_child(iseg), imid+1, iend, i, val);
  } else {
    // This assumes istart == iend == i
      diff = val - segment_tree[iseg];
  }
  segment_tree[iseg] += diff;
  return diff;
}

int main() {
  // Your NumArray object will be instantiated and called as such:
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
