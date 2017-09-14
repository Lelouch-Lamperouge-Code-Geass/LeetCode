Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

# Pitfall

* What if needle is an empty string?

# Solution

* http://articles.leetcode.com/implement-strstr-to-find-substring-in

The brute force method is straightforward to implement. We scan the substring (the target) with the string from its first position and start matching all subsequent letters one by one. If one of the letter doesn’t match, we start over again with the next position in the string. Assume that N = length of string, M = length of substring, then the complexity is O(N*M).



### Solution one

```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
        const int M(haystack.size()),N(needle.size());
        for(int i=0;i<M-N+1;i++){
            int j(0);
            for( ;j<N;j++){
                if(haystack[i+j]!=needle[j]) break;
            }
            if(j==N) return i;
        }
        return -1;
    }
};
```

### Solution two

* http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/
* http://www.geeksforgeeks.org/searching-for-patterns-set-2-kmp-algorithm/

__Since the two portions of the algorithm have, respectively, complexities of O(k) and O(n), the complexity of the overall algorithm is O(n + k). Build KMP table is O(k), and search substring based on it is O(n). These complexities are the same, no matter how many repetitive patterns are in haystack or needle.__

KMP typically has an inner loop and an outer loop. The pattern string pointer or longest matching prefix variable j is initialized with 0 and it is incremented in the outer loop at most n times (the length of the text string) when ```haystack[i] == needle[j]```. The inner loop iteratively decreases j by some non-zero amount, but it stops at 0 and it never increases j. Hence the inner loop can only decrease j when the outer loop has previously incremented it which can happen at most n times.

You can think of the value of j as a resource that is produced by the outer loop i and consumed by the inner loop  until it is exhausted. The worst case thus takes 2n loop iterations (n increments and n decrements) and hence KMP runs in O(n) (if disregarding the construction of the prefix table which takes O(m) by a similar argument).

```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        const std::size_t n (haystack.size()), m(needle.size());
        if (n < m) return -1;
        const vector<std::size_t> &kmp_table = get_kmp_table(needle);
        std::size_t i(0), j(0);
        
        while (i < n) {
            if (haystack[i] == needle[j]) {
                ++ i;
                ++ j;
                if (j == m) return i - m;
            } else {
                if (j == 0) {
                    ++ i;
                } else {
                    j = kmp_table[j-1];
                }
            }
        }
        
        return -1;
    }
private:
    vector<std::size_t> get_kmp_table(const string &needle) {
        const std::size_t n(needle.size());
        vector<std::size_t> kmp_table(n, 0);
        
        std::size_t pre(0), pos(1);
        
        while (pos < n) {
            if (needle[pos] == needle[pre]) {
                kmp_table[pos] = pre + 1;
                ++ pos;
                ++ pre;
            } else {
                if (pre == 0) {
                    kmp_table[pos++] = 0;
                } else {
                    pre = kmp_table[pre - 1] ;
                }
            }
        }
        
        return kmp_table;
    }
};
```
