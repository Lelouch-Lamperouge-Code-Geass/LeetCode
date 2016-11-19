
// Copyright (C) 2016 by 
class Solution {
public:
  vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
    unordered_map< string,vector<string> > mapper; // avoid duplicate calculation
    return helper(s,wordDict,mapper);
  }
private:
  vector<string> helper(const string & s,
                        const unordered_set<string> & wordDict,
                        unordered_map< string,vector<string> > & mapper) {
    if (mapper.find(s)!=mapper.end()) return mapper[s];
    vector<string> res;
    if (wordDict.find(s)!=wordDict.end()) res.push_back(s); //check itself at first
    const int n(s.size());
    for (int i=n-1;i>0;--i) {
      const string & to_end = s.substr(i);
      if (wordDict.find(to_end)!=wordDict.end()) {
        const vector<string> & left_part = helper(s.substr(0,i),wordDict,mapper);
        if (!left_part.empty()) {
          for (const string & left : left_part) {
            res.push_back(left+' '+to_end);
          }
        }
      }
    }
    mapper[s] = res;
    return res;
  }
};
