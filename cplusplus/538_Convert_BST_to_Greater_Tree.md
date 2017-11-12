Given a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus sum of all keys greater than the original key in BST.

##### Example:

```
Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13
```

# Solution

A BST is very similar to a sorted array.

How do we change a sorted array's every entry to the original value plus sum of all bigger values?

We iterate the sorted array backwards, and add the accumulated sum to each entry, it is just that simple.

What about BST? We can do a reverse inorder traversal to traverse the nodes of the tree in descending order. In the process, we keep track of the running sum of all nodes which we have traversed thus far. 

__Time complexity O(number_of_nodes), space complexity O(height_of_the_tree).__

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
    TreeNode* convertBST(TreeNode* root) {
        int sum_of_bigger_elements(0);
        reverseInOrder(root, sum_of_bigger_elements);
        return root;
    }
private:
    void reverseInOrder(TreeNode* root, int &sum_of_bigger_elements) {
        if (root) {
            reverseInOrder(root->right, sum_of_bigger_elements);
            sum_of_bigger_elements += root->val;
            root->val = sum_of_bigger_elements;
            reverseInOrder(root->left, sum_of_bigger_elements);
        }
    }
};
```


