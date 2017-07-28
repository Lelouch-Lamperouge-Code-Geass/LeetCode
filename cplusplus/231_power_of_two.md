Given an integer, write a function to determine if it is a power of two.
  
# Solution

Note that integer can be negative or zero.
  
In sign-magnitude representation: The most-significant bit (msb) is the sign bit, with value of 0 representing positive integer and 1 representing negative integer. The remaining n-1 bits represents the magnitude (absolute value) of the integer.
  
In this question, we just need to make sure the number is positive and only has one set bit.
  
```cpp
class Solution {
public:
  bool isPowerOfTwo(int n) {
    return (n>0) && !(n & (n-1));
  }
};
```
