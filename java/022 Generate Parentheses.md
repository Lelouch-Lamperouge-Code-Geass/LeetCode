Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
  
```
For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
```

# Solution

### Analysis

This problem can be resolved with backtracking.

The idea here is to only add '(' and ')' that we know will guarantee us a solution (instead of adding 1 too many close). Once we add a '(' we will then discard it and try a ')' which can only close a valid '('. Each of these steps are recursively called.
  
You can draw a binary tree begin with an empty string, add ( when go to left child and add ) when go to right child. Make sure on any node, left ( are not less than right ). 


### About backtracking
  
The backtracking algorithm enumerates a set of __partial candidates__ that, in principle, could be completed in various ways to give all the possible solutions to the given problem. The completion is done incrementally, by a sequence of candidate extension steps.
  
Conceptually, the partial candidates are represented as the nodes of a tree structure, the __potential search tree__. Each partial candidate is the parent of the candidates that differ from it by a single extension step; the leaves of the tree are the partial candidates that cannot be extended any further.
  
The backtracking algorithm traverses this search tree recursively, from the root down, in __depth-first order__. At each node c, the algorithm checks whether c can be completed to a valid solution. If it cannot, the whole sub-tree rooted at c is __skipped (pruned)__. Otherwise, the algorithm (1) checks whether c itself is a valid solution, and if so reports it to the user; and (2) recursively enumerates all sub-trees of c. The two tests and the children of each node are defined by user-given procedures.
  
Therefore, the actual search tree that is traversed by the algorithm is only a part of the potential tree. __The total cost of the algorithm is the number of nodes of the actual tree times the cost of obtaining and processing each node.__ This fact should be considered when choosing the potential search tree and implementing the pruning test.

### Time and space complexity

So how many tree nodes the DFS backtracking need process?

Without prune, the search tree is a full binary tree, the totla nodes will be 2^(n+n), note that here n means the amount of parenthesis pairs. With prune, you will see half of the nodes will be removed, therefore the total tree nodes is 2^n.
Since the cost of procesing each node is O(1),  the __time complexity is O(2^n)__.
  
How about space complexity?
  
We used recursion here, so the space complexity is O(height of the tree).

### Code

  
```java
class Solution {
    public List<String> generateParenthesis(int n) {
        List<String> reval = new ArrayList<String>();
        if (n > 0) {
            int leftRemain = n, rightRemain = n;
            addParenthesis(reval, "", n, n);
        }
        return reval;
    }

    private void addParenthesis(final List<String> reval,
                                final String candidate,
                                final int leftRemain,
                                final int rightRemain) {
        if (leftRemain == 0 && rightRemain == 0) {
            reval.add(candidate);
        } else {
            if (leftRemain > 0 && leftRemain <= rightRemain) {
                addParenthesis(reval, candidate + '(', leftRemain - 1, rightRemain);
            }

            if (leftRemain < rightRemain) {
                addParenthesis(reval, candidate + ')', leftRemain, rightRemain - 1);
            }
        }
    }
}
```



```java
public class Solution {
    public List<String> generateParenthesis(int n) {
        List<String> reval = new ArrayList<String>();
        int left_paren = n, right_paren = n;
        StringBuilder sb = new StringBuilder();
        checkWithBacktracking(reval, left_paren, right_paren, sb);
        return reval;
    }
    
    private void checkWithBacktracking(List<String> list,
                                int left_paren, 
                                int right_paren,
                                StringBuilder sb) {
        if (left_paren == 0 && right_paren == 0) {
            list.add(sb.toString());
        } else {
            // try add '('
            if (left_paren > 0) {
                sb.append('(');
                checkWithBacktracking(list, left_paren - 1, right_paren, sb);
                sb.setLength(sb.length() - 1);
            }
            
            // try add ')'
            if (left_paren < right_paren) {
                sb.append(')');
                checkWithBacktracking(list, left_paren, right_paren - 1, sb);
                sb.setLength(sb.length() - 1);
            }
        }
    }
}
```
