Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.

For example, given the range [5, 7], you should return 4.
  
# Solution
  
The result of a range bitwise given a range [m, n] is the common prefix of bit representation of m and n.  
  
The idea is very simple:

1. last bit of (odd number & even number) is 0.
2. when m != n, There is at least an odd number and an even number, so the last bit position result is 0.
3. Move m and n rigth a position.

Keep doing step 1,2,3 until m equal to n, record the shift count in the meantime.  
 
Finally, left shift the common prefix with shift_count times.  

```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int shift(0);
        while (m != n) {
            m >>= 1;
            n >>= 1;
            ++ shift;
        }
        
        return (m << shift);
    }
};
```
