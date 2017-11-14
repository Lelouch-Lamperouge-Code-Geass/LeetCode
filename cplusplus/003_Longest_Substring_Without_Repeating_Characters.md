Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. 

__Note that the answer must be a substring, "pwke" is a subsequence and not a substring.__

# Solution

The basic idea is, keep a hashmap which stores the characters in string as keys and their positions as values, and keep two pointers which define the max substring. move the right pointer to scan through the string , and meanwhile update the hashmap. If the character is already in the hashmap, then move the left pointer to the right of the same character last found. Note that the two pointers can only move forward. 

In our solution, the left pointer is ```start```, right pointer is ```i```. On every ```i```, [start, i] should form the longest substring wihout repeating characters including ```s[i]```.

__The time complexity is O(N)， and the spce complexity is O(1).__ (We use a vector with 256 entries.)

Keynotes:

1. We calculate the length of longest non-duplicate-char string including current char on each char, and compare it with final result.
2. ```start = std::max(start, char_positions[s[i]] + 1)``` is important, because it is highly possible that char_positions[s[i]] + 1 is smaller than start, and that is often ignored by people.

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        std::vector<std::size_t> char_positions(256, -1);
        
        std::size_t start(0), len(0);
        for (std::size_t i = 0, n = s.size(); i < n; ++i) {
            start = std::max(start, char_positions[s[i]] + 1);
            std::size_t cur_len = i - start + 1;
            len = std::max(len, cur_len);
            char_positions[s[i]] = i;
        }
        
        return len;
    }
};
```



