Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.

##### Example 1:

```
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  
on level 1 is 14.5, 
and on level 2 is 11. 
Hence return [3, 14.5, 11].
```

##### Note:

* The range of node's value is in the range of 32-bit signed integer.


# Solution

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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> reval;
        if (!root) return reval;
        
        queue<TreeNode*> nodes;
        nodes.push(root);
        
        while (!nodes.empty()) {
            double sum(0), nodes_count(0);
            std::size_t n(nodes.size());
            for (std::size_t i = 0; i < n; ++i) {
                TreeNode* curr = nodes.front();
                nodes.pop();
                sum += curr->val;
                ++ nodes_count;
                if (curr->left) nodes.push(curr->left);
                if (curr->right) nodes.push(curr->right);
            }
            
            reval.emplace_back(sum / nodes_count);
        }
        
        return reval;
    }
};
```
