Given an integer, write a function to determine if it is a power of three.

Follow up:

Could you do it without using any loop / recursion?

# Solution
  
  
### Solution one
  
Find the maximum integer that is a power of 3 and check if it is a multiple of the given input. 
  
```cpp  
class Solution {
public:
  bool isPowerOfThree(int n) {
    static int max_exponent = (int)(log(INT_MAX)/log(3));
    static int max_power_of_three = pow(3, max_exponent);
    if (n <= 0) return false;
    return (max_power_of_three % n == 0);
  }
};
```

### Solution two : Iterative Solution

```cpp
class Solution {
public:
  bool isPowerOfThree(int n) {
    while(n > 0 && n % 3 == 0) {
      n /= 3;
    }
    return n == 1;
  }
};
```

