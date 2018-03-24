Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

# Solution

In order to solve problems related to roman numberal, remember that roman numberal and arabic numeral are not that different. The only difference they have is how their symbols represent each digit.

For example, for number ```3526```, its roman numberal is ```MMMDXXVI```.

```
3     5   2   6
MMM   D   XX  VI   
```

In arabic numeral, digits are alwasy 0-9, ```3``` in ```123``` represent three digits in ones place, ```3``` in ```231``` represent three digits in tens place, ```3``` in ```321``` represent three digits in hundreds  place. The digit's position plays a very important role here.

In roman numeral, digit changes. ```III``` represent three digits in ones place, ```XXX``` represent three digits in tens place, ```CCC``` represent three digits in ones  place. The digit's position doesn't paly an important role here.

Nevertheless, here their radix are 10-based. All we need care is how to represent the digit.

### Solution one

We start from the end of string, if number on current char is smaller than number on next char, minus it, otherwise add it.
 
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

### Solution two

Start from left to right, add each number and also record previous number.

If we ever meet a number which is larger than previous number, that means we need to minus ```2 * previous\_number```.

__Time complexity is O(n), and space complexity is O(1).__
  

```cpp
class Solution {
public:
  int romanToInt(string s) {
    int reval(0);
    int pre_number(0);
    for (int i = 0, n = s.size();i < n; ++i) {
        if (i > 0 && RomanCharToInteger(s[i]) > RomanCharToInteger(s[i - 1])) {
            reval -= 2 * pre_number; 
        }
        reval += RomanCharToInteger(s[i]);
        pre_number = RomanCharToInteger(s[i]);
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

https://en.wikipedia.org/wiki/Roman_numerals

### Subtractive notation

Subtractive notation is an early form of positional notation used with Roman numerals as a shorthand to replace four or five characters in a numeral representing a number with usually just two characters.

Using subtractive notation the numeral VIIII becomes simply IX. Without subtractive notation, XIV represents the same number as XVI (16 in Arabic numerals). With the introduction of subtractive notation, XIV (14) no longer represents the same number as XVI but rather is an alternate way of writing XIIII.
