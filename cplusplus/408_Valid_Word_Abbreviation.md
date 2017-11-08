Given a non-empty string s and an abbreviation abbr, return whether the string matches with the given abbreviation.

A string such as "word" contains only the following valid abbreviations:

```
["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", 
 "w1r1", "1o2", "2r1", "3d", "w3", "4"]
```

Notice that only the above abbreviations are valid abbreviations of the string "word". Any other string is not a valid abbreviation of "word".

##### Note:
  
Assume s contains only lowercase letters and abbr contains only lowercase letters and digits.

##### Example 1:
  
```
Given s = "internationalization", abbr = "i12iz4n":

Return true.
```

##### Example 2:

```
Given s = "apple", abbr = "a2e":

Return false.
```

# Solution

### Solution one

```cpp
class Solution {
private:
    std::size_t getSkipNumber(const std::string &abbr, std::size_t pos) {
        const std::size_t n = abbr.size();
        std::size_t reval(0);
        while (pos < n && std::isdigit(abbr[pos])) {
            reval = reval * 10 + (abbr[pos] - '0');
            ++ pos;
        }
        
        return reval;
    }
public:
    bool validWordAbbreviation(string word, string abbr) {
        std::size_t pos(0), n(word.size());
        std::size_t i(0), m(abbr.size());
        
        while (pos < n && i < m) {
            std::size_t skip_number = getSkipNumber(abbr, i);
            if (skip_number == 0) {
                if (word[pos] != abbr[i]) return false;
                else ++ pos, ++i;
            } else {
                pos += skip_number;
                i += std::to_string(skip_number).size();
            }
        }
        
        return pos == n && i == m;
    }
};
```

### Solution two

```cpp
class Solution {
public:
  bool validWordAbbreviation(string word, string abbr) {
    int i = 0, j = 0;
    while (i < word.size() && j < abbr.size()) {
      if (isdigit(abbr[j])) {
        if (abbr[j] == '0') return false;
        int val = 0;
        while (j < abbr.size() && isdigit(abbr[j]))
          val = val * 10 + abbr[j++] - '0';
        i += val;
      }
      else if (word[i++] != abbr[j++]) return false;
    }
    return i == word.size() && j == abbr.size();
  }
};
```
