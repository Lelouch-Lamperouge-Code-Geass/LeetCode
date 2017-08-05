Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null.

# Solution

__Time complexity O(h), space complexity O(1)__

```cpp
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (root == NULL || p == NULL) return NULL;
        
        TreeNode *suc = NULL;
        while (root != NULL) {
            if (root->val <= p->val) {
                root = root->right;
            } else {
                suc = root;
                root = root->left;
            }
        }
        
        return suc;
    }
};
```
