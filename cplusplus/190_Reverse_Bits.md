Reverse bits of a given 32 bits unsigned integer.

For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).

##### Follow up:

If this function is called many times, how would you optimize it?

# Solution

```cpp
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t reval(0);
        // Add bit 32 times
        for (int i = 0; i < 32; ++i) {
          reval = (reval << 1) | (n & 1);
          n >>= 1;
        }
        return reval;
    }
};
```

__Note: Don't make a dumb mistake as I did like follow.__

It doesn't work because the loop may stop once there are no higher '1' bit, for example:

```
Input: 1 (00000000000000000000000000000001)
Output: 1 (00000000000000000000000000000001)
Expected: 2147483648 (10000000000000000000000000000000)
```


```cpp
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t reval(0);
        
        while (n) {
            reval = (reval << 1) | (n & 1);
            n >>= 1;
        }
        
        return reval;
    }
};
```

