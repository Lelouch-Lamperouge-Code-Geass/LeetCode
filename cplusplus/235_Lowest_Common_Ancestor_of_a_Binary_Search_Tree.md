Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”
```
        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
   0      _4       7       9
         /  \
         3   5
 ```
For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

# Solution
```
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
```
/* Solution 1: Iteration */
```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) return nullptr;
        
        // make sure p is smaller than q
        if (p->val > q->val) return lowestCommonAncestor(root, q, p);
        
        while (root) {
            if (root->val < p->val) {
                root = root->right;
            } else if (root->val > q->val) {
                root = root->left;
            } else {
                return root;
            }
        }
        
        return root;
    }
};
```

/* Solution 2: recursion */
```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) return nullptr;
        
        // make sure p is smaller than q
        if (p->val > q->val) return lowestCommonAncestor(root, q, p);
        
        if (root->val < p->val) {
            return lowestCommonAncestor(root->right, p, q);
        } else if (root->val > q->val) {
            return lowestCommonAncestor(root->left, p, q);
        } else {
            return root;
        }
    }
};
```

