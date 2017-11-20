Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

# Solution

This problem is an easy problem which can be solved recursively using divide-and-conquer paradigm.

By picking the mid point as root node, we divide the sorted array into equally halves.


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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
      return helper(nums,0,nums.size()-1);
    }
    
    TreeNode* helper(vector<int>& nums, int start, int end) {
      if (start > end) return nullptr;
      int mid = start + (end - start)/2;
      TreeNode *curr = new TreeNode(nums[mid]);
      curr->left = helper(nums,start,mid-1);
      curr->right = helper(nums,mid+1,end);
      return curr;
    }
};
```
