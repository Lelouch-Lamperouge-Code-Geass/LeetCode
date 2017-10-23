Given a non-empty string, encode the string such that its encoded length is the shortest.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.

Note:

* k will be a positive integer and encoded string will not be empty or have extra space.
* You may assume that the input string contains only lowercase English letters. The string's length is at most 160.
* If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them is fine.

Example 1:

```
Input: "aaa"
Output: "aaa"
Explanation: There is no way to encode it such that it is 
shorter than the input string, so we do not encode it.
```

Example 2:

```
Input: "aaaaa"
Output: "5[a]"
Explanation: "5[a]" is shorter than "aaaaa" by 1 character.
```

Example 3:

```
Input: "aaaaaaaaaa"
Output: "10[a]"
Explanation: "a9[a]" or "9[a]a" are also valid solutions, 
both of them have the same length = 5, which is the same as "10[a]".
```

Example 4:

```
Input: "aabcaabcd"
Output: "2[aabc]d"
Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".
```

Example 5:

```
Input: "abbbabbbcabbbabbbc"
Output: "2[2[abbb]c]"
Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also 
be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".
```

# Solution

This is an optimization problem. An optimization problem is the problem of finding the best solution from all feasible solutions. There are two common methods to solve an optimizastion problem.

1. Dynamic programming
2. Greedy algorithm

However, a greedy algorithm does not guarantee an optimal solution unless you can prove it.

Dynamic programming (also known as dynamic optimization) is a method for solving a complex problem by breaking it down into a collection of simpler subproblems, solving each of those subproblems just once, and storing their solutions. The next time the same subproblem occurs, instead of recomputing its solution, one simply looks up the previously computed solution, thereby saving computation time at the expense of a (hopefully) modest expenditure in storage space. (Each of the subproblem solutions is indexed in some way, typically based on the values of its input parameters, so as to facilitate its lookup.) The technique of storing solutions to subproblems instead of recomputing them is called "memoization".



__Time Complexity = O(n^3)__.

```cpp
class Solution {
private:
    // If s is a multiple of patterns, then return that repeat pattern.
    // Return "aba" for s == "abaabaaba"
    std::string get_repeat_pattern(const std::string &s) {
        const std::size_t n = s.size();
        std::vector<std::size_t> kmp_vec(n, 0);
        std::size_t p(0), q(1);
        
        while(q < n) {
            if (s[p] == s[q]) {
                kmp_vec[q] = p + 1;
                ++ p, ++ q;
            } else {
                if (p != 0) {
                    p = kmp_vec[p-1];
                } else {
                    kmp_vec[q] = 0;
                    ++ q;
                }
            }
        }
        std::size_t patternLen = n - kmp_vec.back();
        if(patternLen != n && n % patternLen == 0) {
            return s.substr(0, patternLen);
        } else {
            return s;
        }
    }
public:
    string encode(string s) {
        const std::size_t n = s.size();
        if (n <= 4) return s;
        vector<vector<string>> min_encode(n, vector<string>(n,""));
        
        for (std::size_t len = 1; len <= n; ++len) {
            for (std::size_t i = 0; i + len <= n; ++i) {
                std::size_t j = i + len - 1;
                std::string substr = s.substr(i, len);
                min_encode[i][j] = substr;
                if (len >= 5) {
                     // If string length < 5, we know that encoding will not help.           
                    for (std::size_t k = i; k < j; ++k) {
                        if (min_encode[i][k].size() 
                            + min_encode[k+1][j].size() < min_encode[i][j].size()) {
                            min_encode[i][j] = min_encode[i][k] + min_encode[k+1][j];
                        }
                    }
                    
                    const std::string pattern(get_repeat_pattern(substr));
                    if (pattern.size() == substr.size()) continue; // no repeat pattern found
                    string patternEncode = std::to_string(substr.size() / pattern.size()) 
                        + "[" + min_encode[i][i + pattern.size() - 1] + "]";
                    if(patternEncode.size() < min_encode[i][j].size()) {
                         min_encode[i][j] = patternEncode;
                    }
                }
            }
        }
        return min_encode[0][n-1];
    }
};
```
