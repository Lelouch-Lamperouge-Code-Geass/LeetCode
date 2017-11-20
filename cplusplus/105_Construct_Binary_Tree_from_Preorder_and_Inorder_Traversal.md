Given preorder and inorder traversal of a tree, construct the binary tree.

__Note:__

You may assume that duplicates do not exist in the tree.

# Solution

Here are the preorder and inorder traversal of one tree. __Note that it doesn't have to be a BST, just binary tree is fine.__

I use this BST as an example so that you can draw the picture more easily.

```
Inorder  ： 2, 5, 7, 10, 12, 17, 23
Preorder :  10, 5, 2, 7, 17, 12, 23
```

The first number in preorder is 10. And we can see that 10 can divide inorder tree into two parts. The left part 2, 5, 7 formed the left tree, and the right part 12, 17, 23 form the right tree. And obviously 10 is the root number here.

We can build the left tree based on left part

```
Inorder : 2, 5, 7
Preorder : 5, 2, 7
```
and build the right tree based on right part

```
Inorder : 12, 17, 23
Preorder : 17, 12, 23
```

And they are just the same problem with smaller input.

Right now it is very clear that we can use divide and conquer and build the tree recursively.


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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size()) return nullptr;
        
        return buildTree(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }
    
private:
    TreeNode* buildTree(const vector<int>& preorder,
                       const vector<int>& inorder,
                       std::size_t pb,
                       std::size_t pe,
                       std::size_t ib,
                       std::size_t ie) {
        if (pb > pe) {
            return nullptr;
        } else if (pb == pe) {
            return new TreeNode(preorder[pb]);
        } else {
            int cur_val = preorder[pb];
            
            std::size_t inorder_pos = std::find(inorder.begin() + ib, 
                                                inorder.begin() + ie + 1, cur_val) - inorder.begin();
            std::size_t left_nodes(inorder_pos - ib), right_nodes(ie - inorder_pos);    
            TreeNode *root = new TreeNode(cur_val);
            
            root->left = buildTree(preorder, inorder, pb + 1, pb + left_nodes, ib, inorder_pos - 1);
            root->right = buildTree(preorder, inorder, pe - right_nodes + 1, pe, inorder_pos + 1, ie);
            
            return root;
        }
    }
};
```

# Knowledge

### Divide and conquer algorithm

In computer science, __divide and conquer__ is an _algorithm design paradigm_ based on multi-branched recursion. _A divide and conquer algorithm works by recursively breaking down a problem into two or more sub-problems of the same or related type, until these become simple enough to be solved directly. The solutions to the sub-problems are then combined to give a solution to the original problem._

