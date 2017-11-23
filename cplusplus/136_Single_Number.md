Given an array of integers, every element appears twice except for one. Find that single one.

__Note:__

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

# Solution

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int reval(0);
        for(int num : nums){
            reval ^= num;
        }
        return reval;
    }
};
```

A different style.

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        return std::accumulate(nums.begin(),nums.end(),0,std::bit_xor<int>());
    }
};
```

# Knowledge

__Bit manipulation__ is the act of algorithmically manipulating bits or other pieces of data shorter than a word. Computer programming tasks that require bit manipulation include low-level device control, error detection and correction algorithms, data compression, encryption algorithms, and optimization. For most other tasks, modern programming languages allow the programmer to work directly with abstractions instead of bits that represent those abstractions. Source code that does bit manipulation makes use of the bitwise operations: AND, OR, XOR, NOT, and bit shifts.

Bit manipulation, in some cases, can obviate or reduce the need to loop over a data structure and can give many-fold speed ups, as bit manipulations are processed in parallel, but the code can become more difficult to write and maintain.

### Bitwise Operators

There are different bitwise operations used in the bit manipulation. These bit operations operate on the individual bits of the bit patterns. Bit operations are fast and can be used in optimizing time complexity. Some common bit operators are:

__NOT ( ~ ): Bitwise NOT__ is an unary operator that flips the bits of the number i.e., if the ith bit is 0, it will change it to 1 and vice versa. Bitwise NOT is nothing but simply the one’s complement of a number. Lets take an example. 

```
N = 5 = (101) 
~N = ~5 = ~(101) = (010) = 2
```

__AND ( & ): Bitwise AND__ is a binary operator that operates on two equal-length bit patterns. If both bits in the compared position of the bit patterns are 1, the bit in the resulting bit pattern is 1, otherwise 0.

```
A = 5 = (101) , B = 3 = (011),   A & B = (101) & (011)= (001) = 1
```

__OR ( | ): Bitwise OR__ is also a binary operator that operates on two equal-length bit patterns, similar to bitwise AND. If both bits in the compared position of the bit patterns are 0, the bit in the resulting bit pattern is 0, otherwise 1.

```
A = 5 = (101) , B = 3 = (011)
A | B = (101) | (011) = (111) = 7
```

__XOR ( ^ ): Bitwise XOR__ also takes two equal-length bit patterns. If both bits in the compared position of the bit patterns are 0 or 1, the bit in the resulting bit pattern is 0, otherwise 1.

```
A = 5 = (101) , B = 3 = (011)
A ^ B = (101) ^ (011) = (110) = 6
```

__Left Shift ( << ): Left shift operator__ is a binary operator which shift the some number of bits, in the given bit pattern, to the left and append 0 at the end. Left shift is equivalent to multiplying the bit pattern with 2^k ( if we are shifting k bits ).

```
1 << 1 = 2 = 1 * 2 ^ 1
1 << 2 = 4 = 1 * 2 ^ 2 
1 << 3 = 8 = 1 * 2 ^ 3
1 << 4 = 16 = 1 * 2 ^ 4 
…
1 << n = 1 * 2 ^ n
```

__Right Shift ( >> ): Right shift operator__ is a binary operator which shift the some number of bits, in the given bit pattern, to the right and append 1 at the end. Right shift is equivalent to dividing the bit pattern with 2^k ( if we are shifting k bits ).

```
4 >> 1 = 2
6 >> 1 = 3
5 >> 1 = 2
16 >> 4 = 1
```


