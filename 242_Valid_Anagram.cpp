class Solution {
public:
  bool isAnagram(string s, string t) {
    if (s.size()!=t.size()) return false;
    vector<int> count(256,0);
    const int str_size(s.size());
    for (int i=0;i<str_size;++i) {
      ++ count[s[i]];
      -- count[t[i]];
    }

    for (int i=0;i<256;++i) {
      if (count[i]!=0) return false;
    }
    return true;
  }
};
