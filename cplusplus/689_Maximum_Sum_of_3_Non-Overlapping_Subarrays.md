In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.

Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.

Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.

##### Example:

```
Input: [1,2,1,2,6,7,5,1], 2
Output: [0, 3, 5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
```

##### Note:

* nums.length will be between 1 and 20000.
* nums[i] will be between 1 and 65535.
* k will be between 1 and floor(nums.length / 3).

# Solution

The question asks for three non-overlapping intervals with maximum sum of all 3 intervals. If the middle interval is [i, i+k-1], where k <= i <= n-2k, the left interval has to be in subrange [0, i-1], and the right interval is from subrange [i+k, n-1].

So the following solution is based on DP.

* posLeft[i] is the starting index for the left interval in range [0, i];
* posRight[i] is the starting index for the right interval in range [i, n-1]; 

Then we test every possible starting index of middle interval, i.e. k <= i <= n-2k, and we can get the corresponding left and right max sum intervals easily from DP. And the run time is O(n).

Caution. In order to get lexicographical smallest order, when there are two intervals with equal max sum, always select the left most one. So in the code, the if condition is ">= tot" for right interval due to backward searching, and "> tot" for left interval.


```cpp
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        std::size_t n = nums.size();
        std::vector<int> range_sum = {0};
        
        for (int num : nums) {
            range_sum.push_back(range_sum.back() + num);
        }
        
        // DP for starting index of the left max sum interval
        std::vector<int> pos_left(n, 0);
        for (int i = k, temp_max = range_sum[k] - range_sum[0]; i < n; i++) {
            if (range_sum[i + 1] - range_sum[i + 1 - k] > temp_max) {
                pos_left[i] = i + 1 - k;
                temp_max = range_sum[i + 1] - range_sum[i + 1 - k];
            } else {
                pos_left[i] = pos_left[i-1];
            }
        }
        
        // DP for starting index of the right max sum interval
        // caution: the condition is ">= tot" for right interval, and "> tot" for left interval
        std::vector<int> pos_right(n, n - k);
        for (int i = n - k - 1, temp_max = range_sum[n] - range_sum[n - k]; i >= 0; --i) {
            if (range_sum[i + k] - range_sum[i] >= temp_max) {
                pos_right[i] = i;
                temp_max = range_sum[i+k] - range_sum[i];
            } else {
                pos_right[i] = pos_right[i + 1];
            }
        }
        
        // test all possible middle interval
        std::vector<int> reval(3, 0);
        int max_sum(0);
        for (int i = k; i <= n - 2 * k; ++i) {
            int l = pos_left[i - 1], r = pos_right[i + k];
            int temp_max = (range_sum[i+k]-range_sum[i]) + (range_sum[l+k]-range_sum[l]) + (range_sum[r+k]-range_sum[r]);
            if (temp_max > max_sum) {
                max_sum = temp_max;
                reval = {l, i, r};
            }
        }
        
        return reval;
    }
};
```
