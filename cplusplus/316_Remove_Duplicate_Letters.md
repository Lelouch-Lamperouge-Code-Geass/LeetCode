Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example:
Given "bcabc"
Return "abc"

Given "cbacdcbc"
Return "acdb"

# Solution
  
```cpp
// We need to keep the monotically decreasing substring that contains all the char in the s. 
// So we just use a vector to mimic the stack!
class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> remain_count(256, 0);
        vector<bool> added_to_result(256, false);
        for (char c : s)
            ++ remain_count[c];
        
        /** the key idea is to keep a monotically increasing sequence **/
        string result = "0";
        
        for (char c : s) {
            -- remain_count[c];
            if (added_to_result[c]) continue;
            while (c < result.back() && remain_count[result.back()] > 0) {
                // As long as current char is smaller than the last char of current result
                // and the last char of result will appear later, we can safely pop the last char out
                added_to_result[result.back()] = false;
                result.pop_back();
            }
            result.push_back(c);
            added_to_result[c] = true;
        }
        return result.substr(1);
    }
};
```
