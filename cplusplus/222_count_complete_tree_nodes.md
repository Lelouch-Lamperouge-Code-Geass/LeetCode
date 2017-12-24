Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from [Wikipedia](https://en.wikipedia.org/wiki/Binary_tree#Types_of_binary_trees):

In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

# Solution
                                                      

/* Solution 1*/
class Solution {
public:
    int countNodes(TreeNode* root) {
        int reval(0);
        TreeNode *curr(nullptr);
        while(root) {
            curr = root->left;
            int left_height(0);
            while (curr) {
                ++ left_height;
                curr = curr->left;
            }
            
            curr = root->right;
            int right_height(0);
            while (curr) {
                ++ right_height;
                curr = curr->left;
            }
            
            if (left_height > right_height) {
                reval += 1<<right_height;
                root = root->left;
            } else {
                reval += 1<<left_height;
                root = root->right;
            }
        }
        return reval;
    }
};

/* Solution 2*/
class Solution {
public:
    int countNodes(TreeNode* root) {
        if(!root) return 0;
        int height(0), sum(0), i(0);
        TreeNode *t(root), *t0(nullptr);
        //get the height of the tree;
        while(t) {
            t = t->left, ++ height;
        }
        t = root;
        int level = height - 2; //levels under the child of root;
        while(level >=0 ) //collect the bottom-level nodes by halving them apart;
        {
            t0 = t->left;
            for(i = 0; i < level; ++i) t0 = t0->right; 
            if(t0) { sum += 1<<level; t = t->right; } //rightmost node is not null;
            else t = t->left;
            
            -- level; //move to the next level;
        }
        if(t) sum++; //if it's a complete tree, collect the last right node;
        return sum+((1<<(height-1))-1);
    }
};
