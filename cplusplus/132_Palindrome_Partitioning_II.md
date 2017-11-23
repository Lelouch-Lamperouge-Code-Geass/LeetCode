Given a string s, partition s such that every substring of the partition is a palindrome.  

Return the minimum cuts needed for a palindrome partitioning of s.  

For example, given s = "aab",  

Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.


# Solution

### Solution 1

__O(n^2) time and O(n) space.__

```cpp
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<int> cut(n+1, n);  // number of cuts for the first k characters
        for (int i = 0; i <= n; i++) cut[i] = i-1;
        for (int i = 0; i < n; i++) {
            // odd length palindrome
            for (int j = 0; i-j >= 0 && i+j < n && s[i-j]==s[i+j] ; ++j) {
                cut[i+j+1] = min(cut[i+j+1],1+cut[i-j]);
            }
            
            // even length palindrome
            for (int j = 1; i-j+1 >= 0 && i+j < n && s[i-j+1] == s[i+j]; j++) {
                cut[i+j+1] = min(cut[i+j+1],1+cut[i-j+1]);
            }
        }
        return cut[n];
    }
};
```

a different style.

```cpp
class Solution {
public:
    int minCut(string s) {
     const int n( s.size() );
      vector<int> cut(n+1,n);
      for (int i = 0; i <= n; i++) cut[i] = i-1;
      for (int i=0;i<=n;++i) {
        // odd length palindrome, left and right here represents index
        for (int left=i,right=i;left>=0 && right<n && s[left] == s[right]; --left,++right) {
          cut[right+1] = std::min( cut[right+1], 1 + cut[left] );
        }
        // even length palindrome, left and right here represents index
        for (int left=i,right=i+1;left>=0 && right<n && s[left] == s[right]; --left,++right) {
          cut[right+1] = std::min( cut[right+1], 1 + cut[left] );
        }
      }
      return cut[n];
    }
};
```

### Solution 2

__O(n^2) time and O(n^2) space.__

```cpp
class Solution {
public:
    int minCut(string s) {
        const int n(s.size());
        
        // is_palindrome[i][j] represents s[i-j] can be a palindrome or not.
        // i, j here represents index
        vector<vector<bool>> is_palindrome(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i) is_palindrome[i][i] = true;
        
        for (int end = 1; end < n; ++end) {
            for (int start = end - 1; start >= 0; --start) {
                if (!is_palindrome[start][end]) {
                    if (start == end - 1) {
                        if(s[start] == s[end]) is_palindrome[start][end] = true;
                    } else {
                        is_palindrome[start][end] = (s[start] == s[end]) && (is_palindrome[start + 1][end - 1]);
                    }
                }
            }
        }
        
        vector<int> min_cut(n + 1, 0);
        // i, j here represents length. 
        // For a string length is i, it can be partitioned to [0, j], [j + 1, i]
        for (int i = 1; i <= n;  ++i) {
            min_cut[i] = i - 1;
            for (int j = i - 1; j >= 0; --j) {
                if (is_palindrome[j][i - 1]) {
                    if (j == 0) {
                      min_cut[i] = 0;
                    } else {
                      min_cut[i] = std::min(min_cut[i], min_cut[j] + 1);
                    }
                }
            }
        }
        
        return min_cut.back();
    }
};
```
