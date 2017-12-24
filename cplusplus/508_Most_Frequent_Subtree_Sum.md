Given the root of a tree, you are asked to find the most frequent subtree sum. The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.

##### Examples 1

Input:

```
  5
 /  \
2   -3
```

return [2, -3, 4], since all the values happen only once, return all of them in any order.

##### Examples 2

Input:

```
  5
 /  \
2   -5
```

return [2], since 2 happens twice, however -5 only occur once.

Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.

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
    vector<int> findFrequentTreeSum(TreeNode* root) {
        std::unordered_map<int, int> sum_counter;
        int max_freq(0);
        countSubtreeSums(root, sum_counter, max_freq);
        vector<int> reval;
        for (const auto &pair : sum_counter) {
            if (pair.second == max_freq) {
                reval.emplace_back(pair.first);
            }
        }
        return reval;
    }
private:
    // Count substree sum, and return the sum of current root.
    int countSubtreeSums(TreeNode* root,
                         std::unordered_map<int, int> &sum_counter,
                         int &max_freq) {
        if (root) {
            int left_sum = countSubtreeSums(root->left, sum_counter, max_freq);
            int right_sum = countSubtreeSums(root->right, sum_counter, max_freq);
            int cur_sum = root->val + left_sum + right_sum;
            ++ sum_counter[cur_sum];
            max_freq = std::max(sum_counter[cur_sum], max_freq);
            return cur_sum;
        } else {
            return 0;
        }
    }
};
```
