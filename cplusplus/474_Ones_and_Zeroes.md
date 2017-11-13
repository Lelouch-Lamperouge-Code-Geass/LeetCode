In the computer world, use restricted resource you have to generate maximum benefit is what we always want to pursue.

For now, suppose you are a dominator of m 0s and n 1s respectively. On the other hand, there is an array with strings consisting of only 0s and 1s.

Now your task is to find the maximum number of strings that you can form with given m 0s and n 1s. Each 0 and 1 can be used at most once.

##### Note:

1. The given numbers of 0s and 1s will both not exceed 100
2. The size of given string array won't exceed 600.

##### Example 1:

```
Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
Output: 4
```

Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are “10,”0001”,”1”,”0”

##### Example 2:

```
Input: Array = {"10", "0", "1"}, m = 1, n = 1
Output: 2
Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".
```

# Solution

The reason we have to the update from bottom right to top left is stated in the comments: we need to calculate values for this iteration given values from the last iteration. If we do it the other way around, memo[i][j] is calculated with values from this iteration, which results in overcounting.
memo[i][j] = max(memo[i][j], memo[i - numZeroes][j - numOnes] + 1); This line says:

1. There are two possible ways to form the max number of strings with i 0's and j 1's regarding s: we either form s or skip it.
2. If we skip s, memo[i][j] shouldn't change.
3. Otherwise, we form s with numZeroes 0's and numOnes 1's, which leaves us i - numZeroes 0's and j - numOnes 1's to work with for all previous strings. How many strings can we form with i - numZeroes 0's and j - numOnes 1's? It's memo[i - numZeroes][j - numOnes] which was calculated in previous rounds, so just add 1 to that.
4. We choose to form s or skip it based on which of 2 and 3 gives us a larger memo[i][j]

```cpp
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        const std::size_t strs_size (strs.size());
        
        // max_number[i][j] = the max number of strings that can be formed with i 0's and j 1's
        // from the first few strings up to the current string s
        vector<vector<int>> max_number(m + 1, vector<int>(n + 1, 0));
        
        for (const string &str : strs) {
            int cur_zero(0), cur_one(0);
            for (char c : str) {
                if (c == '0') ++ cur_zero;
                if (c == '1') ++ cur_one;
            }
            
            
            // Catch: have to go from bottom right to top left
            // Why? If a cell in the max_number is updated(because s is selected),
            // we should be adding 1 to max_number[i][j] from the previous iteration 
            // (when we were not considering s)
            // If we go from top left to bottom right, we would be using results 
            // from this iteration => overcounting
            for (int i = m; i >= cur_zero; --i) {
                for (int  j =n; j >= cur_one; --j) {
                    max_number[i][j] = std::max(max_number[i][j], max_number[i - cur_zero][j - cur_one] + 1);
                }
            }
        }
        
        return max_number[m][n];
    }
};
```
