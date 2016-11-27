/* Solution 1*/
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return root;
        TreeNode *left_root(root->left);
        root->left = invertTree(root->right);
        root->right = invertTree(left_root);
        return root;
    }
};

/* Solution 2*/
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return root;
        stack<TreeNode*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            TreeNode * curr = nodes.top();
            nodes.pop();
            TreeNode * left_child = curr->left;
            curr->left = curr->right;
            curr->right = left_child;
            if (curr->left) nodes.push(curr->left);
            if (curr->right) nodes.push(curr->right);
        }
        return root;
    }
};
