Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

You may assume that the given expression is always valid.

Some examples:

```
"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23
```

# Solution

Simple iterative solution by identifying characters one by one. One important thing is that the input is valid, which means the parentheses are always paired and in order.
Only 5 possible input we need to pay attention:

digit: it should be one digit from the current number
'+': number is over, we can add the previous number and start a new number
'-': same as above
'(': push the previous result and the sign into the stack, set result to 0, just calculate the new result within the parenthesis.
')': pop out the top two numbers from stack, first one is the sign before this pair of parenthesis, second is the temporary result before this pair of parenthesis. We add them together.
Finally if there is only one number, from the above solution, we haven't add the number to the result, so we do a check see if the number is zero.

```cpp
class Solution {
public:
    int calculate(string s) {
        int result(0), cur_number(0), sign(1);
        std::vector<int> values;
        
        for (char c : s) {
            if (std::isdigit(c)) {
                cur_number = cur_number * 10 + (c - '0');
            } else {
                if (c == '+') {
                    result += sign * cur_number;
                    sign = 1;
                    cur_number = 0;
                } else if (c == '-') {
                    result += sign * cur_number;
                    sign = -1;
                    cur_number = 0;
                } else if (c == '(') {
                    //we push the result first, then sign;
                    values.push_back(result);
                    values.push_back(sign);
                    //reset the sign and result for the value in the parenthesis
                    sign = 1;
                    result = 0;
                } else if (c == ')'){
                    result += sign * cur_number;  
                    cur_number = 0;
                    result *= values.back();    //values.back() is the sign before the parenthesis
                    values.pop_back();
                    result += values.back();   //values.back() now is the result calculated before the parenthesis
                    values.pop_back();
                } else {
                    // ignore
                }
            }
        }
        
        if(cur_number != 0) result += sign * cur_number;
        
        return result;
    }
};
```
