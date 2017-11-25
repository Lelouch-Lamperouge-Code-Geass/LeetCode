Given a binary tree, return the postorder traversal of its nodes' values.  

For example:  
Given binary tree {1,#,2,3},  

```
   1
    \
     2
    /
   3
```

return [3,2,1].

__Note:__ Recursive solution is trivial, could you do it iteratively?

# Solution

### Solution 1, Morris in-order traversal using threading

Time complexity O(number of nodes), space complexity O(1).

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> reval;
        TreeNode dummy(0);
        dummy.left = root;
        root = & dummy;
        while(root){
            if(root->left){
                TreeNode *pred(root->left);
                while(pred->right && pred->right!=root){
                    pred = pred->right;
                }
                if(pred->right!=root){
                    //first time access current node
                    pred->right = root;
                    root = root->left;
                } else {
                    //second time access current node
                    pred->right = nullptr;//revert back
                     
                    TreeNode *temp(root->left);
                    vector<int> vec;
                    while(temp){
                        vec.push_back(temp->val);
                        temp = temp->right;
                    }
                    reval.insert(reval.end(),vec.rbegin(),vec.rend());
					
                    root = root->right;
                }
            } else {
                root = root->right;
            }
        }
        return reval;
    }
};
```

### Solution 2, iterative solution with a stack

__Time complexity O(number of nodes), space complexity O(depth of tree).__

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> reval;
        if(!root) return reval;
        stack<TreeNode *> nodes;
        nodes.push(root);
        while(!nodes.empty()){
            root = nodes.top();
            nodes.pop();
            reval.push_back(root->val);
            if(root->left) nodes.push(root->left);
            if(root->right) nodes.push(root->right);
        }
        std::reverse(reval.begin(),reval.end());
        return reval;
    }
};
```

### Solution 3, recursive solution

__Time complexity O(number of nodes), space complexity O(depth of recursion).__

```cpp
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> reval;
        postorder(root, reval);
        return reval;
    }
private:
    void postorder(TreeNode* root, vector<int> &reval) {
        if (root) {
            postorder(root->left, reval);
            postorder(root->right, reval);
            reval.emplace_back(root->val);
        }
    }
};
```

# Knowledge

### Morris in-order traversal using threading

![alt](https://2.bp.blogspot.com/-Oi7ZBzR9Wzs/V5YWWkB1FII/AAAAAAAAY8k/hVhzEWlwigM5HpHHN1VIZITzw9By4zAOACLcB/s1600/threadedBT.png)

A binary tree is threaded by making every left child pointer (that would otherwise be null) point to the in-order predecessor of the node (if it exists) and every right child pointer (that would otherwise be null) point to the in-order successor of the node (if it exists).

__Advantages:__

1. Avoids recursion, which uses a call stack and consumes memory and time.  
2. The node keeps a record of its parent.  

__Disadvantages:__

1. The tree is more complex.  
2. We can make only one traversal at a time.  
3. It is more prone to errors when both the children are not present and both values of nodes point to their ancestors.  

Morris traversal is an implementation of in-order traversal that uses threading:

1. Create links to the in-order successor.  
2. Print the data using these links.  
3. Revert the changes to restore original tree.    

### Threaded binary tree

In computing, a threaded binary tree is a binary tree variant that allows fast traversal: given a pointer to a node in a threaded tree, it is possible to cheaply find its in-order successor (and/or predecessor).

![alt](https://upload.wikimedia.org/wikipedia/commons/7/7a/Threaded_tree.svg)

A threaded binary tree defined as follows: "A binary tree is threaded by making all right child pointers that would normally be null point to the inorder successor of the node (if it exists), and all left child pointers that would normally be null point to the inorder predecessor of the node."

