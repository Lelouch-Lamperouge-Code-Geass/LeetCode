/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
  vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> reval;
    dfs_binary_tree_path(reval,"",root);
    return reval;
  }
private:
  void dfs_binary_tree_path(vector<string> &reval,
                            const string & temp,
                            TreeNode* root) {
    if (!root) return;
    if (!root->left && !root->right) {
      reval.push_back(temp+std::to_string(root->val));
    } else {
      dfs_binary_tree_path(reval,temp+std::to_string(root->val)+"->",root->left);
      dfs_binary_tree_path(reval,temp+std::to_string(root->val)+"->",root->right);
    }
  }
};
