Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.

##### Note:

A subtree must include all of its descendants.

Here's an example:

```
   10
    / \
   5  15
  / \   \ 
 1   8   7
```

The Largest BST Subtree in this case is the highlighted one.   
The return value is the subtree's size, which is 3.  

##### Follow up:

Can you figure out ways to solve it with O(n) time complexity?

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
    int largestBSTSubtree(TreeNode* root) {
        int min_val(INT_MAX), max_val(INT_MIN), reval(0);
        isBST(root, min_val, max_val, reval);
        return reval;
    }
private:
    bool isBST(TreeNode *root, int &min_val, int &max_val, int &reval) {
        if (!root) {
            return true;
        } else {
            int left_min(INT_MAX), left_max(INT_MIN), left_size(0);
            bool is_left_bst = isBST(root->left, left_min, left_max, left_size);
            
            int right_min(INT_MAX), right_max(INT_MIN), right_size(0);
            bool is_right_bst = isBST(root->right, right_min, right_max, right_size);
            
            if (is_left_bst && is_right_bst 
                && left_max < root->val && right_min > root->val) {
                // The tree rooted at this node is a binary search tree 
                min_val = root->left ? left_min : root->val;
                max_val = root->right ? right_min : root->val;
                reval = std::max(reval, left_size + right_size + 1);
                return true;
            } else {
                // The tree rooted at this node is not a binary search tree,
                // so take the maximum size of the BST in the left or right subtrees
                reval = std::max(left_size, right_size);
                return false;
            }
        }
    }
};
```
