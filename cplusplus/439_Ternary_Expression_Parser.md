Given a string representing arbitrarily nested ternary expressions, calculate the result of the expression. You can always assume that the given expression is valid and only consists of digits 0-9, ?, :, T and F (T and F represent True and False respectively).

Note:

1. The length of the given string is ≤ 10000.
2. Each number will contain only one digit.
3. The conditional expressions group right-to-left (as usual in most languages).
4. The condition will always be either T or F. That is, the condition will never be a digit.
5. The result of the expression will always evaluate to either a digit 0-9, T or F.

Example 1:

```
Input: "T?2:3"

Output: "2"

Explanation: If true, then result is 2; otherwise result is 3.
```

Example 2:

```
Input: "F?1:T?4:5"

Output: "4"

Explanation: The conditional expressions group right-to-left. 
Using parenthesis, it is read/evaluated as:

             "(F ? 1 : (T ? 4 : 5))"                   "(F ? 1 : (T ? 4 : 5))"
          -> "(F ? 1 : 4)"                 or       -> "(T ? 4 : 5)"
          -> "4"                                    -> "4"
```

Example 3:

```
Input: "T?T?F:5:3"

Output: "F"

Explanation: The conditional expressions group right-to-left. 
Using parenthesis, it is read/evaluated as:

             "(T ? (T ? F : 5) : 3)"                   "(T ? (T ? F : 5) : 3)"
          -> "(T ? F : 3)"                 or       -> "(T ? F : 5)"
          -> "F"                                    -> "F"
```

# Solution

I was trying to solve the problem with this, which is not working for "T?T?F:5:3".

```cpp
class Solution {
public:
    string parseTernary(string expression) {
        const std::size_t colon_pos = expression.find_first_of(':');
        if (colon_pos == std::string::npos) {
            return expression;
        } else {
            const std::size_t question_mark_pos = expression.find_first_of('?');
            const std::string condition(expression.substr(0, question_mark_pos));
            const std::string left_expression(
                expression.substr(question_mark_pos + 1, colon_pos - question_mark_pos -1 )
            );
            const std::string right_expression(
                expression.substr(colon_pos + 1)
            );
            
            
            return condition == "T" ? parseTernary(left_expression) : parseTernary(right_expression);
        }
    }
};
```

Here is the right solution. The time complexity is O(n).

```cpp
class Solution {
public:
    string parseTernary(string expression) {
        std::stack<char> tokens;
        for (std::size_t n = expression.size(), i = n; i-- > 0; ) {
            const char c = expression[i];
            
            if (!tokens.empty() && tokens.top() == '?') {
                // pop '?'
                tokens.pop();
                
                // pop left char
                char left = tokens.top();
                tokens.pop(); 
                
                // pop ':'
                tokens.pop(); 
                
                // pop right char
                char right = tokens.top();
                tokens.pop(); 
                
                if (c == 'T') {
                    tokens.push(left);
                } else {
                    tokens.push(right);
                }
            } else {
                tokens.push(c);
            }
        }
        
        return std::string(1, tokens.top());
    }
};
```







