Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null.

# Solution

The inorder traversal of a BST is the nodes in ascending order. To find a successor, you just need to find the smallest one that is larger than the given value since there are no duplicate values in a BST. It just like the binary search in a sorted list. The time complexity should be O(h) where h is the depth of the result node. succ is a pointer that keeps the possible successor. Whenever you go left the current root is the new possible successor, otherwise the it remains the same.

Initially, the suc is nullptr, and we are at root node. As long as we are moving to right child, suc will not be changed. suc will only be updated when we turn left. Turning left means we meet a smaller node which is larger than the give value. 

Only in a balanced BST O(h) = O(log n). In the worst case h can be as large as n.

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
