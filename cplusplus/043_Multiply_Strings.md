Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2.

Note:

1. The length of both num1 and num2 is < 110.
2. Both num1 and num2 contains only digits 0-9.
3. Both num1 and num2 does not contain any leading zero.
4. You must not use any built-in BigInteger library or convert the inputs to integer directly.

# Solution

Remember how we do multiplication?

Start from right to left, perform multiplication on every pair of digits, and add them together. Let's draw the process! From the following draft, we can immediately conclude:
```num1[i] * num2[j]` will be placed at indices `[i + j`, `i + j + 1]```  
  
![alt](https://drscdn.500px.org/photo/130178585/m%3D2048/300d71f784f679d5e70fadda8ad7d68f)


We have to begin backwards since if we handle the most siginificant position first, how can we update if the product of lower position is 10~ , in which case the higher position need +1?

Another thing need to be pointed out is, for example, let's say the higher position's value is 9, and we just calculated the product of lower position is 10. In this case, the higher position's value +1 ==10. But we don't need to worry about that since we're going to process the higher position later.

We also know that the result string's size won't be more than the sum of the two input strings' size.

Some edge cases:

1. We need take care of leading '0'.  
2. The final result can be "0".  

```cpp
class Solution {
public:
    string multiply(string num1, string num2) {
        const std::size_t n1(num1.size()), n2(num2.size());
        string reval(n1 + n2, '0');
        
        for (std::size_t i = n1; i-- > 0; ) {
            for (std::size_t j = n2; j-- > 0; ) {
                std::size_t pos = i + j + 1;
                std::size_t pre_pos = i + j;
                int val = (reval[pos] - '0') + (num1[i] - '0') * (num2[j] - '0');
                reval[pos] = '0' + (val % 10);
                reval[pre_pos] += (val / 10); // May be larger than 10 at first, 
                                              // but will be updated afterwards
            }
        }
        
        std::size_t non_zero = reval.find_first_not_of('0');
        if (non_zero == std::string::npos) return "0";
        else return reval.substr(non_zero);
    }
};
```
