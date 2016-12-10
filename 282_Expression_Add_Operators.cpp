class Solution {
public:
  vector<string> addOperators(string num, int target) {
    vector<string> result;
    if(num.empty()) return result;
    string temp("");
    backtracking(result,temp,num,0,target,0,0);
    return result;
  }
private:
  void backtracking(vector<string> & result,
                    const string & temp,
                    const string & num,
                    const int start,
                    const int target,
                    const long val,
                    const long pre){
    if(start==num.size() ){
      if(val == target) result.push_back(temp);
    } else {
      const int num_size(num.size());
      for (int i=start;i<num_size;++i) {
        if (num[start]=='0' && i>start) break; // taking care of "03"
        const string & x_str = num.substr(start,i-start+1);
        long x = std::stol(x_str);
        if (start==0) { // first number
          backtracking(result,x_str,num,i+1,target,x,x);
        } else {
          backtracking(result,temp+"+"+x_str,num,i+1,target,val+x,x);
          backtracking(result,temp+"-"+x_str,num,i+1,target,val-x,-x);
          backtracking(result,temp+"*"+x_str,num,i+1,target,val-pre+pre*x,pre*x);
        }
      }
    }
  }
};
