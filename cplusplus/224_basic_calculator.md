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

### Solution 1

Simple iterative solution by identifying characters one by one. One important thing is that the input is valid, which means the parentheses are always paired and in order.

Only 5 possible input we need to pay attention:

1. digit: it should be one digit from the current number
2. '+': number is over, we can add the previous number and start a new number
3. '-': same as above
4. '(': push the previous result and the sign into the stack, set result to 0, just calculate the new result within the parenthesis.
5. ')': pop out the top two numbers from stack, first one is the sign before this pair of parenthesis, second is the temporary result before this pair of parenthesis. We add them together.

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
                    sign = 1; // Not neccessary, since we know there must be a sign after )
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

### Solution 2

Using similar shutting-yard algirthm.

```cpp
class Solution {
public:
    int calculate(string s) {
        int reval(0);
        vector<char> operators;
        vector<int> values;
        vector<string> tokens = getTokens(s);
        
        for (const string &token : tokens) {
            if (token[0] == '(' ) {
                operators.emplace_back(token[0]);
            } else if (token[0] == ')') {
                while (operators.back() != '(') {
                    calculate(operators, values);
                }
                operators.pop_back(); // pop out '('
            } else if (token[0] == '+' || token[0] == '-') {
                while (!operators.empty() && operators.back() != '(') {
                    calculate(operators, values);
                }
                operators.emplace_back(token[0]);
            } else { // is number
                values.emplace_back(std::stoi(token));
            }
        }
        
        while (!operators.empty()) {
            calculate(operators, values);
        }
        
        return values.back();
    }
private:
    void calculate(vector<char> &operators, vector<int> &values) {
        if (operators.empty() || values.empty()) return;
        char op = operators.back();
        operators.pop_back();
        int right = values.back();
        values.pop_back();
        int left = values.back();;
        values.pop_back();
        if (op == '+') {
            values.emplace_back(left + right); 
        } else { // op == '-'
            values.emplace_back(left - right);  
        }
    }
    
    vector<string> getTokens(const string &s) {
        vector<string> tokens;
        std::size_t pos(0), n(s.size());
        
        while (pos < n) {
            if (s[pos] == '(' || s[pos] == ')' || s[pos] == '+' || s[pos] == '-') {
                tokens.emplace_back(string(1, s[pos]));
                ++ pos;
            } else if (std::isdigit(s[pos])){
                string number("");
                while (pos < n && std::isdigit(s[pos])) {
                    number.push_back(s[pos]);
                    ++ pos;
                }
                tokens.emplace_back(number);
            } else { //ignore invalid 
                ++ pos;
            }
        }
        
        return tokens;
    }
};
