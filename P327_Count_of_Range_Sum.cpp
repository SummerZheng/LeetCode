#include<iostream>
#include<vector>
#include<algorithm>
#include"print.h"

using namespace std;

// Method 1 Order Statistic Tree 109ms
struct OStreeNode{
  OStreeNode(int _key = INT_MIN, int _size = 1):key(_key), size(_size), left(nullptr), right(nullptr){}
  int key;
  int size;
  OStreeNode* left;
  OStreeNode* right;
};

class OStree{
  public:
    OStree():root(nullptr){}
    void OS_insert(int val){
      OStreeNode *p = nullptr, *cur = root;
      while (cur) {
        ++cur->size;
        p = cur;
        if (val <= cur->key) {
          cur = cur->left;
        } else {
          cur = cur->right;
        }
      }
      if (p == nullptr) {
        root = new OStreeNode(val);
      } else {
        cur = new OStreeNode(val);
        if (val <= p->key) {
          p->left = cur;
        } else {
          p->right = cur;
        }
      }
    }
    int rank(long target) {
      OStreeNode *cur = root;
      int rank = 0;
      while (cur) {
        if (target < cur->key) {
          cur = cur->left;
        } else {
          rank += getSize(cur->left) + 1;
          if (cur->key == target)
            break;
          cur = cur->right;
        }
      }
      return rank;
    }
    void print() {
      cout<<"print out cumsum tree :"<<endl;
      print(root);
      cout<<endl;
    }
    void print(OStreeNode* p) {
      if (p) {
        print(p->left);
        cout<<p->key<<", ";
        print(p->right);
      }
    }
  private:
    OStreeNode* root;
    inline int getSize(OStreeNode* t) { return t?t->size:0; }
};

int countRangeSum_OS(vector<int>& nums, int lower, int upper) {
  OStree myTree;
  long sum = 0, ct = 0;
  myTree.OS_insert(sum);
  for (int i = 0; i != nums.size(); ++i) {
    sum += nums[i];
    cout<<"looking for sum between ["<<sum-upper-1<<", "<<sum-lower<<"]"<<endl;
    int delta = myTree.rank(sum - lower) - myTree.rank(sum - upper-1);
    cout<<delta<<" number of pairs satisfy bound ending at ix "<<i<<endl;
    ct += delta;
    myTree.OS_insert(sum);
  }
  myTree.print();
  for (int n = -3; n != 4; ++n) {
    cout<<"the rank for n = "<<n<<" is "<<myTree.rank(n)<<endl;
  }
  return ct;
}

// Method 2, MergeSort 53ms
// Refered to the awesome post here: https://discuss.leetcode.com/topic/45522/c-merge-sort-solution-very-short
int countRangeSum_util(vector<int>& sums, int lower, int upper, int istart, int iend) {
  if (istart + 1 >= iend) return 0;
  int imid = istart + (iend - istart)/2, ct = 0, uix = imid, lix = imid;
  ct = countRangeSum_util(sums, lower, upper, istart, imid) + countRangeSum_util(sums, lower, upper, imid, iend);
  for (int i = istart; i < imid; ++i) {
    while (uix < iend && sums[uix] - sums[i] <= upper) ++uix;
    while (lix < iend && sums[lix] - sums[i] <  lower) ++lix;
    // cout<<"uix is "<<uix<<", lix is "<<lix<<", i is "<<i<<endl;
    ct += uix - lix;
  }
  std::inplace_merge(sums.begin()+istart, sums.begin()+imid, sums.begin()+iend);
  // cout<<"ct between ["<<istart<<", "<<iend<<") is "<<ct<<endl;
  return ct;
}

int countRangeSum(vector<int>& nums, int lower, int upper) {
  vector<int> cumSum(nums.size()+1, 0);
  for (int i = 0; i != nums.size(); ++i) {
    cumSum[i+1] = cumSum[i] + nums[i];
  }
  return countRangeSum_util(cumSum, lower, upper, 0, nums.size()+1);
}

int main() {
  // int a[] = {2147483647,-2147483648,-1,0};
  int a[] = {-2, 5, -1};
  vector<int> vec(a, end(a));
  print(vec);
  cout<<countRangeSum(vec, -2, 2)<<endl;
  return 0;
}
