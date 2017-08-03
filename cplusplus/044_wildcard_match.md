Implement wildcard pattern matching with support for '?' and '*'.
 
```
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") ? false
isMatch("aa","aa") ? true
isMatch("aaa","aa") ? false
isMatch("aa", "*") ? true
isMatch("aa", "a*") ? true
isMatch("ab", "?*") ? true
isMatch("aab", "c*a*b") ? false
```

# Solution

### Solution 1 with dynamic programming :
Let's briefly summarize the idea of DP. We define the state P[i][j] to be whether s[0..i) matches p[0..j). The state equations are as follows:
    
```
P[i][j] = P[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '?'), if p[j - 1] != '*';
P[i][j] = P[i][j - 1] || P[i - 1][j], if p[j - 1] == '*'.
```

__Time complexity : O(s.size() * p.size()), Splace Complexity O(s.size() * p.size())__

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        const int s_size(s.size()), p_size(p.size());
        vector< vector<bool> > is_match(s_size+1, vector<bool>(p_size+1,false) );
        is_match[0][0] = true;
        for (int i=1;i<=p_size && p[i-1]=='*' ;++i) is_match[0][i] = true;
        
        for (int i=1;i<=s_size;++i) {
            for (int j=1;j<=p_size;++j) {
                if (p[j-1]!='*') {
                    is_match[i][j] = is_match[i-1][j-1] && (p[j-1]=='?' || s[i-1]==p[j-1]);
                } else {
                  is_match[i][j] = is_match[i][j-1] // * is not used
                    || is_match[i-1][j] ; // * is used to match current char
                }
            }
        }
        return is_match[s_size][p_size];
    }
};
```

We optimize the DP code to O(m) space by recording P[i - 1][j - 1] using a single variable pre.

__Time complexity : O(s.size() * p.size()), Splace Complexity O(p.size())__
```cpp
class Solution {
public:
  bool isMatch(string s, string p) {
    const std::size_t str_size(s.size()), pattern_size(p.size());
    vector<bool> is_match(pattern_size+1,false);
    is_match[0] = true;
    for (std::size_t i = 1;i<=pattern_size && p[i-1]=='*';++i) is_match[i] = true;

    for (std::size_t i=1;i<=str_size;++i) {
      bool pre = is_match[0]; // use the value before update
      is_match[0] = is_match[0] && p[i-1]=='*'; // actually is_match[0] will only be true on first row
      for (std::size_t j=1;j<=pattern_size;++j) {
        bool temp = is_match[j]; // record the value before update
        if (p[j-1]!='*') {
          is_match[j] = pre && (s[i-1]==p[j-1] || p[j-1]=='?');
        } else {
          is_match[j] = is_match[j-1] || is_match[j];
        }
        pre = temp;
      }
    }
    return is_match[pattern_size];
  }
};
```

### Solution two

__Time complexity : O(s.size() * p.size()), Splace Complexity O(1)__

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        int si(0), pi(0),s_size(s.size()), p_size(p.size());
        int p_mark(-1),s_mark(-1);
        while (si<s_size) { // can't check pi<p_size here, think about "abc","*"
            if (p[pi]=='*') {
                // mark the index of wildcard and corresponding index in s
                p_mark = pi;
                s_mark = si;
                
                ++ pi; // * match 0 char at first shot
            } else {
                if (p[pi]=='?' || p[pi]==s[si]) {
                    ++ pi;
                    ++ si;
                } else {
                    if (p_mark!=-1) {
                        pi = p_mark + 1; //p_mark always point to wildcard index in p
                        si = s_mark+1; 
                        
                        ++ s_mark; // use '*' to match one char in s 
                    } else {
                        return false;
                    }    
                }
            }
        }
        
        while (pi<p_size && p[pi]=='*') ++pi; // p may have trailing *
        
        return si == s_size && pi == p_size;
    }
};
```
