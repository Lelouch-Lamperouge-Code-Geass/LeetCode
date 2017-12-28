A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).  

Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.  

For example,

Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three strobogrammatic numbers.  

Note:  
Because the range might be a large number, the low and high numbers are represented as string.  

# Solution

1. Initialize an all-'0' string with length from low.size() to high.size(), e.g. "0000"
2. Use two pointers, left and right position and try to fill left and right with mirror pairs
3. Finally, when left is larger than right, which means that we have filled the whole string. Then we need to make sure 
   the generated string is within range. If it is, increase the count.
   
Note here we don't use the methology like "247 Strobogrammatic Number II", which is building the strings from bottom up, and 
then check the string are within the range or not. This is because there are potentailly many redundant calculations there.

Let's say the "low" string has length == 10, then we need to get length == 10 strings based on length < 10 strings(0 to 9), the time complexity is pretty bad.

```cpp
class Solution {
private:
    void helper(string temp,
                int left,
                int right,
                const string &low,
                const string &high,
                int &count) {
        static std::unordered_map<char, char> mapper = {{'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}};
        if (left <= right) {
            // Try to build all possible strobogrammatic number
            for (const auto &item : mapper) {
                // Note here that if left == right, latter will overwrite former.
                // Therefore we need to handle this case afterwards.
                temp[left] = item.first;
                temp[right] = item.second;
                
                // avoid "080",...
                if (temp.size() > 1 && temp[0] == '0') continue; 
                
                // Like noted above, we need to handle the case when left == right.
                if (left < right || left == right && item.first == item.second) {
                    helper(temp, left + 1, right - 1, low, high, count);
                }
            }
        } else {
            // Current string has been filled up, let's check whether it is within [low, high]
            if (temp.size() == low.size() && temp.compare(low) < 0) return;
            if (temp.size() == high.size() && temp.compare(high) > 0) return;
            
            ++ count;
        }
    }
public:
    int strobogrammaticInRange(string low, string high) {
        int min_size(low.size()), max_size(high.size()), count(0);
        for (int size = min_size; size <= max_size; ++ size) {
            std::string temp(size, '0');
            helper(temp, 0, size - 1, low, high, count);
        }
        return count;
    }
};
```
