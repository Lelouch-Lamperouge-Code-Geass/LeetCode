Given two binary trees and imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not.

You need to merge them into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of new tree.

##### Example 1:

```
Input: 
	Tree 1                     Tree 2                  
          1                         2                             
         / \                       / \                            
        3   2                     1   3                        
       /                           \   \                      
      5                             4   7                  
Output: 
Merged tree:
	     3
	    / \
	   4   5
	  / \   \ 
	 5   4   7
```

Note: The merging process must start from the root nodes of both trees.

# Solution

A couple of things worth mentioning:

1. If one root is null, we still need to clone the other tree recursively.
2. The general preferred way is to return a whole new tree without modifying the input trees.

### Solution one

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
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (!t1 && !t2) {
            return nullptr;
        } else if (!t1 || !t2) {
            return cloneTree(t1 ? t1 : t2);
        } else { // t1 and t2 are not null
            TreeNode *root = new TreeNode(t1->val + t2->val);
            root->left = mergeTrees(t1->left, t2->left);
            root->right = mergeTrees(t1->right, t2->right);
            return root;
        }
    }
private:
    TreeNode* cloneTree(TreeNode* t) {
        if (!t) return nullptr;
        
        TreeNode *root = new TreeNode(t->val);
        root->left = cloneTree(t->left);
        root->right = cloneTree(t->right);
        return root;
    }
};
```

### Solution two

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
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (!t1 && !t2) {
            return nullptr;
        } else {
            TreeNode *root = new TreeNode(0);
            
            if (t1) root->val += t1->val;
            if (t2) root->val += t2->val;
            
            root->left = mergeTrees(t1? t1->left : nullptr, t2? t2->left : nullptr);
            root->right = mergeTrees(t1? t1->right : nullptr, t2? t2->right : nullptr);
            
            return root;
        }
    }

};
```
