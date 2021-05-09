Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.


##### Example 1:

```
Input: k = 3, n = 7

Output:

[[1,2,4]]
```

##### Example 2:

```
Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]
```

# Solution

The brute-force solution to this problem is to exhaust all the possible combinations of k nubmers, and check each combination's sum is equals to n or not. However, this will result in combinatorial time complexity.
    
How can we do better? Backtracking. Basically, for any problem that you find you may need to exhaust all possible candidates, then using backtracking to rule out invalid candidates as soon as possible can improve the performance dramastically.
    
__Backtracking__ is a general algorithm for finding all (or some) solutions to some computational problems, notably constraint satisfaction problems, that incrementally builds candidates to the solutions, and abandons each partial candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.    
    
_Backtracking can be applied only for problems which admit the concept of a "partial candidate solution" and a relatively quick test of whether it can possibly be completed to a valid solution._ It is useless, for example, for locating a given value in an unordered table. When it is applicable, however, backtracking is often much faster than brute force enumeration of all complete candidates, since it can eliminate a large number of candidates with a single test.
    
Conceptually, the partial candidates are represented as the nodes of a tree structure, the __potential search tree__. Each partial candidate is the parent of the candidates that differ from it by a single extension step; the leaves of the tree are the partial candidates that cannot be extended any further.
    
The backtracking algorithm traverses this search tree recursively, from the root down, in depth-first order. At each node c, the algorithm checks whether c can be completed to a valid solution. If it cannot, the whole sub-tree rooted at c is __skipped (pruned)__. Otherwise, the algorithm (1) checks whether c itself is a valid solution, and if so reports it to the user; and (2) recursively enumerates all sub-trees of c. The two tests and the children of each node are defined by user-given procedures.
    
Therefore, the actual search tree that is traversed by the algorithm is only a part of the potential tree. The total cost of the algorithm is the number of nodes of the actual tree times the cost of obtaining and processing each node. This fact should be considered when choosing the potential search tree and implementing the pruning test.    
 
Here, let's draw a tree structure begin with an root node means empty(I use 0 here). For this rood node, it's children can be from 1 to 9. And for any tree node with value num, it's children can be from num + 1 to 9.
    
When we reach any tree node, we check whether the candidate(the temp vector) we have so far can meet our requirement. If so, we add it to final result, otherwise keep going to children nodes.
    
Of course, we need to prune our tree as soon as possible, therefore whenever we can't add more number to temp vector, we need stop seeking in child tree.
    
What's the time compleixty here? O(number of tree nodes you visit).  =)    
    
```cpp
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> reval;
        vector<int> temp;
        populateWithBacktracking(reval, temp, 0, n, k, 0);
        return reval;
    }
private:
    void populateWithBacktracking(vector<vector<int>> &reval,
                                  vector<int> &temp,
                                  const int temp_sum,
                                  const int n,
                                  const int k,
                                  const int cur_num) {
        // We visited current tree node
        if (temp.size() == k && temp_sum == n) {
            reval.emplace_back(temp);
        }
        
        if (temp.size() == k) return; // Can't add more numbers
        
        // We keep visit the children nodes of current node
        for (int child = cur_num + 1; child <= 9; ++child) {
            if (temp_sum + child > n) break;
            // Add this child
            temp.emplace_back(child);
            populateWithBacktracking(reval, temp, temp_sum + child, n, k, child);
            temp.pop_back();
        }
    }
};
```

A different style.
    
```cpp
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> temp;
        dfs(res,temp,k,n,1);
        return res;
    }
private:
    void dfs(vector<vector<int>> & res, 
            vector<int> & temp,
            const int k,
            const int n,
            const int start) {
        if (temp.size()==k && n==0) {
            res.push_back(temp);
        } else {
            if (temp.size()==k || n==0) return;
            for (int i=start;i<=9;++i) {
                if (i>n) break;
                temp.push_back(i);
                dfs(res,temp,k,n-i,i+1);
                temp.pop_back();
            }
        }
    }
};
```
