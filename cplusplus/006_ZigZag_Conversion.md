The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

```
P   A   H   N
A P L S I I G
Y   I   R
```

And then read line by line: "PAHNAPLSIIGYIR"  
Write the code that will take a string and make this conversion given a number of rows:  

```
string convert(string text, int nRows);
```

convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

# Solution

```cpp
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows <= 1) return s;
        vector<string> strs(numRows, "");
        int row(0), step(1);
        for (char c : s) {
            strs[row].push_back(c);
            
            if (row == 0) step = 1;
            if (row + 1 == numRows) step = -1;
            
            row += step;
        }
        
        ostringstream oss;
        for (const std::string &str : strs) {
            oss << str;
        }
        
        return oss.str();
    }
};
```
