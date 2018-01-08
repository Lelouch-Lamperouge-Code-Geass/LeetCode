Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

##### Example 1:

```
Input: "aba"
Output: True
```

##### Example 2:

```
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.
```

##### Note:

The string will only contain lowercase characters a-z. The maximum length of the string is 50000.

__O(n) Time O(1) Space.__

```cpp
class Solution {
public:
    bool validPalindrome(string s) {
        std::size_t left(0), right(s.size() - 1);
        while (left < right && s[left] == s[right]) {
            ++ left;
            if (right > 0) -- right;
        }
        
        if (left >=  right) return true;
        else return isPalindrome(s, left + 1, right) || isPalindrome(s, left, right - 1);
    }
private:
    bool isPalindrome(const string &s, 
                  std::size_t left, 
                  std::size_t right) {
        while (left < right && s[left] == s[right]) {
            ++ left;
            if (right > 0) -- right;
        }
        return left >= right;
    }
};
```
