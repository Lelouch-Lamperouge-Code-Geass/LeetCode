Given an input string, reverse the string word by word.

For example,

```
Given s = "the sky is blue",
return "blue is sky the".
```  

__Update (2015-02-12):__

For C programmers: Try to solve it in-place in O(1) space.
 
# Solution

The idea is,  we reverse the whole string first and then reverse each word one by one.
  
```cpp
class Solution {
public:
  void reverseWords(string &s) {
    std::reverse(s.begin(),s.end());
    const std::size_t n (s.size());
    std::size_t index(0);
    for (std::size_t i=0;i<n;++i) {
      if (s[i]!=' ') {
        if (index!=0) s[index++] = ' ';
        std::size_t j = i;
        while (j<n && s[j]!=' ') s[index++] = s[j++];
        std::reverse( s.begin()+index-(j-i) , s.begin()+index );
        i = j;
      }
    }
    s.erase(s.begin()+index,s.end());

  }
};
```
