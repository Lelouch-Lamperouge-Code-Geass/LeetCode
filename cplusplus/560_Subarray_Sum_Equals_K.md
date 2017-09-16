Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

Example 1:

```
Input:nums = [1,1,1], k = 2
Output: 2
```

Note:
1. The length of the array is in range [1, 20,000].
2. The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].


# Solution

### Naive solution

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        const std::size_t n = nums.size();
        vector<int> range_sum(n+1, 0);
        
        for (std::size_t i = 1; i <= n; ++i) {
            range_sum[i] = range_sum[i - 1] + nums[i - 1];
        }
        
        int reval(0);
        for (std::size_t from = 0; from <= n; ++ from) {
            for (std::size_t to = from + 1; to <= n; ++ to) {
                if (range_sum[to] - range_sum[from] == k) {
                    ++ reval;
                }
            }
        }
        
        return reval;
    }
};
```

### Solution with presum and hashmap

From solution 1, we know the key to solve this problem is SUM[i, j]. So if we know SUM[0, i - 1] and SUM[0, j], then we can easily get SUM[i, j]. To achieve this, we just need to go through the array, calculate the current sum and save number of all seen PreSum to a HashMap. __Time complexity O(n), Space complexity O(n).__

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        const std::size_t n = nums.size();
        
        int reval(0), range_sum(0);
        
        // to take into account those subarrays that begin with index 0
        unordered_map<int, int> sum_counter = {{0,1}}; 
        
        for (int num : nums) {
            range_sum += num;
            if (sum_counter.count(range_sum - k) > 0) {
                reval += sum_counter[range_sum - k];
            }
            
            ++ sum_counter[range_sum];
        }
        
        return reval;
    }
};
```
