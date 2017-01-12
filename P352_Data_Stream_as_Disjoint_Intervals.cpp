#include<iostream>
#include<vector>
#include<set>
#include<random>

using namespace std;

// Definition for an interval.
struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

struct classcomp {
  bool operator() (const Interval& lhs, const Interval& rhs) const
  {return lhs.start < rhs.start;}
};

// Method 2, use STL set
class SummaryRanges {
  public:
    /** Initialize your data structure here. */
    SummaryRanges(){ }
    void addNum(int val) {
      int istart = val, iend = val;
      set<Interval, classcomp>::iterator iter = BST_interval.lower_bound(Interval(istart, iend));
      // merge with successor if possible
      if (iter != BST_interval.end()) {
        if (val == iter->start) {
          return;
        } else if (val + 1 == iter->start) {
          iend = iter->end;
          iter = BST_interval.erase(iter);
        }
      }
      // merge with predecessor if mergable
      if (iter != BST_interval.begin() && (--iter)->end + 1 >= istart) {
        if (iend <= iter->end) return;
        istart = iter->start;
        iter = BST_interval.erase(iter);
      }
      BST_interval.insert(iter, Interval(istart, iend));
    }
    vector<Interval> getIntervals() {
      vector<Interval> trail;
      for (auto itv : BST_interval) {
        trail.push_back(itv);
      }
      return trail;
    }
  private:
    set<Interval, classcomp> BST_interval;
};

// Method 1, self code BST, with TreeNode as Interval, and key as Interval.start, incomplete
struct Interval_TNode {
  Interval_TNode():itv(), left(nullptr), right(nullptr){}
  Interval_TNode(int s, int e):itv(s, e), left(nullptr), right(nullptr){}
  Interval itv;
  Interval_TNode* left;
  Interval_TNode* right;
};

bool mergable_from_right(int val, Interval& itv) {
  return (itv.end + 1 == val)? true : false;
}
bool mergable_from_left(int val, Interval& itv) {
  return (val + 1 == itv.start)? true : false;
}
bool mergable(Interval& i1, Interval& i2) {
  if (i1.end + 1 < i2.start || i2.end + 1 < i1.start)
    return false;
  return true;
}
bool inside_interval(int val, Interval& itv) {
  if (val <= itv.end && val >= itv.start)
    return true;
  return false;
}
void merge_interval(int val, Interval& itv) {
  itv.start = min(val, itv.start);
  itv.end = max(val, itv.end);
}
bool merge_contiguous_tnode(Interval_TNode* p, Interval_TNode* c){
  if (!p || !c) return false;
  if (p->itv.end + 1 == c->itv.start) {
    p->itv.end = c->itv.end;
    p->right = c->right;
    delete(c);
    return true;
  } else if (p->itv.start == c->itv.end + 1){
    p->itv.start = c->itv.start;
    p->left = c->left;
    delete(c);
    return true;
  } else {
    return false;
  }
}

