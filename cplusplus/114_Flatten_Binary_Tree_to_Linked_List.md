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

__The time complexity is O(N) because each node get visited at most once. It's space complexity is O(1).__

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

This solution uses divide-and-conquer paradigm. We first assume that what if we already flattened left tree and right tree, in that case how can we combine them with root node to form a list?

__The time complexity is O(N) because each node get visited at most once. It's space complexity is O(depth of recursion).__

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
        flattenTreeAndReturnTailNode(root);
    }

private:
    TreeNode* flattenTreeAndReturnTailNode(TreeNode* root) {
        if (!root) return nullptr;
        if (!root->left && !root->right) return root; // leaf node
        
        TreeNode* left_tail = flattenTreeAndReturnTailNode(root->left); // Flatten left tree
        TreeNode* right_tail = flattenTreeAndReturnTailNode(root->right); // Flatten right tree

        if (left_tail) { // Note that we need to check whether left tree is empty
            left_tail->right = root->right;
            root->right = root->left;
            root->left = nullptr;
        }
        
        return right_tail ? right_tail : left_tail; // Note that right tree might be empty.
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
