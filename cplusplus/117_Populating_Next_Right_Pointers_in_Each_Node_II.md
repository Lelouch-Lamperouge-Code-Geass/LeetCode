Follow up for problem ["Populating Next Right Pointers in Each Node"](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/).

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,

```
        1
       /  \
      2    3
     / \    \
    4   5    7
```
                                                                      
After calling your function, the tree should look like:

```
        1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL
```
                                                                      
# Solution
__Time complexity O(N), space complexity O(1)__

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
        TreeLinkNode *next_level_head(nullptr), *next_level_pre(nullptr);
        while (root) {
            
            if (root->left) {
                if (!next_level_head) {
                    next_level_head = root->left;
                    next_level_pre = root->left;
                } else {
                    next_level_pre->next = root->left;
                    next_level_pre = next_level_pre->next;
                }
            }
            
            if (root->right) {
                if (!next_level_head) {
                    next_level_head = root->right;
                    next_level_pre = root->right;
                } else {
                    next_level_pre->next = root->right;
                    next_level_pre = next_level_pre->next;
                }
            }
            
            if (root->next) {
                root = root->next;
            } else {
                root = next_level_head;
                next_level_head = next_level_pre = nullptr;
            }
        }
    }
};
```

