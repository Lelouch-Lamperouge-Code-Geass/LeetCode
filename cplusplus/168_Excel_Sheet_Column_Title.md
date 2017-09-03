Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

```
1 -> A
2 -> B
3 -> C
...
26 -> Z
27 -> AA
28 -> AB 
```    

# Solution

Let's see the relationship between the Excel sheet column title and the number:

```
A   1     AA    26+ 1     BA  2×26+ 1     ...     ZA  26×26+ 1     AAA  1×26²+1×26+ 1
B   2     AB    26+ 2     BB  2×26+ 2     ...     ZB  26×26+ 2     AAB  1×26²+1×26+ 2
.   .     ..    .....     ..  .......     ...     ..  ........     ...  .............   
.   .     ..    .....     ..  .......     ...     ..  ........     ...  .............
.   .     ..    .....     ..  .......     ...     ..  ........     ...  .............
Z  26     AZ    26+26     BZ  2×26+26     ...     ZZ  26×26+26     AAZ  1×26²+1×26+26
```

本质是进制转换，将n转化为26进制，转化过程如下（括号里的是26进制数）：

```
1->(1)->A
2->(2)->B
...
26->(10)->Z
27->(11)->AA
28->(12)->AB
.....
52->(20)->AZ
53->(21)->BA
```

从least significant digit开始，不断地除以26取余数

因为A是1，而不是0，相当于26进制的数都整体减1，才能对应上从0开始的十进制数。
 
consider the letter 'A' to have a value of 1, 'B'->2 ..... 'Z'->26
note that in the above notation, values are 1-based

here our Radix (R) == 26

the final value of a number X Y Z = X * R^2 + Y * R + Z

this looks similar to base-10 decimal number but the biggest difference is that the numbers on every digit starts with 1, instead of 0., and the max on each digit goes up to R (Radix) instead of R-1

for example
```
Z== Radix
then next number is AA = R + 1 = Z+1
ZZ = R * R + R
next number is AAA = 1*R^2 + 1 * R + 1 = ZZ +1
```
so from the AAA notation to their sequence number (decimal) it's easy, but the other way is a bit tricky due to the way % and / operates

```cpp
class Solution {
 public:
  // Instead of 1 -> A, 26 -> Z, we can assume that 0 -> A, 25 -> Z, and then
  // here comes the base 26 representation, it's similar when you convert a
  // number from base 10 to base 2
  string convertToTitle(int n) {
        string reval("");
        
        while (n) {
            -- n;
            reval.push_back('A' + n % 26);
            n /= 26;
        }
        
        std::reverse(reval.begin(), reval.end());
        return reval;
    }
};
```
