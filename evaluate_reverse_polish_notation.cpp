// Copyright (C) 2016 by Yang Liu
class Solution {
public:
  int evalRPN(vector<string>& tokens) {
    std::stack<int> operands;
    for (const string & token : tokens) {
      if (token.size()==1 && !std::isdigit(token[0])) {
        int right = operands.top();
        operands.pop();
        switch (token[0]) {
        case '+': operands.top() += right; break;
        case '-': operands.top() -= right; break;
        case '*': operands.top() *= right; break;
        case '/': operands.top() /= right; break;
        default: break;
        }
      } else {
        // it is a number,push it into stack
        operands.push(std::stoi(token));
      }
    }
    return operands.top();
  }
};
