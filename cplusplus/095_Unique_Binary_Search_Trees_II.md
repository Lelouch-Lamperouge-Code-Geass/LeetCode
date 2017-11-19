Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.  

For example,  
Given n = 3, your program should return all 5 unique BST's shown below.  

```
   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
```

# Solution

I start by noting that 1..n is the in-order traversal for any BST with nodes 1 to n. So if I pick i-th node as my root, the left subtree will contain elements 1 to (i-1), and the right subtree will contain elements (i+1) to n. I use recursive calls to get back all possible trees for left and right subtrees and combine them in all possible ways with the root.

__Note:__

1. There are multiple possibilities for left trees. The same for right trees. Therefore, once we pick a number as a root. The total number of trees we can generated is ``` number_of_left_trees * number_of_right_trees```.

2. When we generate a new tree, we need clone every left tree and right tree. That's because every tree should be independent. You don't want two different root nodes' left pointers point to the same left tree.

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
    vector<TreeNode*> generateTrees(int n) {
        if(n<=0) return  vector<TreeNode*>();
        return generateBST(1, n);
    }
private:
    // Clone a tree.
    TreeNode* cloneTree(TreeNode *root){
        if (!root) return nullptr;
        
        TreeNode *clone_root = new TreeNode(root->val);
        clone_root->left = cloneTree(root->left);
        clone_root->right= cloneTree(root->right);
        
        return clone_root;
    }
    
    vector<TreeNode*> generateBST(int begin, int end) {
        if (begin > end) {
            return vector<TreeNode*>(1, nullptr);
        } else if (begin == end) {
            return vector<TreeNode*>(1, new TreeNode(begin));
        } else {
            vector<TreeNode*> reval;
            for (int i = begin; i <= end; ++i) {

                vector<TreeNode*> lefts = generateBST(begin, i - 1);
                vector<TreeNode*> rights = generateBST(i + 1, end);
                for (TreeNode* left : lefts) {
                    for (TreeNode* right : rights) {
                        TreeNode *root = new TreeNode(i);
                        root->left = cloneTree(left); // Note that we need clone the left tree here
                        root->right = cloneTree(right); // Note that we need clone the right tree here
                        reval.emplace_back(root);
                    }
                }
            }
            
            return reval;
        }
    }
};
```
