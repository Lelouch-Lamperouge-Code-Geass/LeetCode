Write a function to generate the generalized abbreviations of a word.

Example:

Given word = “word”, return the following list (order does not matter):

[“word”, “1ord”, “w1rd”, “wo1d”, “wor1”, “2rd”, “w2d”, “wo2”, “1o1d”, “1or1”, “w1r1”, “1o2”, “2r1”, “3d”, “w3”, “4”]


# Solution

The idea is: for every character, we can keep it or abbreviate it. To keep it, we add it to the current solution and carry on backtracking. To abbreviate it, we omit it in the current solution, but increment the count, which indicates how many characters have we abbreviated. When we reach the end or need to put a character in the current solution, and count is bigger than zero, we add the number into the solution.

#### Pitfall

1. In the end, make sure to add the last count if it is not 0.
2. When add previous count and current character, need to check whether previous count is 0 or not.

```cpp
class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> reval;
        std::string temp("");
        helper(reval, temp, word, 0, 0);
        return reval;
    }
private:
    void helper(std::vector<std::string> &reval,
                const std::string &temp,
                const std::string &word,
                const std::size_t pos,
                const std::size_t count
                ) {
        if (pos == word.size()) {
            std::string item = ( count != 0 ? temp + std::to_string(count) : temp);
            reval.emplace_back(item);
        } else {
            // Just increase count
            helper(reval, temp, word, pos + 1, count + 1);
            
         
            // Add the count and current char. Then reset count
            helper(reval, temp + (count > 0 ? std::to_string(count) : "") + word[pos], word, pos + 1, 0);
            
        }
    }
};
```
