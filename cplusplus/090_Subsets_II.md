Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

```
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
```

# Solution

### Solution 1 

We can treat duplicate element as a spacial element.   
For example, if we have duplicate elements (5, 5), instead of treating them as two elements that are duplicate, we can treat it as one special element 5, but this element has more than two choices: you can either NOT put it into the subset, or put ONE 5 into the subset, or put TWO 5s into the subset. 

```cpp
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        
        vector<vector<int>> reval(1, vector<int>());
        
        const std::size_t nums_size(nums.size());
        std::size_t index(0);
        
        while (index < nums_size) {
            const int cur_num(nums[index]);
            std::size_t count(0);
            
            while (index < nums_size && nums[index] == cur_num) {
                ++ index;
                ++ count;
            }
            
            const std::size_t pre_size(reval.size());
            
            for (std::size_t i = 0; i < pre_size; ++i) {
                for (std::size_t cnt = 1; cnt <= count; ++cnt) {
                    reval.emplace_back(reval[i]);
                    vector<int> &last_item = reval.back(); 
                    last_item.insert(last_item.end(), cnt, cur_num);
                }                
            }
        }
        
        return reval;
    }
};
```

### Solution 2 

Note that here the numbers can have duplciates!

The brute-force solution here is to exhaust all the possible subsets, and remove all duplicates. The time complexity is combinatorial.

How can we improve this?   In general, we have two options:

Keep the input pattern, which is unsorted, and use an auxiliary data structure to help us.  
Reorder the input pattern, for example sorting the input vector. And build algorithm based above the sorted array. Note that in this condition, our time complexity will be at least the same as the sorting algorithm.  

Here it is obvious that option 2 might be a better idea.  

Imagine that we begin with an empty basket. For each number, we have two options, choose or not choose. Once we made that decision, we move forward for next number.

As you can see, this is a backtracking problem.

A backtracking problem enumerates a set of partial candidates that, in principle, could be completed in various ways to give all the possible solutions to the given problem. The completion is done incrementally, by a sequence of candidate extension steps. Conceptually, the partial candidates are represented as the nodes of a tree structure, the potential search tree.

For example, let the input array to be [1,1,1,2,2,3,3,4].

Now let's begin with an empty basket, the root node is an empty node. How many children this root node should have?

If you are saying "3 nodes begin with 1, 2 nodes begin with 2, 2 nodes begin with 3, 1 node begin with 4", then dude you are in big trouble. Because the second child begin with the second 1 is just a subtree of the first child! You will definitely have duplicates unless you use a HashSet to filter them out before return the results.

Therefore, the children of our root node should be "1 node begin with 1, 1 node begin with 2, 1 node begin with 3, and 1 node begin with 4". For each tree node in this potential search tree, it can't have two children which have the same value! And you will notice that for the iterative part in below solution.

On each node, we try to choose following numbers as its children. However, if one child is identified to have the same value as its previous sibling, ignore this child. This "choose children" is the iterative part. For each child, we add it to the temp result, and keep doing the same thing. This is the recursive part, which is DFS.

Another different perspectie is like this :

```      
subsets([1,2,3,4]) = []
                     // push(1)
                     [1, subsets([2,3,4])] // if push N times in subsets([2,3,4]), 
                                           // the pop times is also N, so vec is also [1] 
                                           // after backtrack.
                     // pop(), push(2)
                     [2, subsets([3,4])]
                     // pop(), push(3)
                     [3, subsets([4])]
                     // pop(), push(4)
                     [4, subsets([])]
                     // pop()
```


                     
```cpp
class Solution2 {
public:
  vector< vector<int> > subsetsWithDup(vector<int>& nums) {
    vector< vector<int> > res;
    std::sort(nums.begin(),nums.end());
    vector<int> temp;
    dfs(res,temp,nums,0);
    return res;
  }
private:
  // Consider start as a tree node, and the number after nums[start]
  // as its children, which means the branches it can enter.
  // Don't you agree that the longest branch will be visted at first?
  void dfs(vector<vector<int>> & res,
           vector<int> & temp,
           const vector<int> & nums,
           int start) {
    res.push_back(temp);
    for (int i=start;i<nums.size();++i) {
      if (i>start && nums[i]==nums[i-1]) continue; //ignore duplicates
      temp.push_back(nums[i]);
      dfs(res,temp,nums,i+1);
      temp.pop_back();
    }
  }
};
```
