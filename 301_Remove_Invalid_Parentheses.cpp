class Solution {
public:
  vector<string> removeInvalidParentheses(string s) {
    std::vector<std::string> result;
    remove(s, result, 0, 0, std::make_pair('(',')'));
    return result;
  }
private:
  void remove(const string & s,vector<string> & result,int last_i,int last_j, const std::pair<char,char> & parens) {
    for (int stack=0, i = last_i;i<s.size(); ++i) {
      if (s[i]==parens.first) ++stack;
      if (s[i]==parens.second) --stack;
      if (stack>=0) continue;
      // stack<0, which means we have more ) than (
      for (int j=last_j;j<=i;++j) {
        if (s[j]==parens.second && (j==last_j||s[j-1]!=parens.second) ) {
          remove(s.substr(0,j)+s.substr(j+1), result,i,j,parens);
        }
      }
      return;
    }
    std::string rs(s);
    std::reverse(rs.begin(),rs.end());

    if (parens.first=='(') {
      remove(rs, result, 0, 0, std::make_pair(')','('));
    } else {
      result.push_back(rs);
    }
  }
};
