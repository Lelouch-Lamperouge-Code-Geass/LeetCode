Given an integer (signed 32 bits), write a function to check whether it is a power of 4.

Example:

Given num = 16, return true. Given num = 5, return false.

Follow up: Could you solve it without loops/recursion?

# Solution

Note : Relational operators(==, !=, <=, .....) has higher priority than bitwise operators(&, ^, |).

We need to make sure:

1. The number is not less than 1, because the number is an integer and the minimum power of 4 in integer is 1.
2. The number only has one set bit.
3. The set bit is on special position.

```cpp
class Solution {
public:
    bool isPowerOfFour(int num) {
        if (num < 1) return false; // Not less than 1
        if ( (num & (num - 1)) != 0) return false; // Only one set bit
        return (num & 0xAAAAAAAA) == 0; // Set bit is only on special position
    }
};
```

```cpp
class Solution {
public:
    bool isPowerOfFour(int num) {
          if (num < 1) return false;

          if ((num & (num - 1)) != 0) return false;
        
          return (num & 0x55555555) != 0;

    }
};
```
