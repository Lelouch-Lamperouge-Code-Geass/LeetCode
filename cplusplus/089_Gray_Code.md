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

# Knowledge

### Gray code

The __reflected binary code (RBC)__, also known just as reflected binary (RB) or __Gray code__ after Frank Gray, is an ordering of the binary numeral system such that two successive values differ in only one bit (binary digit). The reflected binary code was originally designed to prevent spurious output from electromechanical switches. Today, Gray codes are widely used to facilitate error correction in digital communications such as digital terrestrial television and some cable TV systems.



