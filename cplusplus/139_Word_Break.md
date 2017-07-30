Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words. You may assume the dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".
 
# Solution
 
##### Solution one : Time Limit Exceede

The most intuitive solution is use backtracking.
  
```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        std::unordered_set<std::string> word_set(wordDict.begin(), wordDict.end());
        return backtracking(s, 0, word_set);
    } 
private:
    bool backtracking(const std::string &s, std::size_t position, std::unordered_set<std::string> &word_set) {
        if (position == s.size()) {
            return true;
        } else {
            for (std::size_t len = s.size() - position; len > 0; --len) {
                if (word_set.count(s.substr(position, len)) > 0
                   && backtracking(s, position + len, word_set)) {
                    return true;
                }
            }
            return false;
        }
    }
};
```
  

##### Solution two

```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        std::unordered_set<std::string> word_set(wordDict.begin(), wordDict.end());
        std::vector<bool> is_breakable(s.size() + 1, false);
        is_breakable[0] = true;
        
        for (std::size_t end = 1, s_size = s.size(); end <= s_size; ++ end) {
            for (std::size_t start = 0; start < end; ++ start) {
                if (is_breakable[start] && word_set.count(s.substr(start, end - start)) > 0) {
                    is_breakable[end] = true;
                    break; // already breakable
                }
            }
        }
        
        return is_breakable[s.size()];
    } 

};
```


