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

# Understand the problem:

A classic 10-based math to 26-based math. Remember for a 10-based integer, e.g. 123, how can we extract each digit?  The idea is from the least significant digit and use %10 and /10 respectively. e.g. 

```
123 % 10 = 3, 123 / 10 = 12
12 % 10 = 2, 12 / 10 = 1
1 % 10 = 1, 1 / 10 - 0.
```

Therefore, for this question, we only need to replace 10 to 26. Note that for this question, the map is from 1 to 26. Therefore, we need to minus 1 for each number before the computation.  


# Solution

这个问题本质上是十进制转换成别的进制的问题.在这里我们需要把十进制转换成26进制.唯一要注意的地方是十进制的digit是从0开始的，而这里的26进制是从```1('A')```开始的. 而每个位上的digit是什么取决于在这个位上面的数值和base-digit的差值。比如说如果现在在这个位上面的数值是26, 而base-digit是 ```1(A)```, 那么差值就是25, 所以这个位上面的digit就应该是 ```1(A) + 25 = 26(Z)```. 记得最后的结果要反转这个字符串。

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

### Solution 1

To convert a radix-10 number to a different radix, here is what we need to do. We keep using ```mod``` operation on the number in order to get the "digit" on the new radix, and since we get the representation from least siginificant position to most significant position, eventually we need to reverse the representation string.

Our new number system's radix is 26, therefore we know that every postion can have 26 different digit.
Now the tricky part here is, in the new radix system, the beginning position is 1 not 0. Therefore, we need to make sure that ```1->A, 26->Z```.

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

# Knowledge

Simply put, a __number system__ is a way to represent numbers. We are used to using the base-10 number system, which is also called decimal. Other common number systems include base-16 (hexadecimal), base-8 (octal), and base-2 (binary).

In mathematical numeral systems, the __radix__ or __base__ is the number of unique digits, including zero, used to represent numbers in a positional numeral system. For example, for the decimal system (the most common system in use today) the radix is ten, because it uses the ten digits from 0 through 9.


