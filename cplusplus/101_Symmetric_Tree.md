Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

```
    1
   / \
  2   2
 / \ / \
3  4 4  3
```

But the following [1,2,2,null,3,null,3] is not:

```
  1
   / \
  2   2
   \   \
   3    3
```

__Note:__

Bonus points if you could solve it both recursively and iteratively.

# Solution

# Solution 1

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
    bool isSymmetric(TreeNode* root) {
      if (!root) return true;
      return helper(root->left,root->right);
    }

    bool helper (TreeNode* left, TreeNode* right) {
      if (!left || !right) return left == right;
      return left->val == right->val
        && helper(left->left,right->right)
        && helper(left->right,right->left);
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
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        queue<TreeNode*> left_queue, right_queue;
        left_queue.push(root->left);
        right_queue.push(root->right);
        while(!left_queue.empty() && !right_queue.empty()){
            TreeNode* left = left_queue.front();
            TreeNode* right = right_queue.front();
            left_queue.pop();
            right_queue.pop();
            if(!left ^ !right) return false;
            if(!left && !right) continue;
            if(left->val!=right->val) return false;
            left_queue.push(left->left);
            left_queue.push(left->right);
            right_queue.push(right->right);
            right_queue.push(right->left);
        }
        return left_queue.empty() && right_queue.empty();
    }

};
```

