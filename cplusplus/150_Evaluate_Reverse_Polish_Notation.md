
Evaluate the value of an arithmetic expression in [Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation).

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:

```
  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
```

# Solution


```cpp
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
```

# Knowledge

### Reverse Polish notation

__Reverse Polish notation (RPN)__, also known as Polish postfix notation or simply postfix notation, is a mathematical notation in which operators follow their operands, in contrast to __Polish notation (PN)__, in which operators precede their operands. It does not need any parentheses as long as each operator has a fixed number of operands. 

In computer science, reverse Polish notation is often used in stack-oriented and concatenative programming languages. It is also common in dataflow and pipeline-based systems, including Unix pipelines.
                                                                            
##### Explanation
                                                                            
In reverse Polish notation, the operators follow their operands; for instance, to add 3 and 4, one would write ```3 4 +``` rather than ```3 + 4```. If there are multiple operations, operators are given immediately after their second operands; so the expression written ```3 − 4 + 5``` in conventional notation would be written ```3 4 − 5 +``` in reverse Polish notation: 4 is first subtracted from 3, then 5 is added to it. An advantage of reverse Polish notation is that it removes the need for parentheses that are required by infix notation. While ```3 − 4 × 5``` can also be written ```3 − (4 × 5)```, that means something quite different from ```(3 − 4) × 5```. In reverse Polish notation, the former could be written ```3 4 5 × −```, which unambiguously means ```3 (4 5 ×) −``` which reduces to ```3 20 −```; the latter could be written ```3 4 − 5 ×``` (or ```5 3 4 − ×```, if keeping similar formatting), which unambiguously means ```(3 4 −) 5 ×```.
                                                                            
##### Converting from infix notation
                                                                            
                                                                            
