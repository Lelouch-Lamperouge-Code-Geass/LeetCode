Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

* The left subtree of a node contains only nodes with keys less than the node's key.
* The right subtree of a node contains only nodes with keys greater than the node's key.
* Both the left and right subtrees must also be binary search trees.

Example 1:

```
    2
   / \
  1   3
```

Binary tree [2,1,3], return true.
Example 2:

```
    1
   / \
  2   3
```

Binary tree [1,2,3], return false.

# Solution

If we use in-order traversal to serialize a binary search tree, we can get a list of values in ascending order. It can be proved with the definition of BST. And here I use the reference of TreeNode pointer prev as a global variable to mark the address of previous node in the list.

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
    bool isValidBST(TreeNode* root) {
        TreeNode* predecessor(nullptr);
        
        return check(root, predecessor);
    }
private:
    
    bool check(TreeNode* node, TreeNode* & predecessor) {
        if (!node) return true;
        
        // Check left branch
        if (!check(node->left, predecessor)) return false;
        
        // Check current node, note that duplicate values are not allowed in BST
        if (predecessor && predecessor->val >= node->val) return false;
        
        predecessor = node;
        
        // Check right branch
        return check(node->right, predecessor);
        
    }
};
```

### Solution two

```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> nodes;
        TreeNode *curr(root), *pre(nullptr);
        
        while (curr || !nodes.empty()) {
           if(curr){//root to leaf,going down
                nodes.push(curr);
                curr = curr->left;
            } else {// leaf to root, going up
                curr = nodes.top();
                nodes.pop();
                if (pre && pre->val >= curr->val) return false;
                pre = curr;
                curr = curr->right;
            }
        }
        
        return true;
    }

};
```
