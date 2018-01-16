Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 2^31 - 1.

For example,

```
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
```
  
# Solution

The keypoint is to make sure helper function can return 
```
1. if number == 0, return "";
2. if number != 0, return number.toString() + ' ';
```

```cpp
class Solution {
private:
    vector<string> LESS_THAN_TWENTY = {
          "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", 
          "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"   
    };
    vector<string> LESS_THAN_ONE_HUNDRED = {
          "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"  
    };
    vector<string> THOURSANDS = {
          "", "Thousand","Million","Billion"  
    };
    // Return the number string with a trailing ' '.
    string getNumberStringLessThanThousand(int num) {
        ostringstream oss;
        if (num >= 100) {
            oss << LESS_THAN_TWENTY[num / 100] << " Hundred ";
            num %= 100;
        }
        
        if (num >= 20) {
            oss << LESS_THAN_ONE_HUNDRED[num / 10] << ' ';
            num %= 10;
        }
        
        if (num > 0) {
            oss << LESS_THAN_TWENTY[num] << ' ';
        }
        
        return oss.str();
    }
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        string reval("");
        std::size_t units_index(0);
        while (num) {
            if (num % 1000 != 0) { // Take care of 1,000,000
                reval = getNumberStringLessThanThousand(num % 1000) + THOURSANDS[units_index] + ' ' + reval;
            }
            num /= 1000;
            ++ units_index;
        }
        while (!reval.empty() && reval.back() == ' ') reval.pop_back();
        return reval;
    }
};
```


C++ version.  

```cpp
class Solution {
private:
    vector<string> LESS_THAN_TWENTY = {
          "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
          "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", 
          "Sixteen", "Seventeen", "Eighteen", "Nineteen"   
    };
    vector<string> LESS_THAN_ONE_HUNDRED = {
          "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", 
          "Eighty", "Ninety"  
    };
    vector<string> THOURSANDS = {
          "", "Thousand","Million","Billion"  
    };
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        string reval("");
        std::size_t index(0);
        while (num) {
            if (num % 1000 != 0) {
                reval = helper(num % 1000) + THOURSANDS[index] + ' '+ reval;
            }
            num /= 1000;
            ++ index;
        }
        
        // Remove trailing whitespaces
        size_t last = reval.find_last_not_of(' ');
        return reval.substr(0, last + 1);
    }
private:
    // Note that this function will convert number to string 
    // and the string will has one trailing whitespace.
    string helper(int num) {
        if (num == 0) {
            return "";
        } else if (num < 20) {
            return LESS_THAN_TWENTY[num] + ' ';
        } else if (num < 100) {
            return LESS_THAN_ONE_HUNDRED[num / 10] + ' ' + helper(num % 10);
        } else  {
            return LESS_THAN_TWENTY[num / 100] + " Hundred " + helper(num % 100);
        }
    }
    
};
```
