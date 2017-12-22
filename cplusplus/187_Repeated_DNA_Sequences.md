All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

```
Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].
```  


### Solution 1 

Use HashMap to count the appearances of string.

Only push string when it's count == 2, which means appear more than once.
  
```cpp
class Solution {
public:
  vector<string> findRepeatedDnaSequences(string s) {
    vector<string> res;
    const std::size_t s_size(s.size());
    unordered_map<string,int> counter;
    for (std::size_t i=0;i+10<=s_size;++i) {
      const std::string cur_str(s.substr(i,10));
      ++ counter[cur_str];
      if (counter[cur_str]==2) {
        // Only push to result when count==2
        res.push_back(cur_str);
      }
    }
    return res;
  }
};
```

### Solution 2

We can improve our memory cost based on solution 1. Instead of store string as the key, we can store a hash to represent one string.

The key point is that it is not doing hash, it is doing the exact coding of a 10-letter sequence into a 4-bytes number, which is simply not possible for any generic string, but is possible for strings in this problem because they can have only 4 differfent characters.

In more detail:

If two objects have same hash it means that they may or may not be equal (though two equal objects are required to have same hash). So hashing is not enough here (like calling just "AACCCCCGGG".hashCode() and storing it in the map), because there can be another (different) string with same hash and the program will output wrong result.

We also cannot store the 10-letter substrings themselves because they consume too much memory and the program will exceed memory limit.

So, instead of hashing or storing strings themselves the solution converts 10 letter string into 4-bytes integer (which is much smaller than string in terms of consumed memory). This would not be possible if the string could contain all 26 letters of English alphabet for example. But it is possible for our case, because there can be only 'A', 'C', 'G' and 'T' letters.

So we have only 4 possible letters, and we can use as little bits as possible to store each character of our 10-letter string. We really need only 2 bits (bits, not bytes) for this. Specifically the solution uses the following coding:

```
0 = 00 (bits in binary number system) = 'A'

1 = 01 (bits in binary number system) = 'C'

2 = 11 (bits in binary number system) = 'G'

3 = 10 (bits in binary number system) = 'T'
```

Note that since there 10 letters and each letter requires only 2 bits, we will need only 10 * 2= 20 bits to code the string (which is less then size of integer in C++ (as well as in all othere popular languages), which is 4 bytes = 32 bits).

Below solution, I use grey code, but you can use anything as long as it can provides 4 different values.
  
```cpp
class Solution {
public:
  vector<string> findRepeatedDnaSequences(string s) {
    vector<string> res;
    unordered_map<int,int> counter;
    const std::size_t s_size(s.size());
    int hash(0);
    for (std::size_t i=0;i<=8;++i) {
      hash = hash << 2  | GetCode(s[i]);
    }
    for (std::size_t i=9;i<s_size;++i) {
      hash = (hash<<2) & 0x000FFFFF | GetCode(s[i]);
      ++ counter[hash];
      if (counter[hash]==2) res.push_back(s.substr(i-9,10));
    }
    return res;
  }
private:
  // I use grey code here
  int GetCode(const char c) {
    if (c=='A') return 0;
    if (c=='C') return 1;
    if (c=='G') return 3;
    if (c=='T') return 2;
    return -1;
  }
};
```

# Knowledge

### Rolling hash

A __rolling hash__ (also known as recursive hashing or rolling checksum) is a hash function where the input is hashed in a window that moves through the input.
  
A few hash functions allow a rolling hash to be computed very quickly—the new hash value is rapidly calculated given only the old hash value, the old value removed from the window, and the new value added to the window—similar to the way a moving average function can be computed much more quickly than other low-pass filters.

One of the main applications is the __Rabin–Karp__ string search algorithm. Another popular application is the rsync program, which uses a checksum based on Mark Adler's adler-32 as its rolling hash. Low Bandwidth Network Filesystem (LBFS) uses a Rabin fingerprint as its rolling hash.
  
  
