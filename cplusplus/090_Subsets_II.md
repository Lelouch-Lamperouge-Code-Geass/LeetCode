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
  For example, if we have duplicate elements (5, 5), instead of treating them as two elements that are duplicate, 
  we can treat it as one special element 5, but this element has more than two choices: 
  you can either NOT put it into the subset, or put ONE 5 into the subset, or put TWO 5s into the subset. 

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
