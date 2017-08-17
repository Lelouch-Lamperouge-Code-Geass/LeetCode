Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

# Solution

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

__Time complexity of KMP algorithm is O(n) in worst case.__

* http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/
* http://www.geeksforgeeks.org/searching-for-patterns-set-2-kmp-algorithm/

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
