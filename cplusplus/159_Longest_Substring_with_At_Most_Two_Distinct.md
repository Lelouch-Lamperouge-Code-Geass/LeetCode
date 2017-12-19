Given a string, find the length of the longest substring T that contains at most 2 distinct characters.

For example, Given s = “eceba”,

T is "ece" which its length is 3.

# Solution

This is a typical "sliding window" problem. This problem can be translated into "If we know the longest substring T that contains at most 2 distinct characters ending with each character, can we get the final result?". Obviously we can. Right now the problem becomes how to find the "at most 2 distinct characters longest substring".

This question belong to the same category as those such as "longest substring without repeating characters", "minimum window substring", and "substring with concatenation of all words". __To solve this kind of question we can use two pointers and a hash table.__ When the key of the hash table is char, we can simply use an array as the hash table. __The most important idea in solving this kind of questions is "how to update the "start" pointer" and the solution to these questions seem usually differ only in this respect.__

```cpp
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int start(0), max_len(0), unique_chars(0);
        std::vector<int> chars_in_window(256, 0);
        for (int i = 0, n = s.size(); i < n; ++i) {
            if (chars_in_window[s[i]] == 0) {
                ++ unique_chars; // A new char
            }
            
            ++ chars_in_window[s[i]];
            
            // Keep shifting start until at most 2 distinct characters
            // are within this window.
            while (unique_chars > 2) {
                if (--chars_in_window[s[start]] == 0) --unique_chars;
                ++ start;
            }
            // Right now the window is the longest substring T 
            // that contains at most 2 distinct characters.
            max_len = std::max(max_len, i + 1 - start);
        }
        
        return max_len;
    }
};
```
