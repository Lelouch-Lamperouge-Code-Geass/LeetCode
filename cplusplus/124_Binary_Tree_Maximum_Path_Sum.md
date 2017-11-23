Given a binary tree, find the maximum path sum.  

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.  

For example:  
Given the below binary tree,  

```
       1
      / \
     2   3
```

Return 6.

# Solution

The question asks for finding the maximum path sum of a binary tree.

If we know the maximum path sum of on each node (the path must include that node), then the maximum value of those is our final result.

Right now the problem becomes how to find a maximum path sum on a tree node which includes that tree node.

And this maximum value is depends on :

1. maximum path sum including left child + node->val
2. maximum path sum including right child + node->val
3. node->val ( this happesn when 1, 2 are all negative)

__Time complexity O(number_of_nodes), space complexity O(height of the tree).__

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
    int maxPathSum(TreeNode* root) {
        int reval(INT_MIN); // Note that value might be negative
        maxPathSumEndWithCurrNode(root, reval);
        return reval;
    }
    
private:
    int maxPathSumEndWithCurrNode(TreeNode *root, int &max_path_sum) {
        if (!root) return 0; 
        
        // get max path sum ends with left child
        int left_max = maxPathSumEndWithCurrNode(root->left, max_path_sum);
        // get max path sum ends with right child
        int right_max = maxPathSumEndWithCurrNode(root->right, max_path_sum);
        
        // get max path including current node
        int max_path_sum_include_curr_node(root->val);
        if (left_max > 0) max_path_sum_include_curr_node += left_max;
        if (right_max > 0) max_path_sum_include_curr_node += right_max;
        
        // comparing max path including current node with final result
        max_path_sum = std::max(max_path_sum, max_path_sum_include_curr_node);
        
        int max_path_sum_ends_with_one_child(std::max(left_max, right_max));
        
        return root->val + (max_path_sum_ends_with_one_child > 0 ? max_path_sum_ends_with_one_child :  0);
    }
};
```

Can be simplified as

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
    int maxPathSum(TreeNode* root) {
        int max_sum(INT_MIN);
        maxSumIncludeCurr(root,max_sum);
        return max_sum;
    }
private:
    int maxSumIncludeCurr(const TreeNode * const root, int & max_sum){
        if(!root) return 0;
        int left = std::max(0,maxSumIncludeCurr(root->left,max_sum));
        int right = std::max(0,maxSumIncludeCurr(root->right,max_sum));
        int sum = root->val + left + right;
        max_sum = std::max(max_sum,sum);
        return root->val + std::max(left,right);
    }
};
```
