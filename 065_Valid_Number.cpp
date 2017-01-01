/*
This is one of the worst problems in leetcode.
Don't waste your time on this question, just get the general idea is fine.
This problem won't teach you anything about algorithm and space complexity.
"3.",".123" are considered as valid numbers there.
"12 3","3e6.5" are considered as invalid numbers. 
*/
class Solution {
public:
  bool isNumber(string s)
  {
    std::size_t i(0);

    // skip the whilespaces
    i = s.find_first_not_of(' ');
    if(i==s.size()) return false;


    // check the significand
    if(s[i] == '+' || s[i] == '-') ++i; // skip the sign if exist

    int n_nm, n_pt;
    for(n_nm=0, n_pt=0; (s[i]<='9' && s[i]>='0') || s[i]=='.'; ++i)
      s[i] == '.' ? ++ n_pt : ++ n_nm;
    if(n_pt>1 || n_nm<1) // no more than one point, at least one digit
      return false;

    // check the exponent if exist
    if(s[i] == 'e') {
      i++;
      if(s[i] == '+' || s[i] == '-') i++; // skip the sign

      int n_nm = 0;
      for(; s[i]>='0' && s[i]<='9'; i++, n_nm++) {}
      if(n_nm<1)
        return false;
    }

    // skip the trailing whitespaces
    for(; s[i] == ' '; i++) {}

    return s[i]==0;  // must reach the ending 0 of the string
  }
};
