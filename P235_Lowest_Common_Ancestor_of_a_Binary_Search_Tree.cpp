#include<iostream>
#include"TreeNode.h"

using namespace std;

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  int minV = min(p->val, q->val), maxV = max(p->val, q->val);
  while (root) {
    if (root->val < minV)
     root = root->right;
    else if (root->val > maxV)
     root = root->left;
    else
     break; 
  }
  return root;
}

int main() {
  return 0;
}
