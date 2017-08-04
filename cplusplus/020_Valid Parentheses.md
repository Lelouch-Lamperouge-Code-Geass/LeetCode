Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

# Solution

```cpp
class Solution {
public:
    bool isValid(string s) {
        std::stack<char> parentheses;
        for (char c : s) {
            if ('(' == c) {
                parentheses.push(')');
            } else if ('{' == c) {
                parentheses.push('}');
            } else if ('[' == c) {
                parentheses.push(']');
            } else {
                if (parentheses.empty() || parentheses.top() != c) {
                    return false;
                } else {
                    parentheses.pop();
                }
            }
        }
        
        return parentheses.empty();
    }
};
```

```cpp
class Solution {
public:
    bool isValid(string s) {
        std::stack<char> lefts;
        for(std::size_t i=0;i<s.size();++i){
            if(s[i]=='('||s[i]=='{'||s[i]=='['){
                lefts.push(s[i]);
            } else {
                const char lm ( get_left(s[i]) );
                if(lefts.empty() || lefts.top()!=lm) {
                    return false;
                } else {
                    lefts.pop();
                } 
            }
        }
        return lefts.empty();
    }
private:
    char get_left(char c){
        switch(c){
            case ')' : return '(';
            case '}' : return '{';
            case ']' : return '[';
            default : return ' ';
        }
    }
};
```

