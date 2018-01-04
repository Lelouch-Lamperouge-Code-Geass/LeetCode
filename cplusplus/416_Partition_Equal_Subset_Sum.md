Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

##### Note:

1. Each of the array element will not exceed 100.
2. The array size will not exceed 200.

##### Example 1:

```
Input: [1, 5, 11, 5]

Output: true

Explanation: The array can be partitioned as [1, 5, 5] and [11].
```

##### Example 2:

```
Input: [1, 2, 3, 5]

Output: false

Explanation: The array cannot be partitioned into equal sum subsets.
```

# Solution

This problem is essentially let us to find whether there are several numbers in a set which are able to sum to a specific value (in this problem, the value is sum/2).

For subarray [0, i], whether we can get sum ```k``` is depended on :

1. If we choose to add num[i], whether we can get sum ```k - nums[i]``` out of subarray [0, i - 1]
2. If we choose not to add nums[i], whether we can get sum ```k``` out of subarray[0, i - 1]

Actually, this is a 0/1 knapsack problem, for each number, we can pick it or not. Let us assume dp[i][k] means whether the specific sum k can be gotten from the first i numbers. If we can pick such a series of numbers from 0-i whose sum is k, dp[i][k] is true, otherwise it is false.

Base case: dp[0][0] is true; (zero number consists of sum 0 is true)

Transition function: For each number, if we don't pick it, dp[i][k] = dp[i-1][k], which means if the first i-1 elements has made it to k, dp[i][k] would also make it to k (we can just ignore nums[i]). If we pick nums[i]. dp[i][k] = dp[i-1][k-nums[i]], which represents that k is composed of the current value nums[i] and the remaining composed of other previous numbers. Thus, the transition function is dp[i][k] = dp[i-1][k] || dp[i-1][k-nums[i]].

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        std::size_t sum(0); // We know they are only positive integers
        for (int num : nums) {
            sum += num;
        }
        
        if ( (sum & 1) != 0 ) return false; // sum must be even
        
        sum /= 2;
        const std::size_t n(nums.size());
        
        // can_partition[i][k] means whether the specific sum k can be gotten from the first i numbers
        std::vector<std::vector<bool>> can_partition(n + 1, std::vector<bool>(sum + 1, false));
        
        // When sum == 0 , it's always true
        for (std::size_t i = 0; i <= n; ++i) {
            can_partition[i][0] = true;
        }
        
        
        for (std::size_t i = 1; i <= n; ++i) { // amount of first numbers in nums 
            for (std::size_t k = 1; k <= sum; ++k) { // value from 0 to sum
                can_partition[i][k] = // Not choose current number
                                      can_partition[i-1][k] 
                                      // Choose current number
                                      || k >= nums[i-1] && can_partition[i - 1][k - nums[i - 1]];
            }
        }
        
        return can_partition[n][sum];
    }
};
```

# Knowledge

The knapsack problem or rucksack problem is a problem in combinatorial optimization: Given a set of items, each with a weight and a value, determine the number of each item to include in a collection so that the total weight is less than or equal to a given limit and the total value is as large as possible. It derives its name from the problem faced by someone who is constrained by a fixed-size knapsack and must fill it with the most valuable items.