/** class SummaryRanges {
 *   public:
 *     SummaryRanges():root(nullptr){ }
 *
 *     void addNum(int val) {
 *       Interval_TNode *p = nullptr, *cur = root;
 *       while (cur) {
 *         if (inside_interval(val, cur->itv)) return;
 *         if (mergable_from_right(val, cur->itv)) {
 *           // cout<<val<<" is mergable from right for ("<<cur->itv.start<<", "<<cur->itv.end<<")"<<endl;
 *           cur->itv.end = val;
 *           // merge with cur->successor if mergable
 *           if (cur->right) { // cur->successor is the min Child of its right subtree
 *             Interval_TNode *successor_child = cur->right, *pchild = cur;
 *             while (successor_child && successor_child->left) {
 *               pchild = successor_child;
 *               successor_child = successor_child->left;
 *             }
 *             if (successor_child && mergable(cur->itv, successor_child->itv)) {
 *               if (successor_child == cur->right) {
 *                 merge_contiguous_tnode(cur, successor_child);
 *               } else {
 *                 if (successor_child->right) {
 *                   pchild->left = successor_child->right;
 *                 } else {
 *                   pchild->left = nullptr;
 *                 }
 *                 cur->itv.end = successor_child->itv.end;
 *                 delete(successor_child);
 *               }
 *             }
 *           } else { // cur->successor is it's first right parent
 *             Interval_TNode *rightP = nullptr, *parent = nullptr, *ptrC = root;
 *             while (ptrC != cur ) {
 *               parent = ptrC;
 *               if (ptrC->itv.start >= cur->itv.start) {
 *                 rightP = ptrC;
 *                 ptrC = ptrC->left;
 *               } else {
 *                 ptrC = ptrC->right;
 *               }
 *             }
 *             // TODO: need to delete the right parent, and insert the merged interval
 *             if (rightP) {
 *               rightP->itv.start;
 *             }
 *             if (p && p->left == cur && mergable(p->itv, cur->itv)) {
 *               merge_contiguous_tnode(p, cur);
 *             }
 *           }
 *           return;
 *         }
 *         if (mergable_from_left(val, cur->itv)) {
 *           // cout<<val<<" is mergable from right for ("<<cur->itv.start<<", "<<cur->itv.end<<")"<<endl;
 *           cur->itv.start = val;
 *           if (p && p->right == cur && mergable(p->itv, cur->itv)) {
 *             merge_contiguous_tnode(p, cur);
 *           } else {
 *             Interval_TNode *predecessor_child = cur->left, *pchild = cur;
 *             while (predecessor_child && predecessor_child->right) {
 *               pchild = predecessor_child;
 *               predecessor_child = predecessor_child->right;
 *             }
 *             if (predecessor_child && mergable(cur->itv, predecessor_child->itv)) {
 *               if (predecessor_child == cur->left) {
 *                 merge_contiguous_tnode(cur, predecessor_child);
 *               } else {
 *                 if (predecessor_child->left) {
 *                   pchild->right = predecessor_child->left;
 *                 } else {
 *                   pchild->right = nullptr;
 *                 }
 *                 cur->itv.start = predecessor_child->itv.start;
 *                 delete(predecessor_child);
 *               }
 *             }
 *           }
 *           return;
 *         }
 *         p = cur;
 *         if (val <  cur->itv.start) {
 *           cur = cur->left;
 *         } else if (val > cur->itv.end) {
 *           cur = cur->right;
 *         }
 *       }
 *       if (!p) {
 *         root = new Interval_TNode(val, val);
 *       } else {
 *         cur = new Interval_TNode(val, val);
 *         if (p->itv.start > val)
 *           p->left = cur;
 *         else
 *           p->right = cur;
 *       }
 *     }
 *
 *     vector<Interval> getIntervals() {
 *       vector<Interval> trail;
 *       getIntervals_util(trail, root);
 *       return trail;
 *     }
 *
 *   private:
 *     Interval_TNode* root;
 *     void getIntervals_util(vector<Interval>& trail, Interval_TNode* p) {
 *       if (!p) return;
 *       // Pre-order tree walk to return Intervals from low to high in order
 *       getIntervals_util(trail, p->left);
 *       trail.push_back(Interval(p->itv.start, p->itv.end));
 *       getIntervals_util(trail, p->right);
 *     }
 * }; **/

void print(vector<Interval>& vec) {
  for (auto itv : vec) {
    cout<<"["<<itv.start<<", "<<itv.end<<"]"<<endl;
  }
  cout<<endl;
}

int main() {
  SummaryRanges obj;
  // int a[] = {1, 3, 7, 2, 6};
  // int a[] = {1, 9, 2};
  int a[] = {6, 6, 0, 4, 8, 7, 6, 4, 7, 5};
  vector<int> vec(a, end(a));
  for (int i = 0; i != vec.size(); ++i) {
    cout<<"inserting "<<vec[i]<<" into interval tree"<<endl;
    obj.addNum(vec[i]);
  // std::default_random_engine generator(0);
  // std::uniform_int_distribution<int> distribution(1,100);
  // for (int i = 0; i != 40; ++i) {
  //   int num = distribution(generator);
  //   cout<<"inserting "<<num<<" into interval tree"<<endl;
  //   obj.addNum(num);
    vector<Interval> param_2 = obj.getIntervals();
    print(param_2);
  }
  return 0;
}
