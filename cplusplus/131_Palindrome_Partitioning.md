Given a string s, partition s such that every substring of the partition is a palindrome.  

Return all possible palindrome partitioning of s.  

For example, given s = "aab",  
Return  

```
[
  ["aa","b"],
  ["a","a","b"]
]
```

### Solution 1

```cpp
class Solution {
public:
  vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    vector<string> temp;
    CheckWithBacktracking(res,temp,s,0);
    return res;
  }
private:
  void CheckWithBacktracking(vector<vector<string>> & res,
                    vector<string> & temp,
                    const std::string & s,
                    int start) {
    const int s_size(s.size());
    if (start==s_size) {
      res.push_back(temp);
    } else {
      for (int end=start;end<s_size;++end) {
        if (IsPalindrome(s,start,end)) {
          temp.push_back(s.substr(start,end-start+1));
          CheckWithBacktracking(res,temp,s,end+1);
          temp.pop_back();
        }
      }
    }
  }
  bool IsPalindrome(const std::string & s, int start, int end) {
    while (start<end) {
      if (s[start++]!=s[end--])
        return false;
    }
    return true;
  }
};
```

We can optimize based on solution 1. Using dynamic programming to check is_palindrom[start][end] based on start+1,end-1.

```cpp
class Solution {
public:
  vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    const std::size_t s_size(s.size());
    vector< vector<bool> > is_palindrome(s_size,vector<bool>(s_size,false));
    for (std::size_t end=0;end<s_size;++end) {
      for (std::size_t start=end;start<s_size;--start) {
        if (start==end||s[start]==s[end]&&(end-start<=1||is_palindrome[start+1][end-1])) {
          is_palindrome[start][end] = true;
        }
      }
    }
    vector<string> temp;
    CheckWithBacktracking(res,temp,s,is_palindrome,0);
    return res;
  }
private:
  void CheckWithBacktracking(vector<vector<string>> & res,
                             vector<string> & temp,
                             const string & s,
                             const vector< vector<bool> > & is_palindrome,
                             std::size_t start) {
    const std::size_t s_size(s.size());
    if (start==s_size) {
      res.push_back(temp);
    } else {
      for (std::size_t end=start;end<s_size;++end) {
        if (is_palindrome[start][end]) {
          temp.push_back(s.substr(start,end-start+1));
          CheckWithBacktracking(res,temp,s,is_palindrome,end+1);
          temp.pop_back();
        }
      }
    }
  }
};
```

### Solution 2

```cpp
class Solution {
public:
  vector<vector<string>> partition(string s) {
    const std::size_t s_size(s.size());
    vector<vector<vector<string>>> res(s_size,vector<vector<string>>());
    vector< vector<bool> > is_palindrome(s_size,vector<bool>(s_size,false));
    for (std::size_t end=0;end<s_size;++end) {
      for (std::size_t start=end;start<s_size;--start) {
        if (start==end||s[start]==s[end]&&(end-start<=1||is_palindrome[start+1][end-1])) {
          is_palindrome[start][end] = true;
          string cur_str(s.substr(start,end-start+1));
          if (start==0) {
            res[end].push_back(vector<string>(1,cur_str));
          } else {
            if (!res[start-1].empty()) {
              for (const vector<string> & item : res[start-1]) {
                res[end].push_back(item);
                res[end].back().push_back(cur_str);
              }
            }
          }
        }
      }
    }
    return res[s.size()-1];
  }

};
```
