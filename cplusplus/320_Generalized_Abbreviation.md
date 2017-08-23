Write a function to generate the generalized abbreviations of a word.

Example:

Given word = “word”, return the following list (order does not matter):

[“word”, “1ord”, “w1rd”, “wo1d”, “wor1”, “2rd”, “w2d”, “wo2”, “1o1d”, “1or1”, “w1r1”, “1o2”, “2r1”, “3d”, “w3”, “4”]


# Solution

The idea is: for every character, we can keep it or abbreviate it. To keep it, we add it to the current solution and carry on backtracking. To abbreviate it, we omit it in the current solution, but increment the count, which indicates how many characters have we abbreviated. When we reach the end or need to put a character in the current solution, and count is bigger than zero, we add the number into the solution.

```cpp
class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        dfs(result, word, 0, 0, "");
        return result;
    }
    
    void dfs(vector<string>& result, string word, int pos, int count, string cur) {
        if(pos == word.size()) {
            if(count > 0)   cur += to_string(count);
            result.push_back(cur);
            return;
        }
        /** add the current word **/
        if(count > 0) {
            dfs(result, word, pos + 1, 0, cur + to_string(count) + word[pos]);
        } 
        else {
            dfs(result, word, pos + 1, 0, cur + word[pos]);
        }
        /** skip the current word **/
        dfs(result, word, pos + 1, count + 1, cur);
        
    }
};
```
