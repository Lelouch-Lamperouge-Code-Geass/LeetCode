Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,

```
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
```

You should return [1, 3, 4].
  

# Solution
  
On each level of the tree, we only select the rightmost node. 
  
How do we guarantee the node we visit is the rightmost node of that level?  It turns out we just need to make sure that on each level, we visit the rightmost node first. Therefore, we always visit right child before left child for each node, and we can know whether this is the first node we visit on this level by comparing the level to the size of current result vector.

The time complexity is  O(n) time  where n is the total node of the tree.
  
The space complexity is O(height of the tree).  
  
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> reval;
        populateRightmostWithDFS(root, reval, 0);
        return reval;
    }
private:
    void populateRightmostWithDFS(TreeNode* root, vector<int> &result, const int level) {
        if (root) {
            if (result.size() == level) {
                result.emplace_back(root->val);
            }
            populateRightmostWithDFS(root->right, result, level + 1);
            populateRightmostWithDFS(root->left, result, level + 1);
        }
    }
};
```
