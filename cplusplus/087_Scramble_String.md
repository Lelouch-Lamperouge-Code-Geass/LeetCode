Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

```
   great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
```

To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".
  
```
  rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
```

We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".
  
```
 rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
```

We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
  
# Solution
  
Originally, I thought just count the char of both string, and if the count number are the same for all the characters then it should be a scramble string pair.
  
But this is a wrong because it treats the problem as if it is a permutation problem.
  
For example, "abcd" "bdac" are not scramble string.
  
No matter how to rotate "abcd", the answer we could get are: 

```
abcd, bacd, abdc, badc, cdab, dcab, dcba, cdba  
```

There is no way we can for "bdac".
  
Why? In the question, binary tree is built "by partitioning it to two non-empty substrings recursively".
This means, after first partion, "abcd" will be cut into two halves, and all the following rotations are limited by these two halves.
We can only get ["a", "bcd"], ["ab", "cd"], ["abc", "d"]

And in order to have "bdac", our first cut will need to be : ["bd", "ac"] or ["b", "dac"] .
  
```cpp
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1 == s2) return true;
        if (s1.size() != s2.size()) return false;
        
        vector<int> counter(256, 0);
        
        const std::size_t n = s1.size();
        for (std::size_t i = 0;i < n; ++i) {
            ++ counter[s1[i]];
            -- counter[s2[i]];
        }
        
        for (int val : counter) {
            if (val != 0) return false;
        }
        
        for (std::size_t i = 1;i < n; ++i) { 
            if (isScramble(s1.substr(0, i), s2.substr(0, i)) 
                && isScramble(s1.substr(i), s2.substr(i))) {
                return true;
            }
            if (isScramble(s1.substr(0, i), s2.substr(n - i)) 
                && isScramble(s1.substr(i), s2.substr(0, n - i))) {
                return true;
            }
        }
        
        return false;
    }
};
```
  
A different style.

```cpp
class Solution {
public:
  bool isScramble(string s1, string s2) {
    // Make sure their length are the same
    const int s1_size(s1.size()), s2_size(s2.size());
    if(s1_size!=s2_size) return false;
    // If they are the same
    if (s1==s2) return true;
    
    // Not the same, let's make sure each char count are the same
    vector<int> counter(256,0);
    for (int i=0;i<s1_size;++i) {
      ++ counter[s1[i]];
      -- counter[s2[i]];
    }
    vector<int>::const_iterator non_zero = std::find_if_not(counter.begin(),counter.end(),
                                                            [](int x){return x!=0});
    if (non_zero!=counter.end()) return false;

    for (int i=1;i<s1_size;++i) {
      if ( isScramble(s1.substr(0,i),s2.substr(0,i) 
                      && isScramble(s1.substr(i),s2.substr(i)) )
           || isScramble(s1.substr(0,i),s2.substr(s1_size-i) 
                         && isScramble(s1.substr(i),s2.substr(0,s1_size-i)))
           ) return true;
    }
    return false;
  }
};
```
