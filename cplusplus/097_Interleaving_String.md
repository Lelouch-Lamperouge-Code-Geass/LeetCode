Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example, 

Given:  

s1 = "aabcc",  
s2 = "dbbca",  

When s3 = "aadbbcbcac", return true.  
When s3 = "aadbbbaccc", return false.  

# Solution

DP table represents if s3 is interleaving at (i+j)th position when s1 is at ith position, and s2 is at jth position. 0th position means empty string.

So if both s1 and s2 is currently empty, s3 is empty too, and it is considered interleaving. If only s1 is empty, then if previous s2 position is interleaving and current s2 position char is equal to s3 current position char, it is considered interleaving. similar idea applies to when s2 is empty. when both s1 and s2 is not empty, then if we arrive i, j from i-1, j, then if i-1,j is already interleaving and i and current s3 position equal, it s interleaving. If we arrive i,j from i, j-1, then if i, j-1 is already interleaving and j and current s3 position equal. it is interleaving.


```cpp
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        std::size_t s1_size(s1.size()), s2_size(s2.size()), s3_size(s3.size());
        
        if (s1_size + s2_size != s3_size) return false;
        
        std::vector< std::vector<bool> > can_be_formed(s1_size + 1, std::vector<bool>(s2_size + 1, false));
        can_be_formed[0][0] = true;
        
        // Take none from s2
        for (std::size_t i = 1; i <= s1_size; ++i) {
            can_be_formed[i][0] = (can_be_formed[i - 1][0] && s1[i-1] == s3[i-1]);
        }
        
        // Take none from s1
        for (std::size_t j = 1; j <= s2_size; ++j) {
            can_be_formed[0][j] = (can_be_formed[0][j - 1] && s2[j-1] == s3[j-1]);
        }
        
        for (std::size_t i = 1; i <= s1_size; ++i) { 
            for (std::size_t j = 1; j <= s2_size; ++j) {
                can_be_formed[i][j] = can_be_formed[i-1][j] && s1[i-1] == s3[i + j - 1]
                    || can_be_formed[i][j-1] && s2[j-1] == s3[i + j - 1];
            }
        }
        
        return can_be_formed[s1_size][s2_size];
    }
};
```
