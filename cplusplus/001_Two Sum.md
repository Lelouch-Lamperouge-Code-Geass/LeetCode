Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

```
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
```

# Solution

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        unordered_map<int,std::size_t> visited;
        std::size_t nums_size(nums.size());
        for (std::size_t i = 0;i < nums_size;++i) {
            if (visited.count(target-nums[i])>0) {
                res.push_back(visited[target-nums[i]]);
                res.push_back(i);
            }
            visited[nums[i]] = i;
        }
        return res;
    }
};
```
