Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.  

For example:  
Given the below binary tree and sum = 22,  

```
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
```

return

```
[
   [5,4,11,2],
   [5,8,4,5]
]
```

# Solution

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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
      vector<vector<int>> res;
      vector<int> temp;
      helper(res, temp, root, sum);
      return res;
    }
private:    
    void helper(vector<vector<int>> & res,vector<int> & temp, TreeNode* root, int sum) {
      if (!root) return;
      if (!root->left && !root->right && root->val == sum) { // leaf node
        temp.push_back(root->val);
        res.push_back(temp);
        temp.pop_back(); // revert back
      } else {
        temp.push_back(root->val);
        sum -= root->val;
        helper(res,vec,root->left,sum);
        helper(res,vec,root->right,sum);
        temp.pop_back(); // revert back
      }
    }
};
```
