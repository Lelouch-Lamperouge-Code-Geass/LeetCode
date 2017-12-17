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
class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        /** the left most node, when backtrack we need to set the parent node left & right point to null **/
        if(!root || !root->left) return root;
        /** record the current left & right node before DFS **/
        TreeNode* cur_left = root->left;
        TreeNode* cur_right = root->right;
        /** DFS call to build the right sub tree **/
        TreeNode* new_root = upsideDownBinaryTree(root->left);
        cur_left->right = root;
        cur_left->left = cur_right;
        /** now the root node become the child node, so we need to clear the left & right sub node to avoid cycles**/
        root->left = nullptr;
        root->right = nullptr;
        return new_root;
    }
};
```

### Iterative

For the iterative solution, it follows the same thought, the only thing we need to pay attention to is to save the node information that will be overwritten.

![alt](http://i68.tinypic.com/2nkj582.jpg)

```cpp
class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        /** cur   : record the current root node 
         * parent : record the parent node of the current node
         * right  : record the right child node of the parent node 
         * next   : record the next level left child node **/
        TreeNode* cur = root;
        TreeNode* parent = NULL;
        TreeNode* right = NULL;
        TreeNode* next = NULL;
        while(cur != NULL) {
            next = cur->left;
            /** set the cur->left point to right and cur->right point to parent **/
            cur->left = right;
            right = cur->right;
            cur->right = parent;
            parent = cur;
            /** move left down to the next node **/
            cur = next;
        }
        return parent;
    }
};

```
