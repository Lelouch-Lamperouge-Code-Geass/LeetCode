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

__How to optimize if this function is called multiple times? We can divide an int into 4 bytes, and reverse each byte then combine into an int. For each byte, we can use cache to improve performance.__

```cpp
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        std::vector<uint32_t> bytes(4, 0);
        for (int i = 0; i < 4; i++) {
            // convert int into 4 bytes
            int temp = ((n >> 8*i) & 0xFF);
            bytes[i] = temp;
        }
        int result(0);
        for (int i = 0; i < 4; i++) {
            result += reverseByte(bytes[i]); // reverse per byte
            if (i < 3) {
                result <<= 8;
            }
        }
        return result;
    }
private:
    // This function will return a 32-bit number
    // with reversed last 8 bits of n.
    uint32_t reverseByte(uint32_t n) {
        if (m_cache.count(n)) return n;
        uint32_t reval(0);
        for (int i = 0; i < 8; ++i) {
            reval = (reval << 1) | (n & 1);
            n >>= 1;
        }
        m_cache[n] = reval;
        return reval;
    }
    std::unordered_map<uint32_t, uint32_t> m_cache;
};
```

# Solution 2

However, this solution is too specific. With different size of int, the code needs to be changed to adapt the new size. The operations will always be log sizeof(int) to finish each individual tasks.

```cpp
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        n = (n >> 16) | (n << 16);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        return n;
    }
};
```
