Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. 

__Note that the answer must be a substring, "pwke" is a subsequence and not a substring.__

# Solution

Assume L[i] = s[m...i], denotes the longest substring without repeating characters that ends up at s[i], and we keep a hashmap for every characters between m ... i, while storing <character, index> in the hashmap.

We know that each character will appear only once.
Then to find s[i+1]:
1. if s[i+1] does not appear in hashmap
    we can just add s[i+1] to hash map. and L[i+1] = s[m...i+1]
2. if s[i+1] exists in hashmap, and the hashmap value (the index) is k,
   let m = max(m, k), then L[i+1] = s[m...i+1], we also need to update entry in hashmap to mark the latest occurency of s[i+1].

Since we scan the string for only once, and the 'm' will also move from beginning to end for at most once. Overall complexity is O(n).

If characters are all in ASCII, we could use array to mimic hashmap.

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



