Given two binary strings, return their sum (also a binary string).  

For example,  
a = "11"  
b = "1"  
Return "100".  


# Solution

Begin add number from back of string a, b.

Since we get the final string from back, don't forget to reverse it before return it.

```cpp
class Solution {
public:
  string addBinary(string a, string b) {
    std::string res("");
      
    // i, j begin with size of a, b
    std::size_t i(a.size()), j(b.size());
      
    int carry(0);
      
    while (i > 0 || j > 0 || carry) {    
      int cur_val(carry);
      if (i > 0) cur_val += a[--i] - '0';
      if (j > 0) cur_val += b[--j] - '0';
      res.push_back('0' + cur_val % 2);
      carry = cur_val / 2;
    }
    std::reverse(res.begin(),res.end());
    return res;
  }
};
```
