Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

##### Example 1:

```
Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
```

##### Example 2:

```
Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
```

# Solution

```cpp
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        std::vector<int> reval;
        std::vector<int> counter(256, 0);
        int not_found(p.size()), p_size(p.size());
        
        for (char c : p) {
            ++ counter[c];
        }
        
        for (std::size_t i = 0, n = s.size(); i < n; ++i) {
            -- counter[s[i]]; // Char goes into window
            
            if (counter[s[i]] >= 0) { // Find a char in p
                -- not_found;
            }
            
            // Only when i >= p_size, we begin to pop char out of window
            if (i >= p_size) {
                ++ counter[s[i - p_size]];
                if (counter[s[i - p_size]] > 0) {
                    // For char not in p, it's count will never be more than 0
                    ++ not_found;
                }
            }
            
            if (not_found == 0) { // Find all chars in p
                reval.emplace_back(i + 1 - p_size);
            }
        }
        
        return reval;
    }
};
```

