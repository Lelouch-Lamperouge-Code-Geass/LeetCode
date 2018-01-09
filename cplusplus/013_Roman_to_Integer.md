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
    std::size_t n(s.size()), i(n);
    while (i-- > 0) {
      if (i + 1 < n && RomanCharToInteger(s[i]) < RomanCharToInteger(s[i+1])) {
        reval -= RomanCharToInteger(s[i]);
      } else {
        reval += RomanCharToInteger(s[i]);
      }
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

# Knowledge

### Subtractive notation

Subtractive notation is an early form of positional notation used with Roman numerals as a shorthand to replace four or five characters in a numeral representing a number with usually just two characters.

Using subtractive notation the numeral VIIII becomes simply IX. Without subtractive notation, XIV represents the same number as XVI (16 in Arabic numerals). With the introduction of subtractive notation, XIV (14) no longer represents the same number as XVI but rather is an alternate way of writing XIIII.
