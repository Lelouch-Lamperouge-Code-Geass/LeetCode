/* 
Solution 1
 */
class Solution {
public:
  vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    vector<string> temp;
    CheckWithDfs(res,temp,s,0);
    return res;
  }
private:
  void CheckWithDfs(vector<vector<string>> & res,
                    vector<string> & temp,
                    const std::string & s,
                    int start) {
    const int s_size(s.size());
    if (start==s_size) {
      res.push_back(temp);
    } else {
      for (int end=start;end<s_size;++end) {
        if (IsPalindrome(s,start,end)) {
          temp.push_back(s.substr(start,end-start+1));
          CheckWithDfs(res,temp,s,end+1);
          temp.pop_back();
        }
      }
    }
  }
  bool IsPalindrome(const std::string & s, int start, int end) {
    while (start<end) {
      if (s[start++]!=s[end--])
        return false;
    }
    return true;
  }
};

/*
Solution 2 : optimized based on solution 1.
Using dynamic programming to check is_palindrom[start][end]
based on start+1,end-1.
*/
class Solution {
public:
  vector<vector<string>> partition(string s) {
    const int s_size(s.size());
    vector< vector<bool> > is_palin(s_size,vector<bool>(s_size,false));
    for (int start=s_size-1;start>=0;--start) {
      for (int end=start;end<s_size;++end) {
        if(s[start]==s[end] && (end-start<=1 || is_palin[start+1][end-1]) ) {
          is_palin[start][end] = true;
        }
      }
    }
    vector<vector<string>> res;
    vector<string> temp;
    CheckWithDfs(res,temp,s,0,is_palin);
    return res;
  }
private:
  void CheckWithDfs(vector<vector<string>> & res,
                    vector<string> & temp,
                    const std::string & s,
                    int start,
                    const vector< vector<bool> > & is_palin) {
    const int s_size(s.size());
    if (start==s_size) {
      res.push_back(temp);
    } else {
      for (int end=start;end<s_size;++end) {
        if (is_palin[start][end]) {
          temp.push_back(s.substr(start,end-start+1));
          CheckWithDfs(res,temp,s,end+1,is_palin);
          temp.pop_back();
        }
      }
    }
  }


};
