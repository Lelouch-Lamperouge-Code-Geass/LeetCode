Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

```
        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4
```         

# Solution

### Solution 1 , recursive
Same solution in several languages. It's recursive and expands the meaning of the function. If the current (sub)tree contains both p and q, then the function result is their LCA. If only one of them is in that subtree, then the result is that one of them. If neither are in that subtree, the result is null/None/nil.

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
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(!root || root==p || root==q) return root;
    TreeNode *left = lowestCommonAncestor(root->left,p,q);
    TreeNode *right = lowestCommonAncestor(root->right,p,q);
    if(left && right) return root;
    else return left? left : right;
  }
};
```

### Solution two, iterative 

To find the lowest common ancestor, we need to find where is p and q and a way to track their ancestors. A parent pointer for each node found is good for the job. After we found both p and q, we create a set of p's ancestors. Then we travel through q's ancestors, the first one appears in p's is our answer.

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    unordered_map<TreeNode*, TreeNode*> parents;
    parents[root] = nullptr;
    queue<TreeNode*> qu;
    qu.push(root);
    while (!parents.count(p) || !parents.count(q)) { // Not found both
        int qsize = (int)qu.size();
        for (int i = 0; i < qsize; ++i) {
            auto node = qu.front();
            qu.pop();
            if (node -> left) {
                parents[node -> left] = node;
                qu.push(node -> left);
            }
            if (node -> right) {
                parents[node -> right] = node;
                qu.push(node -> right);
            }
        }
    }
    unordered_set<TreeNode*> ancestors;
    while (p) ancestors.insert(p), p = parents[p];
    while (q && !ancestors.count(q)) q = parents[q];
    return q;
}
```
