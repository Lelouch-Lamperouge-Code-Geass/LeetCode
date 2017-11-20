Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

# Solution

__Note that many solutions on Leetcode named their functions "depth" but is actually using "height" property of node. You must be clear with the difference between "node depth" and "node height". BTW, tree has "depth" and "height" properties too. 

This problem is generally believed to have two solutions: the top down approach and the bottom up way.

1.The first method checks whether the tree is balanced strictly according to the definition of balanced binary tree: the difference between the heights of the two sub trees are not bigger than 1, and both the left sub tree and right sub tree are also balanced. With the helper function heightOfNode(), we could easily write the code;

For the current node root, calling heightOfNode() for its left and right children actually has to access all of its children, thus the complexity is O(N). We do this for each node in the tree, so the overall complexity of isBalanced will be O(N^2). This is a top down approach.

__Not good enough, a lot of recalculations. We should do better!__

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
    bool isBalanced(TreeNode* root) {
        if (!root) return true;
        
        int left_height = heightOfNode(root->left);
        int right_height = heightOfNode(root->right);
        
        return std::abs(left_height - right_height) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }
private:
    int heightOfNode(TreeNode* root) {
        if (!root) return 0;
        return 1 + std::max(heightOfNode(root->left), heightOfNode(root->right));
    }
};
```


2.The second method is based on DFS. Instead of calling heightOfNode() explicitly for each child node, we return the height of the current node in DFS recursion. When the sub tree of the current node (inclusive) is balanced, the function heightOfNode() returns a non-negative value as the height. Otherwise -1 is returned. According to the leftHeight and rightHeight of the two children, the parent node could check if the sub tree is balanced, and decides its return value.

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
    bool isBalanced(TreeNode* root) {
        int height = heightOfNode(root);
        return height < 0 ? false : true;
    }
private:
    int heightOfNode(TreeNode* root) {
        if (!root) return 0;
        
        int left_height = heightOfNode(root->left);
        if (left_height == -1) return -1;
        
        int right_height = heightOfNode(root->right);
        if (right_height == -1) return -1;
        
        if (std::abs(left_height - right_height) > 1) return -1;
        
        return 1 + std::max(left_height, right_height);
    }
};
```

# Knowledge

### What is the difference between tree depth and height?

![alt](https://i.stack.imgur.com/8yPi9.png)

When depth and height are referring to properties of a node:

* The __depth__ of a node is the number of edges from the node to the tree's root node. A root node will have a depth of 0.  
* The __height__ of a node is the number of edges on the longest path from the node to a leaf. A leaf node will have a height of 0.  

When depth and height are referring to properties of a tree:

* The height of a tree would be the height of its root node,or equivalently, the depth of its deepest node.  
* The diameter (or width) of a tree is the number of nodes on the longest path between any two leaf nodes. The tree below has a diameter of 6 nodes.  
