#include<iostream>
#include<vector>
#include"TreeNode.h"

using namespace std;

TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
  if (root == p || root == q || !root) return root;
  TreeNode* leftA = lowestCommonAncestor2(root->left, p, q);
  TreeNode* rightA = lowestCommonAncestor2(root->right, p, q);
  if (leftA && rightA) 
    return root;
  else
    return leftA? leftA : rightA;
}

bool findPath(TreeNode* parent, TreeNode* target, vector<TreeNode*>& trail) {
  if (!parent) return false;
  if (parent == target ||
      findPath(parent->left, target, trail) ||
      findPath(parent->right, target, trail)) {
    trail.push_back(parent);
    return true;
  } else {
    return false;
  }
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  if (!root) return nullptr;
  vector<TreeNode*> path2p, path2q;
  if (!findPath(root, p, path2p)) return nullptr;
  if (!findPath(root, q, path2q)) return nullptr;
  int ixp = path2p.size()-1, ixq = path2q.size()-1;
  TreeNode* lca = nullptr;
  while ( ixp >=0 && ixq >=0 && path2p[ixp] == path2q[ixq]) {
    lca = path2p[ixp];
    --ixp; --ixq;
  }
  return lca;
}


int main() {
  return 0;
}
