/* Solution 1*/
class Solution {
public:
  bool wordBreak(string s, unordered_set<string>& wordDict) {
    const std::size_t s_size(s.size());
    // can_break recordes substring [0-i] can be break or not
    // you can use length instead of index here if you want
    std::vector<bool> can_break(s_size,0);
    for (std::size_t i=0;i<s_size;++i) {
      if (can_break[i]) {
        continue;
      } else {
        if (wordDict.count(s.substr(0,i+1)) != 0) {
          can_break[i] = true;
        } else {
          for (std::size_t j=0;j<i;++j) {
            if (can_break[j] && wordDict.count(s.substr(j+1,i-j))!=0 ) {
              can_break[i] = true;
              break;
            }
          }
        }
      }
    }
    return can_break[s_size-1];
  }
};

/* Solution 2 */
class Solution {
public:
  bool wordBreak(string s, unordered_set<string>& wordDict) {
    const std::size_t s_size(s.size());
    // Here can_break means whether substring with length X can be broke or not
    std::vector<bool> can_break(s_size+1,false);
    can_break[0] = true;
    for(std::size_t len=1;len<=s_size;++len){
      for(std::size_t start=len-1;start>=0&&start<len;--start){
        // notice that size_t is non-negative type, so when start=0 and we try to subtract one
        // from it, it will overflow. Therefore, we add start<len to double check
        if( can_break[start] && wordDict.find( s.substr(start,len-start) ) != wordDict.end()){
          can_break[len] = true;
          break;
        }
      }
    }
    return can_break[s_size];
  }
};
