Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:

```
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
```

Example 2:

```
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]
```


# Solution

1. The <= in (std::size_t j = 0; j <= cur_word.size(); ++j) is aimed to handle empty string in the input.
    Consider the test case of ["a", ""];

2. Since we now use <= in (std::size_t j = 0; j <= cur_word.size(); ++j) instead of <.
    There may be duplicates in the output (consider test case ["abcd", "dcba"]).
    Therefore I put a str2.length()!=0 to avoid duplicates.

__Time complexity  complexity O(LengthOfList * LengthOfWord ^ 2)__

```cpp
class Solution {
private:
  bool isPalindrome(const std::string & word) {
    if (!word.empty()) {
      std::size_t begin(0), end(word.size() - 1);
      while (begin < end) {
        if (word[begin++] != word[end--]) {
          return false;
        }
      }
    }
    return true;
  }


public:
  vector<vector<int>> palindromePairs(vector<string>& words) {
    vector<vector<int>> reval;
    std::unordered_map<std::string, int> word_mapper;
    for (std::size_t i = 0, n = words.size(); i < n; ++i) {
      word_mapper[words[i]] = i;
    }

    for (std::size_t i = 0, n = words.size(); i < n; ++i) {
      const std::string &cur_word = words[i];
      // The <= here is aimed to handle empty string in the input.
      // Consider the test case of ["a", ""];
      for (std::size_t j = 0; j <= cur_word.size(); ++j) {
        std::string left(cur_word.substr(0,j)), right(cur_word.substr(j));
        if (isPalindrome(left)) {
          std::string rev_right(right.rbegin(), right.rend());
          if (word_mapper.count(rev_right) != 0 && word_mapper[rev_right] != i) {
            reval.push_back({word_mapper[rev_right], i});
          }
        }

        if (isPalindrome(right)) {
          std::string rev_left(left.rbegin(), left.rend());
          // check "!right.empty()" to avoid duplicates
          if (word_mapper.count(rev_left) != 0
              && word_mapper[rev_left] != i
              && !right.empty()) {
            reval.push_back({i, word_mapper[rev_left]});
          }
        }
      }
    }

    return reval;
  }
};
```
