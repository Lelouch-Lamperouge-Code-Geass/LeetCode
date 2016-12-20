/* Solution 1 */
class Solution {
public:
  vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
    unordered_map<string,vector<string>> res;
    const vector<string> &  reval = wordBreakWithDp(res,s,wordDict);
    return reval;
  }
private:
  vector<string> wordBreakWithDp(unordered_map<string,vector<string>> & res,
                                 const std::string & s,
                                 unordered_set<string>& wordDict) {
    if (res.count(s)!=0) return res[s];  //take from memory
    const std::size_t s_size(s.size());
    vector<string> cur_res;
    if(wordDict.count(s)!=0) cur_res.push_back(s);//whole string is a word
    for (std::size_t i=1;i<s_size;++i) {
      const std::string right(s.substr(i));
      if (wordDict.count(right)!=0) {
        const vector<string> & left = wordBreakWithDp(res,s.substr(0,i),wordDict);
        for (const std::string & l : left) {
          cur_res.push_back(l+' '+right);
        }
      }
    }
    res[s] = cur_res;// it could be empty
    return cur_res;
  }
};

///// Think about why below will have duplicates
// "catsanddog"
// ["cat","cats","and","sand","dog"]
vector<string> wordBreakWithDp(unordered_map<string,vector<string>> & res,
                               const std::string & s,
                               unordered_set<string>& wordDict) {
  if (res.count(s)!=0) return res[s];
  const std::size_t s_size(s.size());
  vector<string> cur_res;
  if(wordDict.count(s)!=0) cur_res.push_back(s);
  for (std::size_t i=1;i<s_size;++i) {
    const vector<string> & left =  wordBreakWithDp(res,s.substr(0,i),wordDict);
    const vector<string> & right =  wordBreakWithDp(res,s.substr(i),wordDict);
    if (!left.empty() && !right.empty()) {
      for (const std::string & l : left) {
        for (const std::string & r : right) {
          cur_res.push_back(l+' '+r);
        }
      }
    }
  }
  res[s] = cur_res;// it could be empty
  return cur_res;
}

