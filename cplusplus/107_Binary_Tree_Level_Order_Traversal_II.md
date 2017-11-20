Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:  

Given binary tree [3,9,20,null,null,15,7],

```
    3
   / \
  9  20
    /  \
   15   7
```

return its bottom-up level order traversal as:

```
[
  [15,7],
  [9,20],
  [3]
]
```

# Solution

We need make sure our solution meet below requirements:

1. Nodes on the same level should be on the same container.  
2. For each level, nodes should be arranged from left to right.  
3. The final result should be bottom-up.

```cpp
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
      vector<vector<int>> res;
      helper(res,root,0);
      std::reverse(res.begin(),res.end());
      return res;
    }
    
    void helper(vector< vector<int> > & res, TreeNode* root, int level) {
      if (!root) return;
      if (res.size() == level) res.push_back(vector<int>());
      res[level].push_back(root->val);
      helper(res,root->left,level+1);
      helper(res,root->right,level+1);
    }
};
```
