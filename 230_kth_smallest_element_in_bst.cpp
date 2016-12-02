/* Solution 1 */
class Solution {
public:
  int kthSmallest(TreeNode* root, int k) {
    TreeNode* curr = in_order_search(root,k);
    return !curr ? INT_MIN : curr->val;
  }
private:
  TreeNode* in_order_search(TreeNode* root,int & k) {
    if (!root || k<=0) return nullptr;
    TreeNode* reval = in_order_search(root->left,k);
    if (reval) return reval;
    if (k==1) return root;
    --k; // deduct current node
    return in_order_search(root->right,k);
  }
};

/* Solution 2*/
class Solution {
public:
  int kthSmallest(TreeNode* root, int k) {
    if(!root || k<=0) return INT_MIN;
    stack<TreeNode*> my_stack;
    while(root || !my_stack.empty()){
      if(root){
        my_stack.push(root);
        root = root->left;
      } else {
        root = my_stack.top();
        -- k;
        if(k==0) return root->val;
        my_stack.pop();
        root = root->right;
      }
    }
    return INT_MIN;
  }
};
