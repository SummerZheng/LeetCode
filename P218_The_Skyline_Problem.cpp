#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
#include<sstream>
#include<regex>
#include<set>
#include"print.h"

using namespace std;

// Method 1 Self implemented maxChild BSTree
// refered to interval tree of CLRS, augment tree node t with cMax (child max)
// which stores the largest key in the subtree rooted at t
struct TNode {
  TNode(){}
  TNode(int _key):key(_key), cMax(_key), left(nullptr), right(nullptr), parent(nullptr){}
  TNode(int _key, int _cMax):key(_key), cMax(_cMax), left(nullptr), right(nullptr), parent(nullptr){}
  int key;
  int cMax;
  TNode* left;
  TNode* right;
  TNode* parent;
};

class MaxChild_Tree {
  public:
    MaxChild_Tree():root(nullptr){}
    void insert(int val) {
      cout<<"insert node "<<val<<endl;
      TNode *p = nullptr, *cur = root;
      while (cur) {
        p = cur;
        if (val <= cur->key) {
          cur = cur->left;
        } else {
          cur->cMax = max(cur->cMax, val);
          cur = cur->right;
        }
      }
      cur = new TNode(val);
      cur->parent = p;
      if (!p) {
        root = cur;
      } else if (val <= p->key){
        p->left = cur;
      } else {
        p->right = cur;
      }
    }
    bool delete_node(int val) {
      cout<<"delete node "<<val<<endl;
      TNode *p = nullptr, *target = root;
      while (target && target->key != val) {
        p = target;
        if (val < target->key) {
          target = target->left;
        } else {
          target = target->right;
        }
      }
      if (!target) return false;
      if (!target->left) {
        transplant(target, target->right);
      } else if (!target->right) {
        transplant(target, target->left);
      } else {
        TNode* successor = find_successor_child(target);
        if (successor != target->right) {
          transplant(successor, successor->right, false);
          successor->right = target->right;
          target->right->parent = successor;
          successor->cMax = getMax(successor->right);
        }
        successor->left = target->left;
        target->left->parent = successor;
        transplant(target, successor);
      }
      while (p) {
        if (p->cMax != max(p->key, getMax(p->right))) {
          p->cMax = max(p->key, getMax(p->right));
          p = p->parent;
        } else {
          break;
        }
      }
      return true;
    }

    int getMax() { return getMax(root); }
    void print() {
      cout<<"print tree"<<endl;
      print(root);
    }
  private:
    TNode* root;
    int getMax(TNode* t) { return t? t->cMax : 0; }
    void transplant(TNode *t1, TNode *t2, bool delete_after_transplant = true) {
      if (!t1->parent) {
        root = t2;
      } else if (t1->parent->left == t1) {
          t1->parent->left = t2;
      } else {
          t1->parent->right = t2;
      }
      if (t2) t2->parent = t1->parent;
      if (delete_after_transplant) delete(t1);
    }
    TNode* find_successor_child(TNode* t) {
       t = t->right;
       while (t->left && t->left->left) {
         t = t->left;
       }
       return t->left? t->left: t;
    }
    void print(TNode* t) {
      if (!t) return;
      cout<<"TNode "<<t->key<<" with Max Child Value "<<t->cMax<<endl;
      print(t->left);
      print(t->right);
    }
};

void update_skyline(MaxChild_Tree& myTree, vector<pair<int, int>>& skyline, int& curMax, int curX) {
  if (myTree.getMax() != curMax) {
    curMax = myTree.getMax();
    if (!skyline.empty() && curX == skyline.back().first) {
      skyline.pop_back();
    }
    skyline.push_back(make_pair(curX, curMax));
  }
}

bool myComp(const pair<int, int>& p1, const pair<int, int>& p2) {
  return p1.first < p2.first? true : false;
}

