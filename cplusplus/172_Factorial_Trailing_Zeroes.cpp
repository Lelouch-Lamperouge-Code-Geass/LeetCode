Given an integer n, return the number of trailing zeroes in n!.

Note: Your solution should be in logarithmic time complexity.
  
  
# Solution
  
The idea is:

1. The ZERO comes from 10.
2. The 10 comes from 2 x 5
3. And we need to account for all the products of 5 and 2. likes 4×5 = 20 ...
4. So, if we take all the numbers with 5 as a factor, we'll have way more than enough even numbers to pair with them to get factors of 10  
  

```cpp
class Solution {
public:
  int trailingZeroes(int n) {
    int result = 0;
    while(n){
      if(n/5) result += n/5;
      n /= 5;
    }
    return result;
  }
};
```
