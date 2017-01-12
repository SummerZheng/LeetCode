#include<iostream>
#include<vector>
#include<deque>
#include"print.h"

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void print(deque<TreeNode*> myQ) {
  for (auto t : myQ) {
    if (!t)
      cout<<", _";
    else
      cout<<", "<<t->val;
  }
  cout<<endl;
}

vector<vector<int>> levelOrder(TreeNode* root) {
  vector<vector<int>> output;
  deque<TreeNode*> curLevel;
  if (root) curLevel.push_back(root);
  deque<TreeNode*> nextLevel;
  while (!curLevel.empty()) {
    print(curLevel);
    vector<int> curInt;
    while (!curLevel.empty()) {
      TreeNode* frontNode = curLevel.front();
      curLevel.pop_front();
      if (frontNode->left)
        nextLevel.push_back(frontNode->left);
      if (frontNode->right)
        nextLevel.push_back(frontNode->right);
      curInt.push_back(frontNode->val);
    }
    output.push_back(curInt);
    cout<<"before swap, next level"<<endl;
    print(nextLevel);
    swap(curLevel, nextLevel);
    cout<<"after swap, cur level"<<endl;
    print(curLevel);
  }
  return output;
}

int main() {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(2);
  root->left->right = new TreeNode(3);
  root->right->right = new TreeNode(3);
  vector<vector<int>> level_order_traversal(levelOrder(root));
  print(level_order_traversal);
  return 0;
}
