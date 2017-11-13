Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.

Note:

* Given target value is a floating point.

* You are guaranteed to have only one unique value in the BST that is closest to the target.


# Solution

Notice that here we have a binary search tree, and we should know how to use its characteristics.

The key point is that, the value whice is equal to the target, or closest to the target, will be the nodes on the "search path" to find target.

### Solution one, iterative

Walk the path down the tree close to the target, return the closest value on the path. 
Think about why the closest value is definitely on this path.

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
    int closestValue(TreeNode* root, double target) {
        if (!root) throw std::invalid_argument("root can't be null!");
        int reval = root->val;
        double diff = std::fabs(root->val - target);
        while (root) {
            double cur_diff = std::fabs(root->val - target);
            if (cur_diff < diff) {
                reval = root->val;
                diff = cur_diff;
            }
            if (root->val > target) {
                root = root->left;
            } else if (root->val < target){
                root = root->right;
            } else {
                return root->val;
            }
        }
        
        return reval;
    }
};
```

### Solution two, Recursive

```cpp
int closestValue(TreeNode* root, double target) {
    int a = root->val;
    auto kid = target < a ? root->left : root->right;
    if (!kid) return a;
    int b = closestValue(kid, target);
    return abs(a - target) < abs(b - target) ? a : b;
}
```
