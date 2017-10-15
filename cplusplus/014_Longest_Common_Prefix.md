Write a function to find the longest common prefix string amongst an array of strings.

# Solution

```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string reval("");
        std::size_t n = strs.size();
        if (n == 0) return reval;
        
        for (std::size_t i = 0; i < strs[0].size(); ++i) {
            char cur_char = strs[0][i];
            for (std::size_t j = 1; j < n; ++j) {
                if (i >= strs[j].size() 
                    || strs[j][i] != cur_char) {
                    return reval;
                }
            }
            reval.push_back(cur_char);
        }

        return reval;
    }
};
```
