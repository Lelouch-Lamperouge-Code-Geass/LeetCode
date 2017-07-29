Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

For example:

```
Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".
```

# Solution

##### Solution 1

```cpp
class Solution {
public:
  string shortestPalindrome(string s) {
    string rev(s.rbegin(),s.rend());// get reverse string
    const int s_size(s.size());
    int len(s_size);// the minimum suffix length from the reverse string we need to add before s
    for (len=s_size;len>=0;--len) {
      if (s.substr(0,len) == rev.substr(s_size-len)) break;
    }
    return rev.substr(0,s_size-len)+s;
  }
};
```

##### Solution 2

```cpp
class Solution {
public:
  string shortestPalindrome(string s) {
    string rever(s.rbegin(),s.rend());
    string mirror = s + '#' + rever;
    vector<int> kmp = get_kmp(mirror);
    int len = kmp[mirror.size()-1];
    return rever.substr(0,s.size()-len) + s;
  }
private:
  vector<int> get_kmp(const string & s) {
    const int N(s.size());
    vector<int> res(N,0);
    int pos(1),len(0);
    while(pos<N){
      if(s[pos] == s[len]) {
        res[pos] = len + 1;
        ++ pos;
        ++ len;
      } else {
        if(len==0) {
          res[pos] = 0;
          ++ pos;
        } else {
          len = res[len-1];
        }
      }
    }
    return res;
  }
};
```

##### Solution 3 : optimize on solution 2 

```cpp
class Solution {
public:
  string shortestPalindrome(string s) {
    std::string rev_s(s.rbegin(),s.rend());
    std::string ss(s+'#'+rev_s);
    std::size_t len =  LongestCommonPrefixSuffixLength(ss);
    return rev_s.substr(0,s.size()-len) + s;
  }
private:
  std::size_t LongestCommonPrefixSuffixLength(const std::string & s) {
    const std::size_t s_size(s.size());
    vector<std::size_t> kmp_table(s_size,0);
    std::size_t len(0),index(1);
    while (index < s_size) {
      if (s[len] == s[index]) {
        kmp_table[index++] = ++len;
      } else {
        if (len!=0) {
          len = kmp_table[len-1];
        } else {
          kmp_table[index++] = 0;
        }
      }
    }
    return kmp_table[s_size-1];
  }
};
```
