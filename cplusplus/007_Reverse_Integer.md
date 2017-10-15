Reverse digits of an integer.

Example1: x = 123, return 321  
Example2: x = -123, return -321  
  
##### Note:  
The input is assumed to be a 32-bit signed integer. Your function should return 0 when the reversed integer overflows.

##### Sploi
  
Have you thought about this?  
  
Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!  

If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.  

Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. How should you handle such cases?  

For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.  
  
# Solution  

```cpp
class Solution {
public:
    int reverse(int x) {
        int sign = x > 0 ? 1 : -1;
        
        long abs_x = std::labs(x); 
        
        long reval(0);
        
        while (abs_x) {
            reval = reval * 10 + (abs_x % 10);
            if (reval > INT_MAX) return 0;
            abs_x /= 10;
        }
        
        reval *= sign;
        
        return reval < INT_MIN || reval > INT_MAX ? 0 : reval;
    }
};
```


# Knowledge

The specific guarantees are as follows:

* char is at least 8 bits (1 byte by definition, however many bits it is)
* short is at least 16 bits
* int is at least 16 bits
* long is at least 32 bits
* long long (in versions of the language that support it) is at least 64 bits

