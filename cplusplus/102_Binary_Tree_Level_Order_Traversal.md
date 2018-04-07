Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:  
Given binary tree [3,9,20,null,null,15,7],  

```
    3
   / \
  9  20
    /  \
   15   7
 ```
 
 return its level order traversal as:
 
 ```
 [
  [3],
  [9,20],
  [15,7]
]
```

# Solution

Another intersting problem https://github.com/YangLiuNYU/LeetCode/blob/master/cplusplus/314_Binary_Tree_Vertical_Order_Traversal.md.

In this problem, we need to make sure nodes on different level are in their related container in final result.

And for the nodes on the same leve, we need to make sure they are ordered from left to right.

### Solution one

In this solution, we perform depth-first search on left child first, and then right child. We pass down the "level" information.

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> reval;
        visit(root, 0, reval);
        return reval;
    }
    
private:
    void visit(TreeNode* root, 
               const std::size_t level, 
               vector<vector<int>> &reval) {
        if (root) {
            if (level == reval.size()) {
                reval.emplace_back(vector<int>());
            }
            
            reval[level].emplace_back(root->val);
            
            visit(root->left, level + 1, reval);
            visit(root->right, level + 1, reval);
        }
    }
};
```

### Solution two

In this solution, we use a queue and push nodes into the queue level by level.

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return vector<vector<int>>();
        
        queue<TreeNode*> nodes;
        nodes.push(root);
        vector<vector<int>> reval;
        while (!nodes.empty()) {
            reval.emplace_back(vector<int>());
            for (size_t i = 0, n = nodes.size(); i < n; ++i) {
                TreeNode *cur_node = nodes.front();
                nodes.pop();
                reval.back().emplace_back(cur_node->val);
                if (cur_node->left) nodes.push(cur_node->left);
                if (cur_node->right) nodes.push(cur_node->right);
            }
        }
        
        return reval;
    }
};
```
Or we can add a null node to mark the end of each level.

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> reval;
        if (!root) return reval;
        queue<TreeNode*> nodes;
        nodes.push(root);
        nodes.push(nullptr); // mark end of this level
        TreeNode *cur_node(nullptr);
        reval.emplace_back(vector<int>());
        while (!nodes.empty()) {
            cur_node = nodes.front();
            nodes.pop();
            if (cur_node) {
                reval.back().emplace_back(cur_node->val);
                if (cur_node->left) nodes.push(cur_node->left);
                if (cur_node->right) nodes.push(cur_node->right);
            } else { 
                // cur_node is nullptr, this is the end of this level
                // Let's also add a nullptr to mark the end of next level
                // and a new vector for the elements in next level. 
                // But we need to make sure there are nodes in next level at first.
                if (!nodes.empty()) {
                    nodes.push(nullptr);
                    reval.emplace_back(vector<int>());
                }
            }
        }
        return reval;
    }
};
```
