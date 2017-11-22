Given a string S and a string T, count the number of distinct subsequences of S which equals T.  

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).  

Here is an example:  
S = "rabbbit", T = "rabbit"  

Return 3.  

# Solution

This problem is asking "count the number of distinct subsequences", which is a sign that we _may_ solve it by using dynamic programming. 

Dynamic programming can generally be used for :

1. Finding optimal solutions to some problems.  
2. Counting the number of solutions.

It does this by breaking it down into a collection of simpler subproblems, solving each of those subproblems just once, and storing their solutions. The key is to find out the relationship between subproblems and current problem.

Now let's find out the relationship between a subproblem and current problem here.

If we defines F[i][j] as the number of distinct t.substr(0, i) in s.substr(0, j). Then its value comes from :

1. F[i][j - 1] : means the number of distinct t.substr(0, i) for s.substr(0, j - 1), here we ignores s[j].
2. If s[j-1] == t[i - 1], then add F[i - 1][j - 1] : means the number of distinct t.substr(0, i - 1) for s.substr(0, j - 1), here we choose s[j].

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        const std::size_t t_size(t.size()), s_size(s.size());
        std::vector< std::vector<std::size_t> > subsequence_count(t_size + 1, 
                                                std::vector<std::size_t>(s_size + 1, 0));
        
        // Process the first row, should be all '1'
        for (std::size_t j = 0; j <= s_size; ++j) subsequence_count[0][j] = 1;
        
        for (std::size_t i = 1; i <= t_size; ++i) {
            for (std::size_t j = 1; j <= s_size; ++j) {
                subsequence_count[i][j] += subsequence_count[i][j - 1];
                if (s[j - 1] == t[i - 1]) {
                    subsequence_count[i][j] += subsequence_count[i - 1][j - 1];
                }
            }
        }
        
        return subsequence_count[t_size][s_size];
    }
};
```
