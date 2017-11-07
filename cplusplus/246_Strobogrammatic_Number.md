A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.

For example, the numbers "69", "88", and "818" are all strobogrammatic.

# Solution

```cpp
class Solution {
public:
    bool isStrobogrammatic(string num) {
        static unordered_map<char, char> rotation_mapper = {
            {'0','0'},  {'1','1'}, {'6','9'}, {'8','8'}, {'9','6'} 
        };
        
        if (!num.empty()) {

            while (low <= high) {
                if (rotation_mapper.count(num[low]) == 0
                   || rotation_mapper[num[low]] != num[high]) {
                    return false;
                } 
                
                ++ low;
                if (high > 0) -- high;
            }
        }
    
        return true;
    }
};
```
