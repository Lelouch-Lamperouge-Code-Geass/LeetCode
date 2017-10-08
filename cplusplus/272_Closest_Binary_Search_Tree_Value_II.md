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

Maintain a k-size min-heap. The heap stores <diff(val, target), val> pairs.
We traversal the whole tree, and add each node to this heap, eventually we will get result from this heap.

Time complexity is O(klogn), worst case when k==n it is O(nlogn).

```cpp
void dfs(TreeNode* root, priority_queue<pair<double, int>>& pq, double target, int k) {
    if(!root) return;
    
    pq.push(make_pair(fabs(target - double(root->val)), root->val));
    
    if(pq.size() > k) 
        pq.pop();
        
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

### Solution two

The idea is to compare the predecessors and successors of the closest node to the target, we can use two stacks to track the predecessors and successors, then we compare and pick the closest one to the target and put it to the result list.

Following the hint, I use a predecessor stack and successor stack. I do a logn traversal to initialize them until I reach the null node. Then I use the getPredecessor and getSuccessor method to pop k closest nodes and update the stacks.

I think this is a O(k + logN) solution.

According the follow up question, for a balanced BST, the size of "prec" and "suc" is bounded by logN. Each time, we call getPrec or getSuc, we may kind of shrink/enlarge the stack, but they are still bounded by logN. The amortized complexity will be O(1) for get, since we can consider it like "lazy traverse".



```java
public class Solution {
    public List<Integer> closestKValues(TreeNode root, double target, int k) {
        List<Integer> ret = new LinkedList<>();
        Stack<TreeNode> succ = new Stack<>();
        Stack<TreeNode> pred = new Stack<>();
        initializePredecessorStack(root, target, pred);
        initializeSuccessorStack(root, target, succ);
        if(!succ.isEmpty() && !pred.isEmpty() && succ.peek().val == pred.peek().val) {
            getNextPredecessor(pred);
        }
        while(k-- > 0) {
            if(succ.isEmpty()) { // No sucessor anymore
                ret.add(getNextPredecessor(pred));
            } else if(pred.isEmpty()) { // No predecessor anymore
                ret.add(getNextSuccessor(succ));
            } else {
                double succ_diff = Math.abs((double)succ.peek().val - target);
                double pred_diff = Math.abs((double)pred.peek().val - target);
                if(succ_diff < pred_diff) {
                    ret.add(getNextSuccessor(succ));
                } else {
                    ret.add(getNextPredecessor(pred));
                }
            }
        }
        return ret;
    }

    // Binary search, only add node to stack if its value is larger than target.
    private void initializeSuccessorStack(TreeNode root, double target, Stack<TreeNode> succ) {
        while(root != null) {
            if(root.val == target) {
                succ.push(root);
                break;
            } else if(root.val > target) {
                succ.push(root);
                root = root.left;
            } else {
                root = root.right;
            }
        }
    }

     // Binary search, only add node to stack if its value is smaller than target.
    private void initializePredecessorStack(TreeNode root, double target, Stack<TreeNode> pred) {
        while(root != null){
            if(root.val == target){
                pred.push(root);
                break;
            } else if(root.val < target){
                pred.push(root);
                root = root.right;
            } else{
                root = root.left;
            }
        }
    }
    
    private int getNextSuccessor(Stack<TreeNode> succ) {
        TreeNode curr = succ.pop();
        int ret = curr.val;
        curr = curr.right;
        while(curr != null) {
            succ.push(curr);
            curr = curr.left;
        }
        return ret;
    }

    private int getNextPredecessor(Stack<TreeNode> pred) {
        TreeNode curr = pred.pop();
        int ret = curr.val;
        curr = curr.left;
        while(curr != null) {
            pred.push(curr);
            curr = curr.right;
        }
        return ret;
    }
}
```

