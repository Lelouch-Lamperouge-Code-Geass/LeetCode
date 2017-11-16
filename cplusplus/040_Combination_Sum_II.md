Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

##### Note:
  
* All numbers (including target) will be positive integers.
* The solution set must not contain duplicate combinations.

For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8, 
A solution set is: 

```
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
```

# Solution

__Note that here the numbers can have duplciates!__

The brute-force solution here is to exhaust all the possible combination, and check the sum of each combination is equals to target or not. And we also need a HashSet to perfor deduplciation. The time complexity is combinatorial.
  
How can we improve this?
  
In general, we have two options:

1. Keep the input pattern, which is unsorted, and use an auxiliary data structure to help us.   
2. Reorder the input pattern, for example sorting the input vector. And build algorithm based above the sorted array. Note that in this condition, our time complexity will be at least the same as the sorting algorithm.  
  
Here it is obvious that option 2 might be a better idea.
  
Imagine that we begin with an empty basket. For each number, we have two options, choose or not choose. Once we made that decision, we can check whether the sum passed target value or not. If the sum exceeds target value, there is no point to keep going forward.
  
As you can see, this is a backtracking problem.
  
A backtracking problem enumerates a set of __partial candidates__ that, in principle, could be completed in various ways to give all the possible solutions to the given problem.  The completion is done incrementally, by a sequence of __candidate extension__ steps. Conceptually, the partial candidates are represented as the nodes of a tree structure, the __potential search tree__.
  
For example, let the input array to be [1,1,1,2,2,3,3,4] and the target number to be 5.
  
Now let's begin with an empty basket, the root node is an empty node. How many children this root node should have?
  
If you are saying "3 nodes begin with 1, 2 nodes begin with 2, 2 nodes begin with 3, 1 node begin with 4", then dude you are in big trouble.   Because the second child begin with the second 1 is just a subtree of the first child! You will definitely have duplicates unless you use a HashSet to filter them out before return the results.
  
Therefore, the children of our root node should be "1 node begin with 1, 1 node begin with 2, 1 node begin with 3, and 1 node begin with 4".  For each tree node in this potential search tree, it can't have two children which have the same value! And you will notice that for the iterative part in below solution.

On each node, if we find that the sum is equals to the target, add the valid candidate to our result. Whenever the sum is larger than target value, prune!  

```cpp
class Solution {
public:
  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> temp;
    std::sort(candidates.begin(),candidates.end());
    dfs(res,temp,candidates,target,0);
    return res;
  }
private:
  void dfs(vector<vector<int>> & res,
           vector<int> & temp,
           const vector<int> & candidates,
           int target,
           int start){
    if (target==0) {
      res.push_back(temp);
    } else {
      for (int i=start;i<candidates.size();++i) {
        if (target<candidates[i]) break;
        if (i>start && candidates[i]==candidates[i-1]) continue;
        temp.push_back(candidates[i]);
        dfs(res,temp,candidates,target-candidates[i],i+1);
        temp.pop_back();
      }
    }
  }
};
```

