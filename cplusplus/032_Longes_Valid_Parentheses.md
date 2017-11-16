

# Solution

### Solution one, using a stack

The workflow of the solution is as below.

Scan the string from beginning to end.

1. If current character is '(', push its index to the stack.   
2. If current character is ')' and the character at the index of the top of stack is '(', we just find a matching pair so pop from the stack. Otherwise, we push the index of ')' to the stack.  
3. After the scan is done, the stack will only contain the indices of characters which cannot be matched. Then let's use the opposite side - substring between adjacent indices should be valid parentheses.  
4. If the stack is empty, the whole input string is valid. Otherwise, we can scan the stack to get longest valid substring as described in step 3.  

```
class Solution {
public:
  int longestValidParentheses(string s) {
    stack<int> parens;
    for (int i=0;i<s.size();++i) {
      if (s[i]==')' && !parens.empty() && s[parens.top()]=='(') {
        parens.pop();
      } else {
        parens.push(i);
      }
    }

    int reval(0),end(s.size());
    while (!parens.empty()) {
      reval = std::max(reval,end-parens.top()-1);
      end = parens.top();
      parens.pop();
    }
    reval = std::max(reval,end);

    return reval;
  }
};
```


### Soluiont two, dynamic programming


This solution uses DP. The main idea is as follows: I construct a array longest[], for any longest[i], it stores the longest length of valid parentheses which is end at i.

And the DP idea is :

1. If s[i] is '(', set longest[i] to 0, because any string end with '(' cannot be a valid one.

2. Else if s[i] is ')'
   * If s[i-1] is '(', longest[i] = longest[i-2] + 2
   * Else if s[i-1] is ')' and s[i-longest[i-1]-1] == '(', longest[i] = longest[i-1] + 2 + longest[i-longest[i-1]-2]

For example, input "()(())", at i = 5, longest array is [0,2,0,0,2,0], longest[5] = longest[4] + 2 + longest[1] = 6.

```cpp
class Solution {
public:
  int longestValidParentheses(string s) {
    int reval(0);
    const int s_size(s.size());
    // Represents the longest valid parentheses
    // length including current char
    vector<int> dp(s_size,0);
    for(int i=1;i<s_size;++i){
      if(s[i]==')'){
        int pre = i - dp[i-1] -1;
        if(pre>=0 && s[pre]=='('){
          dp[i] = dp[i-1] + 2 + (pre>=1? dp[pre-1] : 0);
          reval = std::max(reval,dp[i]);
        }
      }
    }
    return reval;
  }
};
```
