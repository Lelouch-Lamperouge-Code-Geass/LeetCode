Given a binary tree

```
struct TreeLinkNode {
   TreeLinkNode *left;
   TreeLinkNode *right;
   TreeLinkNode *next;
}
```

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

__Note:__

* You may only use constant extra space.
* You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

For example,  
Given the following perfect binary tree,   

```
         1
       /  \
      2    3
     / \  / \
    4  5  6  7
```

After calling your function, the tree should look like:

```
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
```
### Solution one. 

This solution is straightforward. We traverse the nodes level by level.

And in the inner loop when we are scanning one level, we adjust the nodes' next pointers on the next level.

__Space complexity  O(1). Time complexity O(n), n is the number of nodes.__

```cpp
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        TreeLinkNode *head(root), *curr(nullptr);
        while (head && head->left) {
          // Begin traversing nodes on this level, and adjust 
          // the nodes' next pointers in the next level.  
          curr = head;
          while (curr) {
            curr->left->next = curr->right;
            if (curr->next) curr->right->next = curr->next->left;
            curr = curr->next;
          }
          // Traversal complete, let's go to next level.  
          head = head->left; 
        }
  }
};
```

### Solution two. 

This works like preorder traversal. 

__Time complexity is O(N), but space complexity is O(logN) considering the recursion stack.__

```cpp
class Solution {
public:
  void connect(TreeLinkNode *root) {
    if (!root) return;
    if (root->left) {
      root->left->next = root->right;
    }

    if (root->right && root->next) {
      root->right->next = root->next->left;
    }

    connect(root->left);
    connect(root->right);
  }
};
```

# Solution three

```cpp
class Solution {
public:
  void connect(TreeLinkNode *root) {
    if(!root) {
      return;
    } else {
      TreeLinkNode *next_head(nullptr),*next_pre(nullptr);
      while(root){
        if(root->left){
          if(!next_head) next_head = root->left;
          if(next_pre) next_pre->next = root->left;
          next_pre = root->left;
        }

        if(root->right){
          if(!next_head) next_head = root->right;
          if(next_pre) next_pre->next = root->right;
          next_pre = root->right;
        }

        root = root->next; //go to next node
        if(!root) {
          root = next_head; //go to next level
          next_head = next_pre = nullptr;//reset
        }
      }
    }
  }
};
```
