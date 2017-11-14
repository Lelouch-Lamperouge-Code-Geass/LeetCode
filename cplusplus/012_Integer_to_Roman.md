Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.

# Solution
 
```cpp  
class Solution {
public:
  string intToRoman(int num) {
    static string one[10] = {"","I","II","III","IV","V","VI","VII","VIII","IX"};
    static string ten[10] = {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
    static string hundred[10] = {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
    static string thousand[4] = {"","M","MM","MMM"};
    return thousand[num/1000]+hundred[(num%1000)/100]+ten[(num%100)/10]+one[(num%10)];
  }
};
```
