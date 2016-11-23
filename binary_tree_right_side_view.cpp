class Solution {
public:
  vector<int> rightSideView(TreeNode* root) {
    vector<int> res;
    dfs(res,root,0);
    return res;
  }
private:
  void dfs(vector<int> & res, TreeNode* root, int level) {
    if (!root) return;
    if (res.size()==level) res.push_back(root->val);
    dfs(res,root->right,level+1);
    dfs(res,root->left,level+1);
  }
};
