Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node) or empty, flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. Return the new root.


For example:

```
Given a binary tree {1,2,3,4,5},

    1
   / \
  2   3
 / \
4   5
 

return the root of the binary tree [4,5,2,#,#,3,1].

   4
  / \
 5   2
    / \
   3   1  
```

# Solution

This is not a very intuitive problem for me, I have to spent quite a while drawing figures to understand it. As shown in the figure, 1 shows the original tree, you can think about it as a comb, with 1, 2, 4 form the bone, and 3, 5 as the teeth. All we need to do is flip the teeth direction as shown in figure 2. We will remove the link 1--3, 2--5, and add link 2--3, and 4--5. And node 4 will be the new root.

As the recursive solution, we will keep recurse on the left child and once we are are done, we found the newRoot, which is 4 for this case. At this point, we will need to set the new children for node 2, basically the new left node is 3, and right node is 1. Here is the recursive solution:

![alt](http://i63.tinypic.com/1s1gcp.jpg)

### Recursive

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
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (!root) return nullptr;
        if (!root->left) return root; // No left, no right
        TreeNode*  reval = upsideDownBinaryTree(root->left);
        root->left->left = root->right;
        root->left->right = root;
        root->left = root->right = nullptr; // Important!
        return reval;
    }
};
```

### Iterative

For the iterative solution, it follows the same thought, the only thing we need to pay attention to is to save the node information that will be overwritten.

![alt](http://i68.tinypic.com/2nkj582.jpg)

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
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        TreeNode *parent(nullptr), *right_sibling(nullptr), *next(nullptr);
        while (root) {
            next = root->left;
            root->left = right_sibling;
            right_sibling = root->right; // save right sibling
            root->right = parent;
            
            parent = root;
            root = next;
        }
        
        return parent;
    }
};

```
