Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

Example:

Given a binary tree 

```
          1
         / \
        2   3
       / \     
      4   5    
```

Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of edges between them.

# Solution

For every node, ```length of longest path which pass it = MaxDepth of its left subtree + MaxDepth of its right subtree```.

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
    int diameterOfBinaryTree(TreeNode* root) {
        int max_path_len(0);
        max_depth(root, max_path_len);
        return max_path_len;
    }
private:
    int max_depth(TreeNode* root, int& max_path_len) {
        if (!root) {
            return 0;
        } else {
            int left_max_depth = max_depth(root->left, max_path_len);
            int right_max_depth = max_depth(root->right, max_path_len);
            max_path_len = std::max(max_path_len, left_max_depth + right_max_depth);
            return 1 + std::max(left_max_depth,right_max_depth);
        }
    } 
};
```
