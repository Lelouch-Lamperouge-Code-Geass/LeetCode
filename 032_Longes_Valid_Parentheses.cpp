/*
Solution 1
*/
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

/*
Solution 2
*/
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
