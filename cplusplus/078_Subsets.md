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

### Solution 1

We are required to find all the solutions for a problem  with some requirement(here it is required to have no duplicates). This gives us hint that we can solve it with backtracking.

Let's draw a potential search tree like this : we begin with a root node which represents an empty set, and for this node we can have each number as its children. Let's take [1,2,3] as an example, which means that our root node will have 3 children in this case, [1], [2], [3]. And for node [1], [2], [3], can each of them has 3 children as well? Obviously it should not, otherwise, we will have [1,2], [2,1] which are considered as duplicates. Therefore, for each node, we give a limitation which means that it should only have children which are adding a bigger number. This means that node [1] will have one child [1,2], and another child [1,3].

We add the ```temp``` to final result when we reach a node.

```cpp
class Solution {
private:
    void searchWithBacktracking(vector<vector<int>> &result,
                                vector<int> &temp,
                                const vector<int> &nums,
                               int pos) {
        result.emplace_back(temp);
        for (int i = pos; i < nums.size(); ++i) {
            temp.emplace_back(nums[i]);
            searchWithBacktracking(result, temp, nums, i + 1);
            temp.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> temp;
        searchWithBacktracking(result, temp, nums, 0);
        return result;
    }
};
```

### Solution 2

This is still a backtracking solution, but from a different perspective. I perfonally think solution 1 is better, because its potential search tree has much smaller height than this solution.

We can form a potential serach tree.

On each level/index we decide to choose that number or not. 

If we choose that number, we go to left child; otherwise, we go to right child.

When we reach the final level (size of nums), we complete our choosing process and it is time to add the item to final result.
  
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

The methology is simple. Whenever we meet a number, we keep previous results,  also clone previous results and add current number into the clones.

```
[] = > [], [1] => [], [1], [2], [1,2] => [], [1], [2], [1,2], [3], [1,3], [2,3], [1,2,3]
```

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

# Knowledge

### Backtracking

Backtracking is a general algorithm for finding all (or some) solutions to some computational problems, notably constraint satisfaction problems, that incrementally builds candidates to the solutions, and abandons each partial candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.
  
Backtracking can be applied only for problems which admit the concept of a "partial candidate solution" and a relatively quick test of whether it can possibly be completed to a valid solution. It is useless, for example, for locating a given value in an unordered table. When it is applicable, however, backtracking is often much faster than brute force enumeration of all complete candidates, since it can eliminate a large number of candidates with a single test.

Backtracking depends on user-given "black box procedures" that define the problem to be solved, the nature of the partial candidates, and how they are extended into complete candidates. It is therefore a metaheuristic rather than a specific algorithm – although, unlike many other meta-heuristics, it is guaranteed to find all solutions to a finite problem in a bounded amount of time.
