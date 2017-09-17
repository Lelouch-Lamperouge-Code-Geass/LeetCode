Given a binary tree, flatten it to a linked list in-place.

For example,
Given

```
         1
        / \
       2   5
      / \   \
     3   4   6
```


The flattened tree should look like:

```
  1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6
```

# Solution

### Solution 1
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
    void flatten(TreeNode* root) {
        while (root) {
            TreeNode* pred = getPredecessor(root);
            if (pred) {
                pred->right = root->right;
                root->right = root->left;
            }
            root->left = nullptr;
            root = root->right;
        }
    }
private:
    TreeNode* getPredecessor(TreeNode* root) {
        if (!root) return nullptr;
        TreeNode* pred(root->left);
        while (pred && pred->right) {
            pred = pred->right;
        }
        return pred;
    }
};
```

### Solution 2

Post order traversal.

```cpp
class Solution {
public:
    void flatten(TreeNode* root) {
        getFlatten(root);
        
    }
private:
    TreeNode* getFlatten(TreeNode* root) {
        if (!root) return nullptr;
        TreeNode* left_tail = getFlatten(root->left);
        TreeNode* right_tail = getFlatten(root->right);
        if (left_tail) {
            left_tail->right = root->right;
            left_tail->left = nullptr;
            root->right = root->left;
            root->left = nullptr;
        }
        if(right_tail) return right_tail;
        if(left_tail) return left_tail;
        return root;
    }
};
```

### Solution 3

Here we pass a pre pointer  to flatten function.   
Note:  
1. We need go to right branch first.  
2. pre pointer is changed on every node.  

```cpp
class Solution {
public:
    void flatten(TreeNode* root) {
        flatten(root, nullptr);
    }
private:
    TreeNode* flatten(TreeNode* root, TreeNode* pre) {
        if (!root) return pre;
        pre = flatten(root->right, pre); // Go to right branch first
        pre = flatten(root->left, pre);
        // Both left branch and right branch have been flattened
        root->right = pre;
        root->left = nullptr;
        pre = root;
        return pre;    
    }
};
```
