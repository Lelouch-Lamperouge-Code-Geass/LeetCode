You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.

Find out how many ways to assign symbols to make sum of integers equal to target S.

Example 1:

```
Input: nums is [1, 1, 1, 1, 1], S is 3. 
Output: 5
Explanation: 

-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3
```

There are 5 ways to assign symbols to make the sum of nums be target 3.

##### Note:

1. The length of the given array is positive and will not exceed 20.
2. The sum of elements in the given array will not exceed 1000.
3. Your output answer is guaranteed to be fitted in a 32-bit integer.

# Solution

### Backtracking, very slow

__Time complexity : exponential.__

```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int reval(0);
        checkWithBacktracking(nums, 0, S, 0, reval);
        return reval;
    }
private:
    void checkWithBacktracking(const std::vector<int> &nums, 
                               std::size_t pos, 
                               const int S,
                               const int sum_so_far,
                              int &reval) {
        if (pos == nums.size()) {
            if (sum_so_far == S) {
                ++ reval;
            }
        } else {
            checkWithBacktracking(nums, pos + 1, S, sum_so_far + nums[pos], reval);
            checkWithBacktracking(nums, pos + 1, S, sum_so_far - nums[pos], reval);
        }
    }
};
```

### Dynamic programming 

The recursive solution is very slow, because its runtime is exponential.

The original problem statement is equivalent to:

Find a subset of nums that need to be positive, and the rest of them negative, such that the sum is equal to target.

Let P be the positive subset and N be the negative subset.

For example:

```
Given nums = [1, 2, 3, 4, 5] and target = 3 then one possible solution is +1-2+3-4+5 = 3
Here positive subset is P = [1, 3, 5] and negative subset is N = [2, 4]
```

Then let's see how this can be converted to a subset sum problem:

```
                  sum(P) - sum(N) = target
sum(P) + sum(N) + sum(P) - sum(N) = target + sum(P) + sum(N)
                       2 * sum(P) = target + sum(nums)
```

So the original problem has been converted to a subset sum problem as follows:

Find a subset P of nums such that sum(P) = (target + sum(nums)) / 2

__Note that the above formula has proved that target + sum(nums) must be even.__

We can use that fact to quickly identify inputs that do not have a solution.

For detailed explanation on how to solve subset sum problem, you may refer to [Partition Equal Subset Sum](https://github.com/YangLiuNYU/LeetCode/blob/master/cplusplus/416_Partition_Equal_Subset_Sum.md).


```cpp
class Solution {
private:
    // Return number of ways to reach target_sum by choosing any number of 
    // numbers in nums.
    int waysOfReachSum(const vector<int> &nums,
                      int target_sum) {
        const int n = nums.size();
        
        // Note that we know nums only have non-negative numbers.
        // Here the target_sum is non-negative too.
        vector< vector<int> > ways_of_sum(n + 1, vector<int>(target_sum + 1, 0));
        
        ways_of_sum[0][0] = 1;
        
        for (int i = 1; i <= n; ++i) {
            int cur_num = nums[i - 1];
            for (int val = 0; val <= target_sum; ++val) {
                ways_of_sum[i][val] = ways_of_sum[i - 1][val]; // not choose cur_num
                if (val >= cur_num) ways_of_sum[i][val] += ways_of_sum[i - 1][val - cur_num]; // choose cur_num
            }
        }
        
        return ways_of_sum[n][target_sum];
    }
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int array_sum = std::accumulate(nums.begin(), nums.end(), 0);
        
        // S can't be bigger tha  array_sum.
        if (S > array_sum) return 0;
        
        // The sum of array sum and S must be an even number.
        
        if ((array_sum + S) % 2 == 1) return 0;
        
        return waysOfReachSum(nums, (array_sum + S) >> 1);
    }
};
```

We can optimize the space complexity to be one-dimension instead of two-dimension.


```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int s) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        return sum < s || (s + sum) & 1 ? 0 : subsetSum(nums, (s + sum) >> 1); 
    }   

    int subsetSum(vector<int>& nums, int s) {
        int dp[s + 1] = { 0 };
        dp[0] = 1;
        for (int n : nums)
            for (int i = s; i >= n; i--)
                dp[i] += dp[i - n];
        return dp[s];
    }
};
```

### Top-down dynamic programming

```cpp
class Solution {
private:
    int numOfSubset(const vector<int>& nums, 
                    const int sum,
                    const int i, 
                    unordered_map<string, int> &memoization) {
        string hash_code = to_string(i) + "->" + to_string(sum);
        if (memoization.count(hash_code)) {
            return memoization[hash_code];
        } else {
            int reval = 0;
            if (i >= 0) {
                reval += numOfSubset(nums, sum, i - 1, memoization);
                if (sum >= nums[i]) reval += numOfSubset(nums, sum - nums[i], i - 1, memoization);
            } else { // i <= 0
                if (sum == 0) ++ reval;
            }
            memoization[hash_code] = reval;
            return reval;
        }
    }
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int sum_of_nums = std::accumulate(nums.begin(), nums.end(), 0);
        int total_sum = sum_of_nums + S;
        
        if (total_sum % 2 == 1) return 0;
        
         unordered_map<string, int> memoization;
        return numOfSubset(nums, total_sum / 2, nums.size() - 1, memoization);
    }
};
```