vector<pair<int, int>> getSkyline_myTree(vector<vector<int>>& buildings) {
  vector<pair<int, int>> highEnds;
  int N = buildings.size();
  for (int i = 0; i != N; ++i) {
    highEnds.push_back(make_pair(buildings[i][1], i));
  }
  sort(highEnds.begin(), highEnds.end(), myComp);
  vector<pair<int, int>> skyline;
  MaxChild_Tree myTree;
  int lix = 0, hix = 0, curMax = 0;
  while (lix != N || hix != N) {
    while (lix != N && buildings[lix][0] <= highEnds[hix].first) {
      myTree.insert(buildings[lix][2]);
      update_skyline(myTree, skyline, curMax, buildings[lix][0]);
      ++lix;
    }
    myTree.delete_node(buildings[highEnds[hix].second][2]);
    myTree.print();
    update_skyline(myTree, skyline, curMax, highEnds[hix].first);
    ++hix;
  }
  return skyline;
}

void update_skyline(multiset<int>& BSTree, vector<pair<int, int>>& skyline, int& curMax, int curX) {
  int tMax = BSTree.empty() ? 0 : *BSTree.rbegin();
  if (tMax != curMax) {
    curMax = tMax;
    if (!skyline.empty() && curX == skyline.back().first) {
      skyline.pop_back();
    }
    skyline.push_back(make_pair(curX, curMax));
  }
}

vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
  vector<pair<int, int>> highEnds;
  int N = buildings.size();
  for (int i = 0; i != N; ++i) {
    highEnds.push_back(make_pair(buildings[i][1], i));
  }
  sort(highEnds.begin(), highEnds.end(), myComp);
  vector<pair<int, int>> skyline;
  multiset<int> BSTree;
  int lix = 0, hix = 0, curMax = 0;
  while (lix != N || hix != N) {
    while (lix != N && buildings[lix][0] <= highEnds[hix].first) {
      BSTree.insert(buildings[lix][2]);
      update_skyline(BSTree, skyline, curMax, buildings[lix][0]);
      ++lix;
    }
    BSTree.erase(BSTree.find(buildings[highEnds[hix].second][2]));
    update_skyline(BSTree, skyline, curMax, highEnds[hix].first);
    ++hix;
  }
  return skyline;
}

vector<vector<int>> read_from_file(string fileName) {
  vector<vector<int> > myMat;
  std::ifstream infile(fileName);
  char delim = ']';
  string triplet;
  while (std::getline(infile, triplet, delim) && !triplet.empty()) {
    cout<<triplet<<endl;
    triplet = regex_replace(triplet, regex("^(\\[|,)\\["), "");
    triplet = regex_replace(triplet, regex(","), " ");
    std::istringstream iss(triplet);
    int a, b, c;
    if (!(iss >> a >> b >>c)) { break; } // error
    vector<int> vec(3);
    vec[0] = a; vec[1] = b; vec[2] = c;
    myMat.push_back(vec);
  }
  return myMat;
}

int main() {
  int N = 5;
  int a[][3] = {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
  // int a[][3] = {{1, 2, 1}, {1, 2, 3}, {1, 2, 2}};
  vector<vector<int>> buildings(N);
  for (int n = 0; n!=N; ++n) {
    for (int i = 0; i != 3; ++i) {
      buildings[n].push_back(a[n][i]);
    }
  }
  // vector<vector<int>> buildings = read_from_file("/Users/yzheng47/Downloads/P218_input.txt");
  cout<<"buildings look like:"<<endl;
  print(buildings);
  cout<<"skyline look like:"<<endl;
  print(getSkyline(buildings));
  // int a[] = {10, 15, 12, 10, 8};
  // vector<int> vec(a, end(a));
  // MaxChild_Tree myTree;
  // myTree.insert(10);
  // cout<<myTree.getMax()<<endl;
  // myTree.insert(15);
  // cout<<myTree.getMax()<<endl;
  // myTree.print();
  // myTree.delete_node(15);
  // myTree.print();
  // myTree.insert(12);
  // cout<<myTree.getMax()<<endl;
  // myTree.delete_node(10);
  // cout<<myTree.getMax()<<endl;
  // myTree.delete_node(12);
  // cout<<myTree.getMax()<<endl;
  // myTree.insert(10);
  // cout<<myTree.getMax()<<endl;
  // myTree.insert(8);
  // cout<<myTree.getMax()<<endl;
  // myTree.delete_node(10);
  // cout<<myTree.getMax()<<endl;
  // myTree.delete_node(8);
  // cout<<myTree.getMax()<<endl;
  return 0;
}
