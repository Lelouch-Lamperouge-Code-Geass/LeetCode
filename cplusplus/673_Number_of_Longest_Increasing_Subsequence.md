Given an unsorted array of integers, find the number of longest increasing subsequence.

##### Example 1:

```
Input: [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].
```

##### Example 2:

```
Input: [2,2,2,2,2]
Output: 5
Explanation: The length of longest continuous increasing subsequence is 1, 
and there are 5 subsequences' length is 1, so output 5.
```

Note: Length of the given array will be not exceed 2000 and the answer is guaranteed to be fit in 32-bit signed int.


# Solution

If we know the length of longest increasing subsenquence end with index i, and the count of same length LIS end with index i. Then we know the max LIS length  of the whole array. And the we can add all the LIS with the same length together.

The solution is based on DP.

The most important thing here is define a sub-problem as "the max-length ending with nums[i], and the count of that length ending with nums[i]". Notice "ending with nums[i]" is the key. 

```
For a sequence of numbers,
cnt[k] is total number of longest subsequence ending with nums[k];
len[k] is the length of longest subsequence ending with nums[k];
```

Then we have following equations

```
len[k+1] = max(len[k+1], len[i]+1) for all i <= k and nums[i] < nums[k+1];
cnt[k+1] = sum(cnt[i]) for all i <= k and nums[i] < nums[k+1] and len[i] = len[k+1]-1;
```

Starting case and default case: cnt[0] = len[0] = 1;

__Time complexity is O(N ^ 2), space complexity is O(N).__

```cpp
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        const std::size_t n = nums.size();
        std::size_t max_len(1);
        // the length of longest subsequence ending with nums[i]
        std::vector<std::size_t> max_len_end_with(n, 1); 
        // total number of longest subsequence ending with nums[i]
        std::vector<std::size_t> max_len_count_end_with(n, 1);
        for (std::size_t i = 1; i < n; ++i) {
            for (std::size_t j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    if (max_len_end_with[j] + 1 > max_len_end_with[i]) {
                        max_len_end_with[i] = max_len_end_with[j] + 1;
                        max_len_count_end_with[i] = max_len_count_end_with[j];
                    } else if (max_len_end_with[j] + 1 == max_len_end_with[i]) {
                        max_len_count_end_with[i]  += max_len_count_end_with[j];
                    } else { 
                        // max_len_end_with[j] + 1 < max_len_end_with[i], ignore
                    }
                }
            }
            
            max_len = std::max(max_len, max_len_end_with[i]);
        }
        
        int reval(0);
        for (std::size_t i = 0; i < n; ++i) {
            if (max_len_end_with[i] == max_len) {
                reval += max_len_count_end_with[i];
            }
        }
        return reval;
    }
};
```
