#include<iostream>
#include<vector>
#include"print.h"

using namespace std;

// Method1 Order Statistic Tree
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
    int OS_insert(int val){
      OStreeNode *p = nullptr, *cur = root;
      int rank = 0;
      while (cur) {
        ++cur->size;
        p = cur;
        if (val <= cur->key) {
          cur = cur->left;
        } else {
          rank += getSize(cur->left) + 1;
          cur = cur->right;
        }
      }
      if (p == nullptr) {
        root = new OStreeNode(val);
      } else {
        cur = new OStreeNode(val);
        if (p->key < val) {
          p->right = cur;
        } else {
          p->left = cur;
        }
      }
      return rank;
    }
  private:
    OStreeNode* root;
    inline int getSize(OStreeNode* t) { return t?t->size:0; }
};

vector<int> countSmaller_OS(vector<int>& nums) {
  OStree myTree;
  vector<int> ctVec(nums.size(), 0);
  for (int i = nums.size()-1; i>=0; --i) {
    ctVec[i] = myTree.OS_insert(nums[i]);
  }
  return ctVec;
}

// TODO: Method 2 merge sort
static bool myComp(const pair<int, int>& p1, const pair<int, int>& p2) {
  return p1.first > p2.first ? true : false;
}

void countSmaller(vector<int>& smallerCount, vector<pair<int, int>>& nums, int istart, int iend) {
  if (istart + 1 >= iend) return;
  int imid = istart + (iend - istart)/2;
  countSmaller(smallerCount, nums, istart, imid);
  countSmaller(smallerCount, nums, imid, iend);
  for (int i = imid-1, j = iend - 1; i >= istart && j >= imid; --i) {
    while (j >= imid && nums[j] < nums[i]) --j;
    smallerCount[i] += iend - j - 1;
  }
  std::inplace_merge(nums.begin()+istart, nums.begin()+imid, nums.begin()+iend, myComp);
}

vector<int> countSmaller(vector<int>& nums) {
  vector<int> smallerCount(nums.size(), 0);
  vector<pair<int, int>> sorted_num_with_idx;
  for (int i = 0; i != nums.size(); ++i) {
    sorted_num_with_idx.push_back(make_pair(nums[i], i));
  }
  countSmaller(smallerCount, sorted_num_with_idx, 0, nums.size());
  vector<int> smallerCount_order_restored(nums.size(), 0);
  print(sorted_num_with_idx);
  print(smallerCount);
  for (int i = 0; i != nums.size(); ++i) {
    int ix = sorted_num_with_idx[i].second;
    smallerCount_order_restored[ix] = smallerCount[i];
  }
  return smallerCount_order_restored;
}

int main() {
  // int a[] = {5, 2, 6, 1, 1};
  int a[] = {1, 9, 7, 8, 5};
  vector<int> vec(a, end(a));
  print(vec);
  print(countSmaller(vec));
  return 0;
}
