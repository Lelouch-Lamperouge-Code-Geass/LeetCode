/***
Solution one
 ***/
class Solution {
public:
  bool isSubsequence(string s, string t) {
    const std::size_t s_size(s.size()) , t_size(t.size());
    std::size_t i(0), j(0);
    while (i<s_size && j<t_size) {
      if (s[i] == t[j]) {
        ++ i;
        ++ j;
      } else {
        ++ j;
      }
    }
    return i == s_size;
  }
};

/***
 Follow up : If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, 
 and you want to check one by one to see if T has its subsequence. 
 In this scenario, how would you change your code? 
***/

class Solution {
public:

  bool isSubsequence(string s, string t) {
    std::unordered_map<char, std::vector<int> > char_indices;
    for (std::size_t i = 0; i < t.size(); ++i) {
      char_indices[t[i]].push_back(i);
    }

    std::size_t begin(0);
    for (char c : s) {
      if (char_indices.count(c) == 0)  return false; // t doesn't contain char c !
      const std::vector<int> & indices = char_indices[c];
      auto iter = std::lower_bound(indices.begin(), indices.end(), begin);
      if (iter == indices.end() ) return false;
      begin = (*iter) + 1;
    }
    return true;
  }
};
