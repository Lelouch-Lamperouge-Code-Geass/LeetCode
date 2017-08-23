Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:
```
Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
Return 16
The two words can be "abcw", "xtfn".
```

Example 2:
```
Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
Return 4
The two words can be "ab", "cd".
```

Example 3:
```
Given ["a", "aa", "aaa", "aaaa"]
Return 0
No such pair of words.
```

# Solution
using an array of int to pre-store the length of each word reducing the frequently measuring process;
since int has 4 bytes, a 32-bit type, and there are only 26 different letters, so we can just use one bit to indicate the existence of the letter in a word.
space cost O(n).
time cost O(n^2) -> comparing each pair of them from the beginning to the end.

```cpp  
class Solution {
public:
  int maxProduct(vector<string>& words) {
    const std::size_t words_size(words.size());
    std::vector<int> bit_mapper(words_size,0);
    for (std::size_t i=0;i<words_size;++i) {
      for (const char c : words[i]) {
        bit_mapper[i] |=  ( 1 << (c-'a') );
      }
    }

    std::size_t max_product(0);
    for (std::size_t i=0;i<words_size;++i) {
      for (std::size_t j=i+1;j<words_size;++j) {
        if ( (bit_mapper[i] & bit_mapper[j]) == 0) { // has no common char
          max_product = std::max(max_product,words[i].size() * words[j].size());
        }
      }
    }
    return max_product;
  }
};
```
