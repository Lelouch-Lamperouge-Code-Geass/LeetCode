/**
 Time complexity O(N), space complexity O(1)
 * };
 */
class Solution {
public:
  void connect(TreeLinkNode *root) {
    while (root) {
      TreeLinkNode *next_head(nullptr), *pre(nullptr);
      while (root) { // iterate on the current level
        // left child
        if (root->left) {
          if (!pre) {
            next_head = pre = root->left;
          } else {
            pre->next = root->left;
            pre = pre->next;
          }
        }
        // right child
        if (root->right) {
          if (!pre) {
            next_head = pre = root->right;
          } else {
            pre->next = root->right;
            pre = pre->next;
          }
        }
        // move to next node
        root = root->next;
      }

      root = next_head;
    }
  }
};
