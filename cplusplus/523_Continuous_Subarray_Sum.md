Given a list of __non-negative__ numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to the multiple of k, that is, sums up to n\*k where n is also an integer.

##### Example 1:

```
Input: [23, 2, 4, 6, 7],  k=6
Output: True
Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
```

##### Example 2:

```
Input: [23, 2, 6, 4, 7],  k=6
Output: True
Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
```

##### Note:

1. The length of the array won't exceed 10,000.
2. You may assume the sum of all the numbers is in the range of a signed 32-bit integer.

# Solution

First of all, let's think a similar problem, "check if the array has a continuous subarray that sums up to S" ? In this case, we will use a range-sum array, and whenever we need a number, check have we met "S - cur_number" or not.

Now for this problem, the anything changed is that right now S must be a multiple of K. That's all.

This solution is based on below formula:

```
(sum2 - sum1) % k = (sum2 % k) - (sum1 % k) if sum2 > sum1
```

There are a couple of things that worth mention:

1. We need to add a dummy item in the HashMap
2. For each modk value, we need to store the index as leftmost as possible
3. k could be 0 or negative


Some test cases:

```
[1,5], -6 -> true;
[0], 0 -> false;
[5, 2, 4], 5 -> false;
[0, 0], 100 -> true;
[0,0], 0  -> true;
[0], 0 -> false;
[23,2,6,4,7] , 0 -> false
```

```cpp
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        const std::size_t n(nums.size());
        
        // Stores  <range sum from beginning, index> 
        unordered_map<long long, int> modk_mapper;
        
        // We add a dummy item at the first of the "virtual range sum vector".
        // The dummy item's value is 0 and locates at index -1.
        modk_mapper.insert(std::make_pair(0, -1));
        
        long long range_sum(0);
        
        for (std::size_t i = 0; i < n; ++i) {
            range_sum += nums[i];
            long long modk = (k == 0 ? range_sum : range_sum % k);
            if (modk_mapper.count(modk)) {
                if (i - modk_mapper[modk] > 1) return true;
            } else {
                modk_mapper[modk] = i;
            }
        }
        
        return false;
    }
};
```

A different style.

```cpp
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        const int n = nums.size();
        vector<int> range_sum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            range_sum[i + 1] = range_sum[i] + nums[i];
        }
        
        unordered_map<int, int> found;
        for (int i = 0; i <= n; ++i) {
            int mod_k = k == 0 ? range_sum[i] : range_sum[i] % k;
            if (!found.count(mod_k)) {
                found[mod_k] = i;
            } else {
                if (i - found[mod_k] >= 2) return true;
            }
        }
        return false;
    }
};
```

# Knowledge

### 负数究竟是如何取模的？

https://www.zhihu.com/question/31344913
