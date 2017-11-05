Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

##### Example 1:

```
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
```

##### Example 2:

```
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
```

Note: The length of the given binary array will not exceed 50,000.

# Solution

The idea is to change 0 in the original array to -1. Thus, if we find SUM[i, j] == 0 then we know there are even number of -1 and 1 between index i and j. Also put the sum to index mapping to a HashMap to make search faster.

```cpp
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        for (int & num : nums) {
            if (num == 0) num = -1;
        }
        
        std::unordered_map<long long, int> mapper;
        mapper.insert(std::make_pair(0, -1));
        long long sum_so_far(0);
        std::size_t reval(0);
        for (std::size_t i = 0, n = nums.size(); i < n; ++i) {
            sum_so_far += nums[i];
            if (mapper.count(sum_so_far)) {
                reval = std::max(reval, i - mapper[sum_so_far]);
            } else {
                mapper.insert(std::make_pair(sum_so_far, i));
            }
        }
        
        return reval;
    }
};
```
