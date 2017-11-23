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

__Space complexity  O(1). Time complexity O(n), n is the number of nodes.

```cpp
class Solution {
public:
  void connect(TreeLinkNode *root) {
    TreeLinkNode *pre(root), *curr(nullptr);
    while (pre && pre->left) {
      curr = pre;
      while (curr) {
        curr->left->next = curr->right;
        if (curr->next) curr->right->next = curr->next->left;
        curr = curr->next;
      }
      pre = pre->left;
    }
  }
};
```

### Solution two. 

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
