Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

```
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
```

# Solution

The brute-force solution for this problem is to exhaust all the combinations and check the length of each one, if its length is k, add to final list. Here we can see that each combination is a candidate. And we can avoid redundant calculations by not extending combination when length is already k.
  
So this is a backtracking problem.

The backtracking algorithm enumerates a set of partial candidates that, in principle, could be completed in various ways to give all the possible solutions to the given problem. The completion is done incrementally, by a sequence of candidate extension steps. Conceptually, the partial candidates are represented as the nodes of a tree structure, the potential search tree. Each partial candidate is the parent of the candidates that differ from it by a single extension step; the leaves of the tree are the partial candidates that cannot be extended any further.
  
For each number from 1 to n, we can either add it or ignore it. __Note that here we have no duplicates.__ 

On the potential search tree, each tree node  in this problem will only have two children (some backtracking problem have more children). We can say that goes to left child means add the number, goes to right child means ignore it. 

```cpp
class Solution {
public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int>  temp;
    Backtracking(res,temp,1,n,k);
    return res;
  }
private:
  void Backtracking(vector<vector<int>> & res, vector<int> & temp, int start,int n,int k){
    if (temp.size()==k) {
      res.push_back(temp);
    } else {
      if (start>n) return;
      // add current item, go to left child
      temp.push_back(start);
      Backtracking(res,temp,start+1,n,k);
      temp.pop_back(); // revert back
      // not add current item,go to right child
      Backtracking(res,temp,start+1,n,k);
    }
  }
};
```

We can make the recursion tree shorter.

```cpp  
class Solution {
public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    if(k<0 || n<k) return res;
    vector<int> temp;
    backtracking(res,temp,n,k,1);
    return res;
  }
private:
  void backtracking(vector<vector<int>> & res,
                    vector<int>&temp,
                    const int n,
                    const int k,
                    const int start){
    if(temp.size()==k){
      res.push_back(temp);
    } else {
      if(start>n) return;
      for(int i=start;i<=n;++i){
        temp.push_back(i);
        backtracking(res,temp,n,k,i+1);
        temp.pop_back();
      }
    }
  }
};
```

```
0 0 #initialization
1 0
1 1 #push_back
1 2 #push_back
1 3 #push_back
1 4 #push_back
1 5
2 5
2 2 #push_back
2 3 #push_back
2 4 #push_back
...
3 4 #push_back
3 5
4 5
4 4
4 5
5 5 #stop
```

```cpp
class Solution {
public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> result;
    int i = 0;
    vector<int> p(k, 0);
    while (i >= 0) {
      p[i]++;
      if (p[i] > n) --i;
      else if (i == k - 1) result.push_back(p);
      else {
        ++i;
        p[i] = p[i - 1];
      }
    }
    return result;
  }

};
```

# Knowledge

### Backtracking

Backtracking is a general algorithm for finding all (or some) solutions to some computational problems, notably constraint satisfaction problems, that incrementally builds candidates to the solutions, and abandons each __partial candidate__ ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.

_Backtracking can be applied only for problems which admit the concept of a "partial candidate solution" and a relatively quick test of whether it can possibly be completed to a valid solution._ It is useless, for example, for locating a given value in an unordered table. When it is applicable, however, backtracking is often much faster than brute force enumeration of all complete candidates, since it can eliminate a large number of candidates with a single test.
                                                                                         
The backtracking algorithm enumerates a set of __partial candidates__ that, in principle, could be completed in various ways to give all the possible solutions to the given problem. The completion is done incrementally, by a sequence of candidate extension steps.
Conceptually, the partial candidates are represented as the nodes of a tree structure, the __potential search tree__. Each partial candidate is the parent of the candidates that differ from it by a single extension step; the leaves of the tree are the partial candidates that cannot be extended any further.
                                                                                         
The backtracking algorithm traverses this search tree recursively, from the root down, in _depth-first order_. At each node c, the algorithm checks whether c can be completed to a valid solution. _If it cannot, the whole sub-tree rooted at c is __skipped (pruned)__._ Otherwise, the algorithm (1) checks whether c itself is a valid solution, and if so reports it to the user; and (2) recursively enumerates all sub-trees of c. The two tests and the children of each node are defined by user-given procedures.
                                                                                         
Therefore, the actual search tree that is traversed by the algorithm is only a part of the potential tree. __The total cost of the algorithm is the number of nodes of the actual tree times the cost of obtaining and processing each node.__ This fact should be considered when choosing the potential search tree and implementing the pruning test.                                                                                         
       
