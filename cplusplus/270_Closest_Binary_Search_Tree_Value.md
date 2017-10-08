Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.

Note:

* Given target value is a floating point.

* You are guaranteed to have only one unique value in the BST that is closest to the target.


# Solution

### Solution one, Recursive

```cpp
int closestValue(TreeNode* root, double target) {
    int a = root->val;
    auto kid = target < a ? root->left : root->right;
    if (!kid) return a;
    int b = closestValue(kid, target);
    return abs(a - target) < abs(b - target) ? a : b;
}
```

### Solution two, iterative

Walk the path down the tree close to the target, return the closest value on the path. 
Think about why the closest value is definitely on this path.

```cpp
int closestValue(TreeNode* root, double target) {
    int closest = root->val;
    while (root) {
        if (abs(closest - target) >= abs(root->val - target))
            closest = root->val;
        root = target < root->val ? root->left : root->right;
    }
    return closest;
}
```
