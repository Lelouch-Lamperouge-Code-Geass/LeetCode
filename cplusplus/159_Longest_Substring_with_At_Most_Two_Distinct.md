Given a string, find the length of the longest substring T that contains at most 2 distinct characters.

For example, Given s = “eceba”,

T is "ece" which its length is 3.

# Solution

This question belong to the same category as those such as "longest substring without repeating characters", "minimum window substring", and "substring with concatenation of all words". __To solve this kind of question we can use two pointers and a hash table.__ When the key of the hash table is char, we can simply use an array as the hash table. __The most important idea in solving this kind of questions is "how to update the "start" pointer" and the solution to these questions seem usually differ only in this respect.__

```cpp
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
          int distinct_count(0);
          std::vector<std::size_t> counter(256, 0);
          std::size_t start(0), max_len(0);
          for (std::size_t i = 0, n = s.size(); i < n; ++i) {
            if (counter[s[i]]++ == 0) {
              ++ distinct_count;
            }

            while (distinct_count > 2) {
              if (--counter[s[start]] == 0) {
                -- distinct_count;
              }
              ++ start;
            }

            max_len = std::max(max_len, i - start + 1);
          }

          return max_len;
    }
};
```
