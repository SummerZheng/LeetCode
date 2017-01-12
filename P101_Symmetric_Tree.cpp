#include<iostream>
#include<vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void print(vector<TreeNode*> vec) {
  for (int i = 0; i != vec.size(); ++i) {
    if (!vec[i])
      cout<<", _";
    else
      cout<<", "<<vec[i]->val;
  }
  cout<<endl;
}

bool isSymmetric_util(vector<TreeNode*>& childNodes) {
  vector<TreeNode*> nextLevel(childNodes.size() * 2, nullptr);
  cout<<"this level of nodes:"<<endl;
  print(childNodes);
  bool allNullptr = true;
  for (int i = 0; i != childNodes.size(); ++i) {
    if (childNodes[i]) allNullptr = false;
  }
  if (allNullptr) return true;
  for (int i = 0, j = childNodes.size()-1; i <= j; ++i, --j) {
    if (!childNodes[i] && childNodes[j] ) return false;
    if ( childNodes[i] && !childNodes[j]) return false;
    if ( childNodes[i] && childNodes[j] ) {
      if (childNodes[i]->val != childNodes[j]->val) {
        return false;
      } else {
        nextLevel[2*i]   = childNodes[i]->left;
        nextLevel[2*i+1] = childNodes[i]->right;
        nextLevel[2*j]   = childNodes[j]->left;
        nextLevel[2*j+1] = childNodes[j]->right;
      }
    }
  }
  cout<<"next level of nodes:"<<endl;
  print(nextLevel);
  return isSymmetric_util(nextLevel);
}

bool isSymmetric_MLE(TreeNode* root) {
  vector<TreeNode*> childNodes;
  childNodes.push_back(root);
  cout<<childNodes.size()<<endl;
  return isSymmetric_util(childNodes);
}

bool isSymmetric_util(TreeNode* p1, TreeNode* p2) {
  if (!p1  && !p2) return true;
  if (p1 && p2 && p1->val == p2->val)
    return isSymmetric_util(p1->left, p2->right) && isSymmetric_util(p1->right, p2->left);
  return false;
}

bool isSymmetric(TreeNode* root) {
  if (!root) return true;
  return isSymmetric_util(root->left, root->right);
}

int main() {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(2);
  root->left->right = new TreeNode(3);
  root->right->right = new TreeNode(3);
  cout<<isSymmetric(root)<<endl;
  return 0;
}
