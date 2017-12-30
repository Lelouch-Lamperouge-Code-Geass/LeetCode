Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:

Given target value is a floating point.  
You may assume k is always valid, that is: k ≤ total nodes.  
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.  
 

Follow up:  
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?  

Hint:

1. Consider implement these two helper functions:
    * getPredecessor(N), which returns the next smaller node to N.
    * getSuccessor(N), which returns the next larger node to N.
2. Try to assume that each node has a parent pointer, it makes the problem much easier.
3. Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
4. You would need two stacks to track the path in finding predecessor and successor node separately.


# Solution

### Solution one

Maintain a k-size max-heap. The heap stores <diff(val, target), val> pairs.
We traversal the whole tree, and add each node to this heap, whenever the heap size is larger than k, we pop the one with _maximum difference_ out.

__Time complexity is O(N * logK)__.

```cpp
void dfs(TreeNode* root, priority_queue<pair<double, int>>& pq, double target, int k) {
    if(!root) return;
    
    pq.push(make_pair(fabs(target - double(root->val)), root->val));
    
    if(pq.size() > k) 
        pq.pop(); // Pop max element out
        
    dfs(root->left, pq, target, k);
    dfs(root->right, pq, target, k);
}

vector<int> closestKValues(TreeNode* root, double target, int k) {
    priority_queue<pair<double, int>> pq;
    vector<int> result;
    
    dfs(root, pq, target, k);
    while(!pq.empty()) {
        result.push_back(pq.top().second);
        pq.pop();
    }
    
    return result;
}
```

A different style.

```cpp
class Solution {
private:
    struct CompareTo{
         bool operator () (const pair<double, int> &left, const pair<double, int> &right){
            return left.first < right.first;
        }
    };
    void dfs(TreeNode* root, 
             priority_queue<pair<double, int>, vector<pair<double, int>>, CompareTo> &pq, 
             double target, 
             int k) {
        if(!root) return;

        pq.push(make_pair(fabs(target - double(root->val)), root->val));

        if(pq.size() > k) 
            pq.pop(); // Pop max element out

        dfs(root->left, pq, target, k);
        dfs(root->right, pq, target, k);
    }

public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
          priority_queue<pair<double, int>, 
                        vector<pair<double, int>>, 
                        CompareTo> pq;
         vector<int> result;

        dfs(root, pq, target, k);
        while(!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }

        return result;
    }
};
```

### Solution two

This problem reveals an interesting property of BST, for any number, the ones which are closer(equal) to it will be on the "search path"(the path to search the node from root, note that the search path here will keep going even after find the node) of the BST. You can draw a picture to understand it better. 

Therefore, the closest predecessors and successors of that target will be on this path. The idea is to compare the predecessors and successors of the closest node to the target, we can use two stacks to track the predecessors and successors, then we compare and pick the closest one to the target and put it to the result list.  A special case is when the BST contains a node whose value equals target.

As we know, inorder traversal gives us sorted predecessors, whereas reverse-inorder traversal gives us sorted successors.


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
private:
    void initializeStackWithInOrder(TreeNode* root, 
                                    double target, 
                                    int k, 
                                    stack<TreeNode*> &nodes, 
                                    bool is_adding_successor) {
        if (root) {
            initializeStackWithInOrder(is_adding_successor ? root->right : root->left, 
                                       target, k, nodes, is_adding_successor);
            
            // Early terminate, no need to traverse the whole tree.
            // Note that, if we find a node whose value is same as target,
            // we add to predecessor. That's why here we have one <= and one <.
            if ((is_adding_successor && root->val <= target) 
                || (!is_adding_successor && root->val > target)) {
                return;
            }
            
            // track the value of current node
            nodes.push(root);
            
            initializeStackWithInOrder(is_adding_successor ? root->left : root->right, 
                                       target, k, nodes, is_adding_successor);
        }
    }
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        // Initialize predecessors and successors stacks.
        stack<TreeNode*> predecessors, successors;
        initializeStackWithInOrder(root, target, k, predecessors, false);
        initializeStackWithInOrder(root, target, k, successors, true);
        
        vector<int> reval;
        while (k-- > 0) {
            if (successors.empty()) {
                // No sucessors anymore
                reval.emplace_back(predecessors.top()->val);
                predecessors.pop();
            } else if(predecessors.empty()) {
                // No predecessors anymore
                reval.emplace_back(successors.top()->val);
                successors.pop();
            } else {
                double succ_diff  = std::fabs(successors.top()->val - target);
                double pred_diff  = std::fabs(predecessors.top()->val - target);
                if (succ_diff < pred_diff) {
                    reval.emplace_back(successors.top()->val);
                    successors.pop();
                } else {
                    reval.emplace_back(predecessors.top()->val);
                    predecessors.pop();
                }
            }
        }
        return reval;
    }
};
```

A different style.

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
private:
    // Travelling down the BST from root, keep adding predecessors and successors
    // of target value on the path, stop when root is null or meet a node equals the target.
    void initializePredecessorsAndSuccessorsStack(TreeNode* root,
                                                  const double target,
                                                  stack<TreeNode*> &predecessors,
                                                  stack<TreeNode*> &successors) {
        while (root) {
            if (root->val > target) {
                successors.push(root);
                root = root->left;
            } else if (root->val < target) {
                predecessors.push(root);
                root = root->right;
            } else {
                successors.push(root);
                predecessors.push(root);
                break;
            }
        }
    }
    // Return the value of current predecessor.
    // And add predecessors before current predecessor.
    int getNextPredecessor(stack<TreeNode*> &predecessors) {
        int reval = predecessors.top()->val;
        TreeNode *curr = predecessors.top();
        predecessors.pop();
        curr = curr->left;
        while (curr) {
            predecessors.push(curr);
            curr = curr->right;
        }
        return reval;
    }
    // Return the value of current successor.
    // And add successors before current successor.
    int getNextSuccessors(stack<TreeNode*> &successors) {
        int reval = successors.top()->val;
        TreeNode *curr = successors.top();
        successors.pop();
        curr = curr->right;
        while (curr) {
            successors.push(curr);
            curr = curr->left;
        }
        return reval;
    }
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        stack<TreeNode*> predecessors, successors;
        initializePredecessorsAndSuccessorsStack(root, target, predecessors, successors);
        if (!predecessors.empty() && !successors.empty() 
            && predecessors.top() == successors.top()) {
            // If there is a node equals to target, then both stacks will have that node on top.
            // Need pop one out.
            getNextPredecessor(predecessors);
        }
        vector<int> reval;
        while (k-- > 0) {
            if (successors.empty()) {
                // No sucessors anymore
                reval.emplace_back(getNextPredecessor(predecessors));
            } else if(predecessors.empty()) {
                // No predecessors anymore
                reval.emplace_back(getNextSuccessors(successors));
            } else {
                double succ_diff  = std::fabs(successors.top()->val - target);
                double pred_diff  = std::fabs(predecessors.top()->val - target);
                if (succ_diff < pred_diff) {
                    reval.emplace_back(getNextSuccessors(successors));
                } else {
                    reval.emplace_back(getNextPredecessor(predecessors));
                }
            }
        }
        return reval;
    }
};
```

