Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:  
Given binary tree [3,9,20,null,null,15,7],

```
    3
   / \
  9  20
    /  \
   15   7
```

return its zigzag level order traversal as:

```
[
  [3],
  [20,9],
  [15,7]
]
```

# Solution

### Solution 1

This solution is very straightforward. We first add nodes to final result level by level.

Finally, reverse nodes on all odd levels in the final result.

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
          vector<vector<int>> res;
          if (!root) return res;
          std::list<TreeNode*> nodes;
          nodes.push_back(root);
          while (!nodes.empty()) {
            res.push_back(vector<int>());
            // This level has cur_size nodes  
            const std::size_t cur_size(nodes.size());
            for (std::size_t i = 0;i < cur_size; ++i) {
                TreeNode *cur_node = nodes.front();
                nodes.pop_front();
                res.back().push_back(cur_node->val);
                if (cur_node->left) nodes.push_back(cur_node->left);
                if (cur_node->right) nodes.push_back(cur_node->right);
            }
          }
        
          for (std::size_t level = 1; level < res.size(); level += 2) {
              std::reverse(res[level].begin(), res[level].end());
          }  
          return res;    
    }
};
```

A different style, while the same methodology.

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        helper(res,root,0);
        const int N(res.size());
        for(int i=1;i<N;i+=2){//reverse the even index row
            std::reverse(res[i].begin(),res[i].end());
        }
        return res;
    }
private:
    void helper(vector<vector<int>> & res,TreeNode*root,int level){
        if(!root) return;
        if(level==res.size()){
            res.push_back(vector<int>());
        }
        res[level].push_back(root->val);
        helper(res,root->left,level+1);
        helper(res,root->right,level+1);
    }
};
```

# Solution 2

We use a bool flag to determine whether we add nodes on current level from left to right, or from right to left.

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        bool to_right(true);
        deque<TreeNode*> nodes(1,root);
        while(!nodes.empty()){
            res.push_back(vector<int>());//push an empty vector for current level
            deque<TreeNode*> next_level;
            const int size(vec.size());
            if(to_right){
                for(int i = 0;i < size; ++i){
                    res.back().push_back(vec[i]->val);
                    if(vec[i]->left) next_level.push_back(vec[i]->left);
                    if(vec[i]->right) next_level.push_back(vec[i]->right);
                }
            } else {
                for(int i = size;i-- > 0; ){
                    res.back().push_back(vec[i]->val);
                    if(vec[i]->right)next_level.push_front(vec[i]->right);
                    if(vec[i]->left)next_level.push_front(vec[i]->left);
                }
            }
            to_right = !to_right;
            vec = next_level;
        }
        return res;
    }
};
```
