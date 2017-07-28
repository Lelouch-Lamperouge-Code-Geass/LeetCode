Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note: 
You may assume k is always valid, 1 ? k ? BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

# Solution

##### Solution 1 : Depth-frst in-order recursive traversel

  __Worst time complexity is O(number of nodes), when it is a skew tree. Space complexity is O(depth of recursion), or you can say O(tree height).  The call stack is the part of the computer memory, where a recursive algorithm allocates its temporary data.__
  
```cpp
class Solution {
public:
  int kthSmallest(TreeNode* root, int k) {
    TreeNode* curr = in_order_search(root,k);
    return !curr ? INT_MIN : curr->val;
  }
private:
  TreeNode* in_order_search(TreeNode* root,int & k) {
    if (!root || k <= 0) return nullptr;
    TreeNode* reval = in_order_search(root->left, k);
    if (reval) return reval;
    if (k == 1) return root;
    -- k; // deduct current node
    return in_order_search(root->right,k);
  }
};
```

##### Solution 2 : Depth-frst in-order iterative traversel

__Worst time complexity is O(number of nodes), when it is a skew tree. Space complexity is O(depth of recursion), or you can say O(tree height).__

```cpp
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
```
