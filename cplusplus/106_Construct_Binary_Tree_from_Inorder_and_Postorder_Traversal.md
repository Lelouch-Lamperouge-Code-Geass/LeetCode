Given inorder and postorder traversal of a tree, construct the binary tree.

__Note:__

You may assume that duplicates do not exist in the tree.

# Solution

The the basic idea is to take the last element in postorder array as the root, find the position of the root in the inorder array; then locate the range for left sub-tree and right sub-tree and do recursion.

Here are the postorder and inorder traversal of one tree. __Note that it doesn't have to be a BST, just binary tree is fine.__

I use this BST as an example so that you can draw the picture more easily.

```
Inorder  ： 2, 5, 7, 10, 12, 17, 23
Postorder :  2, 7, 5, 12, 23, 17, 10
```

The first number in preorder is 10. And we can see that 10 can divide inorder tree into two parts. The left part 2, 5, 7 formed the left tree, and the right part 12, 17, 23 form the right tree. And obviously 10 is the root number here.

We can build the left tree based on left part

```
Inorder  ： 2, 5, 7 
Postorder :  2, 7, 5 
```

and build the right tree based on right part

```
Inorder  ：  12, 17, 23
Postorder :  12, 23, 17
```

And they are just the same problem with smaller input.

Right now it is very clear that we can use divide and conquer and build the tree recursively.

__Note that if you can use int type for start and begin positions, use them. For std::size_t you need to handle overflow very carefully._ 

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty() || postorder.empty() || postorder.size() != inorder.size()) return nullptr;
        
        return buildTree(postorder, inorder, 0, postorder.size() - 1, 0, inorder.size() - 1);
    }
    
private:
    TreeNode* buildTree(const vector<int>& postorder,
                       const vector<int>& inorder,
                       int pb,
                       int pe,
                       int ib,
                       int ie) {
        if (pb > pe) {
            return nullptr;
        } else if (pb == pe) {
            return new TreeNode(postorder[pe]);
        } else {
            int cur_val = postorder[pe];
            
            int inorder_pos = std::find(inorder.begin() + ib, 
                        inorder.begin() + ie + 1, cur_val) - inorder.begin();
            int left_nodes(inorder_pos - ib), right_nodes(ie - inorder_pos);    
            
            TreeNode *root = new TreeNode(cur_val);
            root->left = buildTree(postorder, inorder, pb, pb + left_nodes - 1,  ib, inorder_pos - 1);
            root->right = buildTree(postorder, inorder, pe - right_nodes, pe - 1, inorder_pos + 1, ie);
            
            return root;
        }
    }
};
```
