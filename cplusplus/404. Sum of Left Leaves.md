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

For given node we check whether its left child is a leaf. If it is the case, we add its value to answer, otherwise recursively call method on left child. For right child we call method only if it has at least one nonnull child.

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
                // Left child is a leaf node
                if (!root->left->left && !root->left->right) {
                    reval += root->left->val;
                }
            }
            
            reval += sumOfLeftLeaves(root->left);
            reval += sumOfLeftLeaves(root->right);
        }
        return reval;
    }
};
```

### Iterative method.

Here for each node in the tree we check whether its left child is a leaf. If it is true, we add its value to answer, otherwise add left child to the stack to process it later. For right child we add it to stack only if it is not a leaf.

```cpp
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if (!root) return 0;
        
        int reval(0);
        queue<TreeNode*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            root = nodes.front();
            nodes.pop();
            if (root->left 
                && !root->left->left && !root->left->right) { // Left child is a leaf node
                reval += root->left->val;
            }
            if (root->left) nodes.push(root->left);
            if (root->right) nodes.push(root->right);
        }
        
        return reval;
    }
};
```
