Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

__Note:__

A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

# Solution

It's clear that we need use in order traversal here. Since it requires the space complexity to be constant. We need to use morris traversal here.

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
    void recoverTree(TreeNode* root) {
        TreeNode *first(nullptr), *second(nullptr); // The two violated nodes
        TreeNode *pre(nullptr); // Always point to the predecessor of root pointer
        while (root) {
            if (root->left) {
                TreeNode *predecessor(root->left);
                
                // Find predecessor
                while (predecessor->right 
                       && predecessor->right != root) {
                    predecessor = predecessor->right;
                }
                
                if (predecessor->right != root) { // Going left
                    predecessor->right = root; // Set the thread
                    root = root->left;
                } else { // Going right
                    
                    predecessor->right = nullptr; // Revert back
                    
                    if (pre && pre->val > root->val) {
                        if (!first) {
                            first = pre;
                            second = root;
                        } else {
                            second = root;
                        }
                    }
                    
                    pre = root;
                    root = root->right;
                }
            } else { // Going right
                if (pre && pre->val > root->val) {
                    if (!first) {
                        first = pre;
                        second = root;
                    } else {
                        second = root;
                    }
                }
                
                pre = root;
                root = root->right;
            }
        }
        
        if (first && second) {
            std::swap(first->val, second->val);
        }
    }
};
```
