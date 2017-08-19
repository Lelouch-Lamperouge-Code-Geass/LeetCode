Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

Examples:

```
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
 

return its vertical order traversal as:

[
  [9],
  [3,15],
  [20],
  [7]
]
 

Given binary tree [3,9,20,4,5,2,7],

    _3_
   /   \
  9    20
 / \   / \
4   5 2   7
 

return its vertical order traversal as:

[
  [4],
  [9],
  [3,5,2],
  [20],
  [7]
]
```

# Solution

BFS, put node, col into queue at the same time.  
Every left child access col - 1 while right child col + 1.  
This maps node into different col buckets.    
Get col boundary min and max on the fly.    
Retrieve result from cols.    

__*Note that DFS won't work here since the order of elements won't be guranteed.It would be worth mentioning in the explanation that since the nodes in a column are ordered by their row number(depth) we cannot process level x+2 nodes before we process level x.*__

```cpp
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        map<int,vector<int>> hm;
        queue<pair<TreeNode*,int>> q;
        q.push({root,0});
        while(!q.empty()){
            TreeNode* node=q.front().first;
            int col=q.front().second;
            q.pop();
            hm[col].push_back(node->val);
            if(node->left) q.push({node->left,col-1});
            if(node->right) q.push({node->right,col+1});
        }
        for(auto i:hm){
            res.push_back(i.second);
        }
    return res;
  }
};
```
