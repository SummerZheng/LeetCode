#include<iostream>
#include<vector>
#include<string>

using namespace std;
//Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool isLeaf(TreeNode* t) {
  return (!t->left && !t->right)? true: false;
}

void binaryTreePaths(TreeNode* t, string& trail, vector<string>& paths) {
  string numstr = to_string(t->val);
  int sz = numstr.size();
  trail += numstr;
  if (isLeaf(t)) {
    paths.push_back(trail);
  } else {
    trail += "->";
    if (t->left)
      binaryTreePaths(t->left, trail, paths);
    if (t->right)
      binaryTreePaths(t->right, trail, paths);
    trail.pop_back();
    trail.pop_back();
  }
  while (sz--) {
    trail.pop_back();
  }
}

vector<string> binaryTreePaths(TreeNode* root) {
  vector<string> all_paths;
  if (root) {
    string trail;
    binaryTreePaths(root, trail, all_paths);
  }
  return all_paths;
}


int main() {
  return 0;
}
