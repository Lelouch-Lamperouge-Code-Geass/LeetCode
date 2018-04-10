Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.
  
![alt](https://upload.wikimedia.org/wikipedia/commons/thumb/7/73/Telephone-keypad2.svg/200px-Telephone-keypad2.svg.png)
       
```
Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
```

# Solution

```cpp
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return vector<string>();
        vector<string> reval(1, "");
        
        for (char digit : digits) {
            const string &letters = getLetters(digit);
            vector<string> temp;
            for (char letter : letters) {
                for (const string &pre : reval) {
                    temp.emplace_back(pre);
                    temp.back().push_back(letter);
                }
            }
            reval = temp;
        }
        
        return reval;
    }
private:
    std::string getLetters(char digit) {
        static vector<string> letters = {
          "","","abc","def", "ghi", "jkl", "mno", "pqrs","tuv", "wxyz"  
        };
        
        return letters[digit - '0'];
    }
};
```
