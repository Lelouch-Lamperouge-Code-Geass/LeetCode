/***
   Solution one. Space complexity  O(1). Time complexity O(n), n is the number of nodes.
 ***/

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

/***
    Solution two. Time complexity is O(N), but space complexity is O(logN) considering the recursion stack.
 ***/

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

/***
    Solution three
 ***/

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
