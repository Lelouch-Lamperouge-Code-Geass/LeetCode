Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

# Solution

* https://en.wikipedia.org/wiki/Roman_numerals

We start from the end of string, if the char is smaller than next char, minus it, otherwise add it.
 
__Time complexity is O(n), and space complexity is O(1).__
  
```cpp
class Solution {
public:
  int romanToInt(string s) {
    int reval(0);
    int n(s.size()), i(n - 1);
    while (i >= 0) {
      if (i >= 0 && RomanCharToInteger(s[i]) < RomanCharToInteger(s[i+1])) {
        reval -= RomanCharToInteger(s[i]);
      } else {
        reval += RomanCharToInteger(s[i]);
      }
      -- i;
    }
    return reval;
  }
private:
  int RomanCharToInteger(char c) {
    switch (c) {
    case 'I' : return 1;
    case 'V' : return 5;
    case 'X' : return 10;
    case 'L' : return 50;
    case 'C' : return 100;
    case 'D' : return 500;
    case 'M' : return 1000;
    default : return 0;
    }
  }
};
```
