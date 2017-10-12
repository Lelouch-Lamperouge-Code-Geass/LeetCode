Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

```
   1
 /   \
2     3
 \
  5
```

All root-to-leaf paths are:

```
["1->2->5", "1->3"]
```

# Solution

The time complexity for the problem should be O(n), since we are basically visiting each node in the tree.

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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> reval;
        string temp("");
        traversalWithDFS(reval, temp, root);
        return reval;
    }
private:
    void traversalWithDFS(vector<string> &reval, 
                         const string &temp,
                         TreeNode *root) {
        if (root) {
            string new_temp = temp.empty() ? std::to_string(root->val) : temp + "->" + std::to_string(root->val);
            if (!root->left && !root->right) {
                reval.emplace_back(new_temp);
            } else {
               if (root->left) traversalWithDFS(reval, new_temp, root->left);
               if (root->right) traversalWithDFS(reval, new_temp, root->right);
            }
        }
    }
};

```
