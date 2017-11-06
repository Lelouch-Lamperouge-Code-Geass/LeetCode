Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.

The input string does not contain leading or trailing spaces and the words are always separated by a single space.

```
For example,
Given s = "the sky is blue",
return "blue is sky the".
```

Could you do it in-place without allocating extra space?

Related problem: [Rotate Array](https://leetcode.com/problems/rotate-array/description/)

Update (2017-10-16):

We have updated the function signature to accept a character array, so please reset to the default code definition by clicking on the reload button above the code editor. Also, Run Code is now available!

# Solution

```cpp
class Solution {
public:
    void reverseWords(vector<char>& str) {
        // Reverse the whole sentence
        std::reverse(str.begin(), str.end());
        
        // Reverse each word
        vector<char>::iterator pos(str.begin()), END(str.end());
        while (pos != END) {
            vector<char>::iterator empty_space = std::find(pos, str.end(), ' ');
            if (empty_space == END) {
                // Reverse last work and jump out of loop
                std::reverse(pos, empty_space);
                break;
            } else {
                std::reverse(pos, empty_space);
                pos = ++empty_space;
            }
        }
    }
};
```
