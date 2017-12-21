Related to question Excel Sheet Column Title

Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

```
    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
```

# Solution

```cpp
class Solution {
public:
    int titleToNumber(string s) {
        int reval(0);
        for(std::size_t i = 0, n = s.size();i < n; ++i){
            reval = reval * 26 + (s[i] - 'A' + 1);
        }
        return reval;
    }
}; 
```

A different style.

```cpp
class Solution {
public:
    int titleToNumber(string s) {
        int reval(0);
        
        int base(1);
        for (int i = s.size(); i-- > 0; ){
            reval += (s[i] - 'A' + 1) * base;
            base *= 26;
        }
        
        return reval;
    }
};
```
