#include<iostream>
#include<stack>

using namespace std;

/**
 * Definition for binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BSTIterator {
  public:
    BSTIterator(TreeNode *root): node(root), parent_trail(stack<TreeNode*>()){  
      if (node != nullptr) {
        getMin();
        node->left = new TreeNode(0);
        parent_trail.push(node);
        node = node->left;
      }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
      if (node == nullptr) return false;
      if (node->right) return true;
      stack<TreeNode*> trail_cp(parent_trail);
      TreeNode* node_backup = node;
      while (!trail_cp.empty() && trail_cp.top()->right == node) {
        node = trail_cp.top();
        trail_cp.pop();
      }
      node = node_backup;
      return trail_cp.empty()? false : true; 
    }

    /** @return the next smallest number */
    int next() {
      if (node->right) {
        parent_trail.push(node);
        node = node->right;
        getMin();
      } else {
        while (!parent_trail.empty() && parent_trail.top()->right == node) {
          node = parent_trail.top();
          parent_trail.pop();
        }
        node = parent_trail.top();
        parent_trail.pop();
      }
      return node->val; 
    }
  
  private:
    void getMin() {
      while (node->left) {
        parent_trail.push(node);
        node = node->left;
      } 
    }
    TreeNode* node;
    stack<TreeNode*> parent_trail;
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

int main() {
  TreeNode* 
  //TreeNode* root = new TreeNode(2);
  //root->left = new TreeNode(-1);
  //root->right = new TreeNode(5);
  //BSTIterator i = BSTIterator(root);
  while (i.hasNext()) 
    cout << i.next()<<endl;
  return 0;
}
