/*
Solution 1 : use HashMap to count the appearances of string.
Only push string when it's count==2, which means appear more than once.
*/
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

/*
We can improve our memory cost based on solution 1.
Instead of store string as the key, we can store integer to
represent one string.
*/
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

