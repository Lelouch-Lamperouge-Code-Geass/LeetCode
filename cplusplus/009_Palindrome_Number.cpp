
Determine whether an integer is a palindrome. Do this without extra space.
  
##### Some hints:  
  
Could negative integers be palindromes? (ie, -1)  

If you are thinking of converting the integer to string, note the restriction of using extra space.  

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?  

There is a more generic way of solving this problem.  


# Solution

There are below corner cases you need to consider:

1. x < 0
2. x has tailing 0, e.g. 100

```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || x > 0 && x % 10 == 0) return false;
        
        int y(0);
        while (x > y) {
            y = y * 10 + (x % 10);
            x /= 10;
        }
        
        return x == y || x == y / 10;
    }
};
```
