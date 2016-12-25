class Solution {
public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;
    string temp("");
    checkWithDfs(res,temp,n,n);
    return res;
  }
private:
  void checkWithDfs(vector<string> & res,string & temp,int left, int right){
    if (left==0 && right==0) {
      res.push_back(temp);
    } else {
      if (left>0) {
        temp.push_back('(');
        checkWithDfs(res,temp,left-1,right);
        temp.pop_back();
      }
      if (right>left) {
        temp.push_back(')');
        checkWithDfs(res,temp,left,right-1);
        temp.pop_back();
      }
    }
  }
};
