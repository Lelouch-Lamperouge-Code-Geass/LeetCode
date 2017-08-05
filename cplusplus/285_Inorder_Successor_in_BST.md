Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null.

# Solution

__Time complexity O(h), space complexity O(1)__

```cpp
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (root == NULL || p == NULL) return NULL;
        
        TreeNode *suc = NULL;
        while (root != NULL) {
            if (root->val <= p->val) {
                root = root->right;
            } else {
                suc = root;
                root = root->left;
            }
        }
        
        return suc;
    }
};
```


#### Java recursive version

```java
public TreeNode successor(TreeNode root, TreeNode p) {
  if (root == null)
    return null;

  if (root.val <= p.val) {
    return successor(root.right, p);
  } else {
    TreeNode left = successor(root.left, p);
    return (left != null) ? left : root;
  }
}
```

```java
public TreeNode predecessor(TreeNode root, TreeNode p) {
  if (root == null)
    return null;

  if (root.val >= p.val) {
    return predecessor(root.left, p);
  } else {
    TreeNode right = predecessor(root.right, p);
    return (right != null) ? right : root;
  }
}
```
