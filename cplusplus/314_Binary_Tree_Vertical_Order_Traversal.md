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

* BFS, put node, col into queue at the same time.  
* Every left child access col - 1 while right child col + 1.  
* This maps node into different col buckets.    
* Get col boundary min and max on the fly.    
* Retrieve result from cols.    

__*Note that DFS won't work here since the order of elements won't be guranteed.It would be worth mentioning in the explanation that since the nodes in a column are ordered by their row number(depth) we cannot process level x+2 nodes before we process level x.*__

Here is an example of [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]. Notice that every child access changes one column bucket id. So 12 actually goes ahead of 11.

![alt](https://drscdn.500px.org/photo/135826875/m%3D900/7e1d9c2bdc47791e3b54f25bf50b6370)


__The most important thing is to think about how to guarantee the order of top-to-bottom and left-to-right.__ Left to right is easy, because we are maintaining a HashMap from column to nodes, and we can eventually add nodes column by column. However, DFS won't guranteee that within each column, upper level node will be add before lower level node. Therefore we can't use DFS here.


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
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int>> reval;
        unordered_map<int, vector<int>> mapper;
        int min_column(0);
        
        if(root) BFS(mapper, root, min_column);
        
        while (mapper.count(min_column)) { 
            // We know that column value is continuous
            reval.emplace_back(mapper[min_column]);
            ++ min_column;
        }
        
        return reval;
    }
private:
    void BFS(unordered_map<int, vector<int>> &mapper, 
             const TreeNode *root,
             int & min_column) {
        std::queue< std::pair<int, const TreeNode*> > nodes;
        nodes.push(std::make_pair(0, root));
        while (!nodes.empty()) {
            std::pair<int, const TreeNode*> item = nodes.front();
            nodes.pop();
            min_column = std::min(min_column, item.first);
            mapper[item.first].emplace_back(item.second->val);
            if (item.second->left) {
                nodes.push(std::make_pair(item.first - 1, item.second->left));
            }
            if (item.second->right) {
                nodes.push(std::make_pair(item.first + 1, item.second->right));
            }
        }
    }
};
```

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
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if (!root) return vector<vector<int>>();
        
        unordered_map<int, vector<int>> column_to_nodes_mapper;
        queue<pair<int, TreeNode*>> nodes;
        nodes.push(make_pair(0, root));
        int min_column(0), max_column(0);
        
        while (!nodes.empty()) {
            int cur_column = nodes.front().first;
            TreeNode* node = nodes.front().second;
            nodes.pop();
            column_to_nodes_mapper[cur_column].emplace_back(node->val);
            min_column = std::min(min_column, cur_column);
            max_column = std::max(max_column, cur_column);
            
            if (node->left) {
                nodes.push(make_pair(cur_column - 1, node->left));
            }
            if (node->right) {
                nodes.push(make_pair(cur_column + 1, node->right));
            }
        }
        
        vector<vector<int>> result;
        for (int i = min_column; i <= max_column; ++i) {
            result.emplace_back(column_to_nodes_mapper[i]);
        }
        
        return result;
    }
};
```
