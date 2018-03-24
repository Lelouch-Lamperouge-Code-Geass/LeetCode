Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

# Pitfall

* What if needle is an empty string?

# Solution

* http://articles.leetcode.com/implement-strstr-to-find-substring-in

The brute force method is straightforward to implement. We scan the substring (the target) with the string from its first position and start matching all subsequent letters one by one. If one of the letter doesn’t match, we start over again with the next position in the string. Assume that N = length of string, M = length of substring, then the complexity is O(N*M).



### Solution one : A naive solution

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

### Solution two : KMP algorithm

* http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/
* http://www.geeksforgeeks.org/searching-for-patterns-set-2-kmp-algorithm/
* http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/

Firstly, let me share my understanding of KMP algorithm.  
The key of KMP is to build a look up table that records the match result of __proper prefix__ and __preper postfix__.

* __Proper prefix__: All the characters in a string, with one or more cut off the end. “S”, “Sn”, “Sna”, and “Snap” are all the proper prefixes of “Snape”.
* __Proper suffix__: All the characters in a string, with one or more cut off the beginning. “agrid”, “grid”, “rid”, “id”, and “d” are all proper suffixes of “Hagrid”.

_String can be prefix and suffix of itself, but it is not a proper prefix and proper suffix._

Value in the table means the max len of matching substring that exists in both proper prefix and proper postfix.  
In the proper prefix this substring should starts from 0, while in the proper postfix this substring should ends at current index.  

For example, now we have a string "ababc"  
The KMP table will look like this:  

```
a b a b c

0 0 1 2 0
```

(Note: we will not match substring with itself, so we will skip index 0)

__So how does this table help us search string match faster? Well, the answer is if we are trying to match a char after proper postfix with target string and failed, then we can smartly shift the string, so that the matching string in proper prefix will replace proper postfix and now we can try to match the char after proper prefix with this char in target.__

Take above string as an example.

Now we try to match string "ababc" with "abababc".

We will initially have match as below

```
a b a b a b c (string x)

a b a b c (string y)

0 1 2 3 4 5 6
```

We found char at index 4 does not match, then we can use lookup table and shift the string y wisely.
We found table[3] = 2, which means we can shift the string y rightward by 2, and still have same but shorter prefix before index 4, like this:

```
a b a b a b c (string x)
___a b a b c (string y)

0 1 2 3 4 5 6
```

If there is a long gap between prefix and postfix, this shift can help us save a lot of time.
In the brute force way, we cannot do that because we have no information of the string. We have to compare each possible pair of chars. While in kmp, we know the information of string y so we can move smartly. We can directly jump to the next possible matching pair while discard useless pair of chars.

We are almost done with KMP, but we still have one special case that needs to be taken care of.

Say now we have a input like this:

```
a a b a a a (input String)
0 1 2 3 4 5 (index)
0 1 0 1 2 ? (KMP table)
```

How should we build the KMP table for this string?

Say the pointer in prefix is "x", which is at index 2 now and the pointer in postfix is "y" which is at index 5 now. we need to match "b" pointed by x with "a" pointed by y. It is an unmatched pair, how should we update the cell?

Well, we really don't need to reset it to 0, that will make us skip a valid shorter matching substring "aa".
What we do now is just to shorten the length of substring by 1 unit and try to match a shorter substring "aa". This can be done by moving pointer x to the index recorded in [indexOf(x)-1] while keep pointer y stay still. This is because by following the value in KMP table we can always make sure previous part of prefix and postfix is matched even we have shorten their length, so we only need to care about the char after matched part in prefix and postfix.

Use above example:

Firstly we try to compare prefix "aab" with postfix "aaa", pointer in prefix now points to "b" while pointer in postfix now points to "a". So this means current len of postfix/prefix will not give a match, we need to shorten it.

So in the second step, we will fix pointer in postfix, and move pointer in prefix so that we can compare shorter prefix and postfix. The movement of pointer in prefix (say at index x) is done by using KMP table. We will set pointer in prefix to be table [indexOf(x)-1]. In this case, we will move prefix pointer to index 1. So now we try to compare prefix "aa" with postfix "aa".

Finally, we found the matching prefix and postfix, we just update the cell accordingly.

Above is my understanding of KMP algorithm, so how could we apply KMP to this problem

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
