Given a binary tree, find the length of the longest consecutive sequence path.

 

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).

For example,

```
   1
    \
     3
    / \
   2   4
        \
         5
```

Longest consecutive sequence path is 3-4-5, so return 3.

```
   2
    \
     3
    / 
   2    
  / 
 1
```

Longest consecutive sequence path is 2-3,not3-2-1, so return 2.

# Solution

My first solution is like this, which is absolutely WRONG!



```cpp
class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        return DFS(root);
    }
private:
    int DFS(TreeNode* root) {
        if (!root) return 0;
        if (!root->left && !root->right) return 1;
        
        int left = DFS(root->left);
        int right = DFS(root->right);
        
        if (root->left && root->val + 1 == root->left->val) left += 1;
        if (root->right && root->val + 1 == root->right->val) right += 1;
        
        return std::max(left, right);
    }
};
```

This is the RIGHT solution!

### Solution 1

A very intuitive solution.

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
    int longestConsecutive(TreeNode* root) {
        int max_len(0);
        DFS(root, nullptr, 0, max_len);
        return max_len;
    }
private:
    void DFS(TreeNode *root, TreeNode *parent, int len, int &max_len) {
        if (!root) return;
        
        if (parent && root->val == parent->val + 1) len += 1;
        else len = 1; // New path begins
        
        max_len = std::max(max_len, len);
        
        DFS(root->left, root, len, max_len);
        DFS(root->right, root, len, max_len);
    }
};
```

### Solution 2

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
    int longestConsecutive(TreeNode* root) {
        return DFS(root, nullptr, 0);
    }
private:
    // For each node, return the max path len so far including that node
    int DFS(TreeNode *root, TreeNode *parent, int len) {
        if (!root) return len;
        
        if (parent && root->val == parent->val + 1) len += 1;
        else len = 1; // New path begins
        
        int left = DFS(root->left, root, len);
        int right = DFS(root->right, root, len);
        
        return std::max(len, std::max(left, right));
    }
};
```


