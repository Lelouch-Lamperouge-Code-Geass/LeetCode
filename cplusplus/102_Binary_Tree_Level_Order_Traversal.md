Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:  
Given binary tree [3,9,20,null,null,15,7],  

```
    3
   / \
  9  20
    /  \
   15   7
 ```
 
 return its level order traversal as:
 
 ```
 [
  [3],
  [9,20],
  [15,7]
]
```

# Solution

### Solution one

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> reval;
        visit(root, 0, reval);
        return reval;
    }
    
private:
    void visit(TreeNode* root, 
               const std::size_t level, 
               vector<vector<int>> &reval) {
        if (root) {
            if (level == reval.size()) {
                reval.emplace_back(vector<int>());
            }
            
            reval[level].emplace_back(root->val);
            
            visit(root->left, level + 1, reval);
            visit(root->right, level + 1, reval);
        }
    }
};
```

### Solution two

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector< vector<int> > reVal;
        if(!root)
            return reVal;
        queue<TreeNode*> myQueue;
        vector<int> curLevel;
        myQueue.push(root);
        myQueue.push(NULL);//push NULL as a mark of level end
        TreeNode *curNode(NULL);
        while(!myQueue.empty() )
        {
            curNode = myQueue.front();
            myQueue.pop();
            if(!curNode)//NULL node, level end
            {
                reVal.push_back(curLevel);
                curLevel.clear();
                if(!myQueue.empty())
                    myQueue.push(NULL);//add mark 
            }
            else
            {
                curLevel.push_back(curNode->val);
                if(curNode->left) myQueue.push(curNode->left);
                if(curNode->right) myQueue.push(curNode->right);
            }
        }
        return reVal;
    }
};
```
