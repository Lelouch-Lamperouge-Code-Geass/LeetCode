Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

For example,

```
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.
```    

##### Note:
    
You may assume both s and t have the same length.
    
# Solution

### Solution 1
    
The intuitive solution is to use two mapper<char, char>  to store the bi-directional relationship.
    
```cpp
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) return false;
        std::unordered_map<char, char> s_to_t, t_to_s;
        for (std::size_t i = 0, n = s.size(); i < n; ++i) {
            if (s_to_t.count(s[i]) != 0 || t_to_s.count(t[i]) != 0) {
                if (s_to_t[s[i]] != t[i] || t_to_s[t[i]] != s[i]) {
                    return false;
                }
            }
            // Add the bi-direction relationship
            s_to_t[s[i]] = t[i];
            t_to_s[t[i]] = s[i];
        }
        return true;
    }
};
```

### Solution 2

For each string, we use its indexes as the unique keys for each char. 
    
And if a char in s is mapped to a char in t, then these two chars should have the same key(index i).
    
We can use a vector here to improve performance.    

```cpp
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() !=t.size()) return false;
        vector<int> s_mapper(256,-1), t_mapper(256,-1);
        const int str_size(s.size());
        for (int i=0;i<str_size;++i) {
            if (s_mapper[s[i]] != t_mapper[t[i]]) return false;
            s_mapper[s[i]] = t_mapper[t[i]] = i;
        }
        return true;
    }
};
```
