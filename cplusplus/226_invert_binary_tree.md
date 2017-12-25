Invert a binary tree.
    
```    
     4
   /   \
  2     7
 / \   / \
1   3 6   9
```

to

```
     4
   /   \
  7     2
 / \   / \
9   6 3   1
```    

##### Trivia:

This problem was inspired by this [original tweet](https://twitter.com/mxcl/status/608682016205344768) by Max Howell:
Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so fuck off.

### Solution 1,  Recursive, DFS


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
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        TreeNode *left = invertTree(root->left);
        TreeNode *right = invertTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
};
```

### Solution 2, BFS, level order traversal

```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return root;
        stack<TreeNode*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            TreeNode * curr = nodes.top();
            nodes.pop();
            TreeNode * left_child = curr->left;
            curr->left = curr->right;
            curr->right = left_child;
            if (curr->left) nodes.push(curr->left);
            if (curr->right) nodes.push(curr->right);
        }
        return root;
    }
};
```
