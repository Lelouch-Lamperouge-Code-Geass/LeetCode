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

We can use backtracking algorithm to solve this problem.

> __Backtracking__ is a general algorithm for _finding all (or some) solutions_ to some computational problems, _notably constraint satisfaction problems_, that incrementally builds candidates to the solutions, and abandons each partial candidate ("backtracks") as soon as it determines that the candidate cannot possibly be completed to a valid solution.

This problem is asking for "finding all (or some) solutions", and it is also "constraint satisfaction problems" because all the substrings of the partition are required to be palindrome.

> Backtracking can be applied only for problems which admit the concept of a _"partial candidate solution"_ and a relatively quick test of whether it can possibly be completed to a valid solution. It is useless, for example, for locating a given value in an unordered table. When it is applicable, however, backtracking is often much faster than brute force enumeration of all complete candidates, since it can eliminate a large number of candidates with a single test.


__Time complexity: O(n\*(2^n))__.
For a string with length n, there will be (n - 1) intervals between chars.
For every interval, we can cut it or not cut it, so there will be 2^(n - 1) ways to partition the string.
For every partition way, we need to check if it is palindrome, which is O(n).
So the time complexity is O(n\*(2^n)).

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

The normal dfs backtracking will need to check each substring for palindrome, but a dp array can be used to record the possible break for palindrome before we start recursion.

First, I ask myself that how to check if a string is palindrome or not, usually a two point solution scanning from front and back. Here if you want to get all the possible palindrome partition, first a nested for loop to get every possible partitions for a string, then a scanning for all the partitions. That's a O(n^2) for partition and O(n^2) for the scanning of string, totaling at O(n^4) just for the partition. However, if we use a 2d array to keep track of any string we have scanned so far, with an addition pair, we can determine whether it's palindrome or not by justing looking at that pair, which is this line if(s.charAt(i) == s.charAt(j) && (i - j <= 2 || dp[j+1][i-1])). This way, the 2d array dp contains the possible palindrome partition among all.

Second, based on the prescanned palindrome partitions saved in dp array, a simple backtrack does the job.


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

Here the ```is_palindrome``` is to mark a range for the substring is a palindrome. if is_palindrome[i][j] is true, that means sub string from i to j is palindrome.

The ```res[i]```, is to store from beginng until current index i (Non inclusive), all possible partitions. From the past result we can determine current result.

__Time complexity O(n^2).__

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
