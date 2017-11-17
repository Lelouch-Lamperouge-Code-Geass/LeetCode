Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

Example:

```
Input: "Hello World"
Output: 5
```

# Solution
  
```cpp
class Solution {
public:
  int lengthOfLastWord(string s) {
    int end(s.size()-1);
    while (end >=0 && !std::isalpha(s[end])) -- end; // Take care of tailing ' '
    
    if (end == -1) return 0; // No word exist
    
    int start = end;
    while (start - 1 >= 0 && std::isalpha(s[start-1])) -- start;
    
    return end - start + 1;
  }
};
```
