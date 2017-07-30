Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

* Given numerator = 1, denominator = 2, return "0.5".
* Given numerator = 2, denominator = 1, return "2".
* Given numerator = 2, denominator = 3, return "0.(6)".

# Solution

The important thing is to consider all edge cases while thinking this problem through, including: negative integer, possible overflow, etc.

Use HashMap to store a remainder and its associated index while doing the division so that whenever a same remainder comes up, we know there is a repeating fractional part.

```cpp
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (denominator == 0) return "";
        if (numerator == 0) return "0";
        
        // get integer part
        std::string reval(""); 
        
        // check sign
        if (numerator < 0 ^ denominator < 0) reval.push_back('-');
        
        long abs_numerator = std::labs(numerator);
        long abs_denominator = std::labs(denominator);
        
        reval += std::to_string(abs_numerator / abs_denominator);
        
        // no remainder ?
        if (abs_numerator % abs_denominator == 0) return reval;
        
        // add decimal point
        reval.push_back('.');
        
        // begin process decimal part
        
        // use a hashmap to record the numerator we used in decimal part
        // and its corresopnding index of return value string.
        abs_numerator %= abs_denominator;
        std::unordered_map<long, std::size_t> used_numerator;

        while (abs_numerator) {         
            if (used_numerator.count(abs_numerator) > 0) { // find a recurring numerator
                reval.insert(reval.begin() + used_numerator.at(abs_numerator), '(');
                reval.push_back(')');
                break;
            } else {
                used_numerator.emplace(std::make_pair(abs_numerator, reval.size()));
                abs_numerator *= 10;
                reval.push_back('0' + abs_numerator/ abs_denominator);
                abs_numerator %= abs_denominator;
            }
        }
        
        return reval;
    }
};
```
