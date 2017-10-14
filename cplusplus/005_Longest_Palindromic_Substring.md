Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.


##### Example
  
```
Input: "babad"

Output: "bab"

Note: "aba" is also a valid answer.
```

##### Example:

```
Input: "cbbd"

Output: "bb"
```

# Solution

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        std::size_t start(0), max_len(0), n(s.size());
        
        for (std::size_t i = 0; i < n; ) {
            std::size_t left(i), right(i);
            // Expand to right as long as the char is the same
            while(right + 1 < n && s[right+1]==s[i]) ++ right;
            
            i = right + 1; // ignore the consecutive same character
            
            while (left - 1 < n && right+1 < n && s[left-1]==s[right+1]) {
                -- left;
                ++ right;
            }
            
            std::size_t cur_len = right + 1 - left;
            if (cur_len > max_len) {
                start = left;
                max_len = cur_len;
            }            
        }
        return s.substr(start, max_len);
    }

};
```
