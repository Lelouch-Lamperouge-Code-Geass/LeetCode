Given a set of distinct integers, nums, return all possible subsets.  

Note: The solution set must not contain duplicate subsets.  

For example,  
If nums = [1,2,3], a solution is:  

```
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
```
# Solution

### Solution 1, Backtracking

Backtracking is a general algorithm for finding all (or some) solutions to some computational problems, notably constraint satisfaction problems, that incrementally builds candidates to the solutions, and abandons each partial candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.
  
Backtracking can be applied only for problems which admit the concept of a "partial candidate solution" and a relatively quick test of whether it can possibly be completed to a valid solution. It is useless, for example, for locating a given value in an unordered table. When it is applicable, however, backtracking is often much faster than brute force enumeration of all complete candidates, since it can eliminate a large number of candidates with a single test.

Backtracking depends on user-given "black box procedures" that define the problem to be solved, the nature of the partial candidates, and how they are extended into complete candidates. It is therefore a metaheuristic rather than a specific algorithm – although, unlike many other meta-heuristics, it is guaranteed to find all solutions to a finite problem in a bounded amount of time.
  
  
```cpp
class Solution {
public:
  vector<vector<int>> subsets(vector<int>& nums) {
    vector< vector<int> > reval;
    vector<int> temp;
    Backtracking(reval,temp,nums,0);
    return reval;
  }
private:
  // Formed a potential search tree.
  // Each level/index decide whether choose that number or not.
  // Let's say go to left child means choose while go to right child means not choose that number.
  // the whole process is depth first.
  void Backtracking(vector< vector<int> > & reval,
              vector<int> & temp,
              vector<int> & nums,
              int index) {
    if (index ==  nums.size() ) {
      reval.push_back(temp);
    } else {
      // choose current number, go to left child
      temp.push_back(nums[index]);
      Backtracking(reval,temp,nums,index+1);
      temp.pop_back(); // revert back

      // not choose current number, go to right child
      Backtracking(reval,temp,nums,index+1);
    }
  }
};
```

### Solution, iterative solution.

```cpp
class Solution {
public:
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res(1,vector<int>());
    for (int num : nums) {
      const std::size_t pre_size(res.size());
      for (std::size_t i=0;i<pre_size;++i) {
        res.push_back(res[i]);
        res.back().push_back(num);
      }
    }
    return res;
  }
};
```
