Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null.

# Solution

The inorder traversal of a BST is the nodes in ascending order. To find a successor, you just need to find the smallest one that is larger than the given value since there are no duplicate values in a BST. It just like the binary search in a sorted list. The time complexity should be O(h) where h is the depth of the result node. succ is a pointer that keeps the possible successor. Whenever you go left the current root is the new possible successor, otherwise the it remains the same.

Initially, the suc is nullptr, and we are at root node. As long as we are moving to right child, suc will not be changed. suc will only be updated when we turn left. Turning left means we meet a smaller node which is larger than the give value. 

Only in a balanced BST O(h) = O(log n). In the worst case h can be as large as n.

```
The idea is to compare root's value with p's value if root is not null, and consider the following two cases:

1. root.val > p.val. In this case, root can be a possible answer, so we store the root node first and call it res. 
However, we don't know if there is anymore node on root's left that is larger than p.val. So we move root to its left and check again.

2. root.val <= p.val. In this case, root cannot be p's inorder successor, neither can root's left child. 
So we only need to consider root's right child, thus we move root to its right and check again.
```

__Time complexity O(h), space complexity O(1)__

```cpp
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (root == NULL || p == NULL) return NULL;
        
        TreeNode *suc = NULL;
        while (root != NULL) {
            if (root->val > p->val) {
                suc = root;
                root = root->left;
            } else {
                root = root->right;
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
