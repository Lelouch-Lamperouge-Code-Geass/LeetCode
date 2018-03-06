Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000.

##### Example 1:

```
Input: "bbbab"
Output: 4
One possible longest palindromic subsequence is "bbbb".
```

##### Example 2:

```
Input: "cbbd"
Output: 2
One possible longest palindromic subsequence is "bb".
```

# Solution

__Be careful about subsequence vs substring! This is the first thing you need to get clarification from interviwer.__

Here is a problem looking for [longest palindromic substring](https://leetcode.com/problems/longest-palindromic-substring/description/). Please ponder the difference between these two problems. 

### Solution 1

Let's define max_len[left][right] means the longest palindromic subsequence's length of substring [left, right].

Then max_len[left][right] is the maximum value of :

1. If s[left] == s[right] : s[left + 1][right - 1] + 2, s[right] and s[left] are both part of current longest palindromic subsenquence.
2. max_len[left][right - 1] : s[right] is not useful, it is not part of current longest palindromic subsenquence.
3. max_len[left + 1][right] : s[right] is useful, but since s[left] != s[right] here, we can just ignore s[left].


```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        if (s.empty()) return 0;
        
        const std::size_t n = s.size();
        std::vector<std::vector<int>> max_len(n, std::vector<int>(n, 0)); 
        
        for (int right = 0; right < n; ++right) {
            for (int left = right; left >= 0; --left) {
                if (left == right) {
                    max_len[left][right] = 1;
                } else {
                    if (s[left] == s[right]) {
                        // We don't need to compare it to below two max_len values.
                        // We definitely can get the max length by evolving from max_len[left + 1][right - 1].
                        max_len[left][right] = max_len[left + 1][right - 1] + 2;
                    } else {            
                        max_len[left][right] = std::max(max_len[left][right - 1],
                                                        max_len[left + 1][right]);
                    }
                }
            }
        }
        
        return max_len[0][n - 1];
    }
};
```

### Solution 2


You will be considering substrings starting at left and ending at right (inclusive). To do this you will iterate over all lengths from 1 to n and within each length iterate over staring (or left) position. The key is that you get the answers for a single length at all start positions before going to the next length because the dp depends on the answers from shorter lengths. If you do it this way you will have 3 cases to consider on every iteration, pick the one with the highest value.

1. the answer from removing the left edge char  
2. the answer from removing the right edge char  
3. and if the left and right chars are equal, 2 plus the answer from removing both left and right  

the 3rd case is how the answer grows. After iterating through all you will have performed O(n^2) checks and used O(n^2) memory, the answer is where left is 0 and right is n-1 which will be your very last calculation.

```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        if (s.empty()) return 0;
        
        const std::size_t n = s.size();
        
        std::vector<std::vector<int>> max_len(n, std::vector<int>(n, 0)); 
        
        for (int len = 1; len <= n; ++ len) {
            for (int left = 0, right = len - 1; right < n; ++ left, ++ right) {
                if (right == left) {
                    max_len[left][right] = 1;
                } else {
                    // Better of without left or without right edge char
                    int cur_max = std::max(max_len[left][right - 1], max_len[left + 1][right]);
                    if (s[left] == s[right])
                    {
                        // Now check 2 plus without left and without right.
                        // Actually this is definitely the max of these three candidates.
                        cur_max = std::max(cur_max, 2 + max_len[left + 1][right - 1]);
                    }

                    max_len[left][right] = cur_max;
                }
            }
        }
        
        return max_len[0][n - 1];
    }
};
```
