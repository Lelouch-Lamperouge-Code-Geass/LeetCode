The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

```
00 - 0
01 - 1
11 - 3
10 - 2
```

__Note:__

For a given n, a gray code sequence is not uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.

For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.

# Solution

### Solution one

My idea is to generate the sequence iteratively. For example, when n=3, we can get the result based on n=2.
00,01,11,10 -> (000,001,011,010 ) (110,111,101,100). The middle two numbers only differ at their highest bit, while the rest numbers of part two are exactly symmetric of part one. It is easy to see its correctness.

```cpp
class Solution {
public:
    vector<int> grayCode(int n) {
        if(n<0) return vector<int>();
        vector<int> reval(1,0);
        reval.reserve(2*n);
        for(int i=1;i<=n;++i){
            int pre_size = reval.size();
            int k = 1 << (i-1);
            for(int j=pre_size-1;j>=0;--j){
                reval.push_back(k+reval[j]);
            }
        }
        return reval;
    }
};
```

### Solution two

We can convert the number to its grey code by ```grey-code(num) = num ^ (num >> 1)```. 



```cpp
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> reval;
        for (int i = 0, max = (1 << n); i < max; ++i) {
            reval.emplace_back(i ^ (i>>1));
        }
        
        return reval;
    }
};
```

# Knowledge

### Gray code

The __reflected binary code (RBC)__, also known just as reflected binary (RB) or __Gray code__ after Frank Gray, is an ordering of the binary numeral system such that two successive values differ in only one bit (binary digit). The reflected binary code was originally designed to prevent spurious output from electromechanical switches. Today, Gray codes are widely used to facilitate error correction in digital communications such as digital terrestrial television and some cable TV systems.

Many devices indicate position by closing and opening switches. If that device uses natural binary codes, positions 3 and 4 are next to each other but all three bits of the binary representation differ: ```3(011), 4(100)```. The problem with natural binary codes is that physical switches are not ideal: it is very unlikely that physical switches will change states exactly in synchrony. In the transition between the two states shown above, all three switches change state. In the brief period while all are changing, the switches will read some spurious position. Even without keybounce, the transition might look like ```011 — 001 — 101 — 100```. When the switches appear to be in position 001, the observer cannot tell if that is the "real" position 001, or a transitional state between two other positions. If the output feeds into a sequential system, possibly via combinational logic, then the sequential system may store a false value. _The reflected binary code solves this problem by changing only one switch at a time, so there is never any ambiguity of position._

More formally, a Gray code is a code assigning to each of a contiguous set of integers, or to each member of a circular list, a word of symbols such that no two code words are identical and each two adjacent code words differ by exactly one symbol. These codes are also known as single-distance codes, reflecting the Hamming distance of 1 between adjacent codes. In principle, there can be more than one such code for a given word length, but the term Gray code was first applied to a particular binary code for non-negative integers, the binary-reflected Gray code, or BRGC, the four-bit version of which is shown above.

The following functions in C convert between binary numbers and their associated Gray codes. While it may seem that gray-to-binary conversion requires each bit to be handled one at a time, faster algorithms exist.

```c
/*
 * This function converts an unsigned binary
 * number to reflected binary Gray code.
 *
 * The operator >> is shift right. The operator ^ is exclusive or.
 */
unsigned int binaryToGray(unsigned int num)
{
    return num ^ (num >> 1);
}

/*
 * This function converts a reflected binary
 * Gray code number to a binary number.
 * Each Gray code bit is exclusive-ored with all
 * more significant bits.
 */
unsigned int grayToBinary(unsigned int num)
{
    unsigned int mask = num;
    while (mask != 0)
    {
        mask = mask >> 1;
        num = num ^ mask;
    }
    return num;
}

/*
 * A more efficient version for gray codes 32 bits or fewer
 * through the use of SWAR (SIMD within a register) techniques.
 * It implements a parallel prefix XOR function.
 * 
 * This function can be adapted for longer gray codes by adding steps.
 * A 4-bit variant changes a binary number (abcd)2 to (abcd)2 ^ (00ab)2,
 * then to (abcd)2 ^ (00ab)2 ^ (0abc)2 ^ (000a)2.
 */
unsigned int grayToBinary32(unsigned int num)
{
    num = num ^ (num >> 16);
    num = num ^ (num >> 8);
    num = num ^ (num >> 4);
    num = num ^ (num >> 2);
    num = num ^ (num >> 1);
    return num;
}
```

