Given an arbitrary ransom note string and another string containing letters from all the magazines, write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

Note:
You may assume that both strings contain only lowercase letters.

```
canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true
```

# Solution

```cpp
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> counter(256, 0);
        
        for (char c : magazine) {
            ++ counter[c];
        }
        
        for (char c : ransomNote) {
            if (counter[c] == 0) return false;
            -- counter[c];
        }
        
        return true;
    }
};
```
