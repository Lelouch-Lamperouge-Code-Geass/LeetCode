Find the sum of all left leaves in a given binary tree.

Example:

```

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
```


# Solution

The key is to make sure we only add value when it comes from a leaf node on left branch.

### Recursive solution

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
    int sumOfLeftLeaves(TreeNode* root) {
        int reval(0);
        if (root) {
            if (root->left) {
                TreeNode* left = root->left;
                if (!left->left && !left->right) {
                    reval += left->val;
                } else {
                    reval += sumOfLeftLeaves(root->left);
                }
            }
            
            reval += sumOfLeftLeaves(root->right);
        }
        return reval;
    }

};
```

### Iterative method.

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
    int sumOfLeftLeaves(TreeNode* root) {
        if (!root) return 0;
        int reval(0);
        stack<TreeNode*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            TreeNode* node = nodes.top();
            nodes.pop();
            if (node->left) {
                TreeNode* left_child = node->left;
                
                if (!left_child->left && !left_child->right) {
                    reval += left_child->val;
                } else {
                    nodes.push(left_child);
                }
            }
            
            if (node->right) {
                nodes.push(node->right);
            }
        }
        return reval;
    }

};
```
