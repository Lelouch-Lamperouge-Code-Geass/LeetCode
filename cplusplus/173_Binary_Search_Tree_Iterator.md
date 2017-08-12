Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.

# Solution

My idea comes from this: My first thought was to use inorder traversal to put every node into an array, and then make an index pointer for the next() and hasNext(). That meets the O(1) run time but not the O(h) memory. O(h) is really much more less than O(n) when the tree is huge.

This means I cannot use a lot of memory, which suggests that I need to make use of the tree structure itself. And also, one thing to notice is the "average O(1) run time". It's weird to say average O(1), because there's nothing below O(1) in run time, which suggests in most cases, I solve it in O(1), while in some cases, I need to solve it in O(n) or O(h). These two limitations are big hints.

Before I come up with this solution, I really draw a lot binary trees and try inorder traversal on them. We all know that, once you get to a TreeNode, in order to get the smallest, you need to go all the way down its left branch. So our first step is to point to pointer to the left most TreeNode. The problem is how to do back trace. Since the TreeNode doesn't have father pointer, we cannot get a TreeNode's father node in O(1) without store it beforehand. Back to the first step, when we are traversal to the left most TreeNode, we store each TreeNode we met ( They are all father nodes for back trace).

After that, I try an example, for next(), I directly return where the pointer pointing at, which should be the left most TreeNode I previously found. What to do next? After returning the smallest TreeNode, I need to point the pointer to the next smallest TreeNode. When the current TreeNode has a right branch (It cannot have left branch, remember we traversal to the left most), we need to jump to its right child first and then traversal to its right child's left most TreeNode. When the current TreeNode doesn't have a right branch, it means there cannot be a node with value smaller than itself father node, point the pointer at its father node.

hasNext() is O(1) for sure. How can we prove next() has average O(1) complexity?

If the returned TreeNode doesn't have a right branch, it is O(1). If it has a right branch, it will traversal until its right child's left-most TreeNode. Now, considering the code under "// traversal right branch". After I use next() to go through the entire tree once, this part of code will traversal each node with a right child once. The total run time of this part is O(n). And since I go through the entire tree, the average next() run time is O(n) / n = O(1)

__BTW, If we use Morris Traversal, can reduce the space complexity to O(1)__

```cpp
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        addNodesOnLeftmostPath(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !m_nodes.empty();
    }

    /** @return the next smallest number */
    int next() {
        int reval = m_nodes.top()->val;
        TreeNode *right_child = m_nodes.top()->right;
        m_nodes.pop();
        addNodesOnLeftmostPath(right_child);
        return reval;
    }
private:
    void addNodesOnLeftmostPath(TreeNode *node) {
        while (node) {
            m_nodes.emplace(node);
            node = node->left;
        }
    }
    std::stack<TreeNode*> m_nodes;
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
 ```

### Solution with Morris Traversal

__ Haven't complete yet __

We need to find a way to avoid find predecessor again when visit from bottom-up.
Probably need a bool value in TreeNode which is ``` bool should_recover```.

```cpp
class BSTIterator {
public:
    BSTIterator(TreeNode *root)  {
        cur_node = visitLeftmostPath(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return cur_node;
    }

    /** @return the next smallest number */
    int next() {
        int reval = cur_node->val;

        TreeNode* prede = findPredecessor(cur_node);
        if (prede && prede->right == cur_node) { // recover
            prede->right = nullptr;
        } else {
          cur_node = visitLeftmostPath(cur_node->right);
        }
        
        return reval;
    }
private:
    TreeNode *cur_node;
    
    TreeNode* visitLeftmostPath(TreeNode *node) {
        while (node && node->left) {
            TreeNode* prede = findPredecessor(node);
            if (prede && !prede->right) {
                prede->right = node;
            }
            node = node->left;
        }
        return node;
    }
    
    TreeNode* findPredecessor(TreeNode *node) {
        if (!node || !node->left) return nullptr;
        // Find the predecessor of current node(root)
        TreeNode *prede = node->left;
        while(prede->right && prede->right != node){
            prede = prede->right;
        }

        return prede;
    }
};
```
