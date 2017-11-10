You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

##### Example:

```
root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
```

# Solution

### Solution one

For each node,

1. Build the path with it 
2. Build the path without it

Let me explain time complexity. It is O(nlogn) in general and O(n^2) in worst case.
In common case (a balanced tree):

```

            1
      2           3
   4     5     6     7
```

Firstly, pathSum() will be called O(n) times, which is O(n) to traverse the tree.

Then, on every node, we call pathSumFrom(), but notice, the time of this call is different on different node. Consider node 2 and node 3 in above tree, they have O(3) and O(3) respectfully. Which means, the sum time of pathSumFrom() from a layer is <= O(n).

```
Overall, the time complexity is: O(n) + height * O(n)
Best case = O(n) + logn * O(n) = O(nlogn)
Worst case = O(n) + n * O(n) = O(n^2)
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
    int pathSum(TreeNode* root, int sum) {
        if (!root) return 0;
        return pathSumInclude(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
    }
private:
    int pathSumInclude(TreeNode* root, const int sum) {
        int reval(0);
        if (root) {
            if (root->val == sum) ++ reval;
            reval += pathSumInclude(root->left, sum - root->val);
            reval += pathSumInclude(root->right, sum - root->val);
        }
        return reval;
    }
};
```

### Solution two

The idea is based on path. When I come to one node, I want to find all paths ended with current node, whose sum equal to target.

Suppose now the hash table preSum stores the prefix sum of the whole path. Then after adding current node's val to the pathsum, if (pathsum-target) is in the preSum, then we know that at some node of path we have a (pathsum-target) preSum, hence we have a path of target. Actually, it is the path starting from that node.

Now the problem is how to maintain this preSum table? Since one path's preSum is different from others, we have to change it. However, we should notice that we can reuse the most part of the preSum table. If we are done with current node, we just need to delete the current pathsum in the preSum, and leave all other prefix sum in it. Then, in higher layers, we can forget everything about this node (and its descendants).


```cpp
class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        int res = 0;
        unordered_map<int, int> prev_sums;
        prev_sums[0] = 1; 
        dfs(root, prev_sums, 0, res, sum);
        return res;
    }
    
    void dfs(TreeNode* root, unordered_map<int, int> &prev_sums, int cur_sum, int &res, const int sum){
        if(root == NULL) return;
        cur_sum = cur_sum + root->val;
        if(prev_sums.find(cur_sum - sum) != prev_sums.end()){
            res += prev_sums[cur_sum - sum];
        }
        prev_sums[cur_sum]++; // Add current pathsum
        dfs(root->left, prev_sums, cur_sum, res, sum);
        dfs(root->right, prev_sums, cur_sum, res, sum);
        prev_sums[cur_sum]--; // this deletes current pathsum and leave all previous sum
    }
};
```
