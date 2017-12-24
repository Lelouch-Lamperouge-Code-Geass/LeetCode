Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from [Wikipedia](https://en.wikipedia.org/wiki/Binary_tree#Types_of_binary_trees):

In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

# Solution

####  Full binary tree vs complete binary tree vs perfect binary tree

![alt](http://www.csie.ntnu.edu.tw/~u91029/BinaryTree2.png)

####  What is the difference between height and depth of a tree?

![alt](https://i.stack.imgur.com/RHEqu.png)


Depth and height as properties of a node:

* The depth of a node is the number of edges from the node to the tree's root node. A root node will have a depth of 0.  
* The height of a node is the number of edges on the longest path from the node to a leaf. A leaf node will have a height of 0.  

Properties of a tree:

* The height of a tree would be the height of its root node, or equivalently, the depth of its deepest node.
* Note that depth doesn't make sense for a tree.



                                                     
### Solution 1

Since this is a complete binary tree, for any tree node, if its left child tree's height is bigger than the right child tree, then the left child tree is a perferct binary tree. For a perferct binary tree with height H, its total nodes is ```2 ^ (height_of_left_tree + 1) - 1```, we can add the total nodes of left child tree plus current node, which is ```2 ^ height_of_left_tree```, and the move current node pointer to its right child.

If current node's left child tree's height is the same as right child tree, then its right child tree is a perferct binary tree. We can do the same thing like above, collecting the nodes of right tree plus current node.

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
private:
    // Since we know it is a complete binary tree,
    // the height of  a node as a root is simply the distance 
    // to its leftmost node.
    // Return -1 if root is nullptr.
    int getHeight(TreeNode *root) {
        if (!root) return -1;
        int reval(0);
        while (root && root->left) {
            root = root->left;
            ++ reval;
        }
        return reval;
    }
public:
    int countNodes(TreeNode* root) {
        int reval(0);
        while (root) {
            int left_height(getHeight(root->left));
            int right_height(getHeight(root->right));
            if (left_height == right_height) {
                // Left child tree is a perfect binary tree.
                // A special case here is that root node is leaf node,
                // in this case, left_height == -1 here.
                reval += std::pow(2, left_height + 1);
                root = root->right;
            } else { // left_height is larger then right_height
                // Right child tree is a perfect binary tree
                reval += std::pow(2, right_height + 1);
                root = root->left;
            }
        }
        return reval;
    }
};
```

### Solution 2

```cpp
class Solution {
public:
    int countNodes(TreeNode* root) {
        if(!root) return 0;
        int height(0), sum(0), i(0);
        TreeNode *t(root), *t0(nullptr);
        //get the height of the tree;
        while(t) {
            t = t->left, ++ height;
        }
        t = root;
        int level = height - 2; //levels under the child of root;
        while(level >=0 ) //collect the bottom-level nodes by halving them apart;
        {
            t0 = t->left;
            for(i = 0; i < level; ++i) t0 = t0->right; 
            if(t0) { sum += 1<<level; t = t->right; } //rightmost node is not null;
            else t = t->left;
            
            -- level; //move to the next level;
        }
        if(t) sum++; //if it's a complete tree, collect the last right node;
        return sum+((1<<(height-1))-1);
    }
};
```
