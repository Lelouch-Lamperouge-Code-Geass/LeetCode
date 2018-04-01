Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

##### Example 1:

```
Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
```

##### Example 2:

```
Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
```

__Note__: The input string length won't exceed 1000.

# Solution

### Solution 1, Dynamic programming

is_palindrome[i][j] means substring with range [i, j] is a palindrome or not.

Since is_palindrome[left][right] is based on is_palindrome[left + 1][right - 1], we need make sure that we have processed the substring first.

__The time complexity and space compelxity are both O(n^2).__

```
class Solution {
public:
    int countSubstrings(string s) {
        if (s.empty()) return 0;
        
        int s_size(s.size()), reval(0);;
        
        std::vector<std::vector<int>> is_palindrome(s_size, std::vector<int>(s_size, false));
        for (int right = 0; right < s_size; ++right) {
            for (int left = right; left >= 0; --left) {
                if (left == right) {
                    is_palindrome[left][right] = true;
                } else {
                    if (s[left] == s[right]) {
                        if (left + 1 == right) {
                            is_palindrome[left][right] = true;
                        } else {
                            is_palindrome[left][right] = is_palindrome[left + 1][right - 1];
                        }
                    }
                }
                reval += is_palindrome[left][right] ? 1 : 0;
            }
        }
        
        return reval;
    }
};
```

### Solution 2

Idea is start from each index and try to extend palindrome for both odd and even length.

The time complexity is O(n^2), when the case is like "aaaa....aaaaa", however this is not often the case. Unlike the Dynamic programming solution, whose time complexity is O(n^2) in whichever case. In practical, this solution will yield better performance since it can avoid some redundant calculations in general cases.

Also the space complexity is O(1), which is much better than the DP solution.

```cpp
class Solution {
private:
    int extendPalindrome(const string &s,
                         int left,
                         int right){
       int reval(0), s_size(s.size());
       while (left >= 0 && right < s_size) {
           if (s[left] == s[right]) {
               ++ reval;
               -- left, ++ right;
           } else {
               break;
           }
       }
       return reval;
    }
public:
    int countSubstrings(string s) {
        int reval(0);
        
        for (int i = 0, n = s.size(); i < n; ++i) {
            reval += extendPalindrome(s, i, i); // odd length;
            reval += extendPalindrome(s, i, i + 1); // even length
        }
        
        return reval;
    }
};
```
