Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.

##### Example 1:

Given tree s:

```
     3
    / \
   4   5
  / \
 1   2
```
 
Given tree t:

```
   4 
  / \
 1   2
```

Return true, because t has the same structure and node values with a subtree of s.

##### Example 2:

Given tree s:

```
     3
    / \
   4   5
  / \
 1   2
    /
   0
```

Given tree t:

```
   4
  / \
 1   2
```

Return false.

# Solution

For each node during pre-order traversal of s, use a recursive function isSame to validate if sub-tree started with this node is the same with t.


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
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (s) {
            if (isSameTree(s, t)) {
                return true;
            }
            return isSubtree(s->left, t) || (isSubtree(s->right, t));
        } else {
            return s == t;
        }
    }
private:
    bool isSameTree(TreeNode *root1, TreeNode *root2) {
        if (!root1 || !root2) {
            return root1 == root2;
        } else {
            if (root1->val != root2->val) {
                return false;
            }
            
            return isSameTree(root1->left, root2->left) && isSameTree(root1->right, root2->right);
        }
    }
};
```
