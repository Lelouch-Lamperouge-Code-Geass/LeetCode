class Solution {
public:
  vector<int> diffWaysToCompute(string input) {
    vector<int> res;
    for(int i=0;i<input.size();++i){
      if( std::ispunct(input[i]) ) {
        // get results from left and right part
        vector<int> lvalues = diffWaysToCompute(input.substr(0,i));
        vector<int> rvalues = diffWaysToCompute(input.substr(i+1));
        // calculation
        const char op = input[i];
        for (int l : lvalues) {
          for (int r : rvalues) {
            if (op == '+') {
              res.push_back(l+r);
            }  else if ( op =='-') {
              res.push_back(l-r);
            } else {
              res.push_back(l*r);
            }
          }
        }
      }
    }
    // if res is empty so far, then it means this string is a number.
    return res.empty() ? vector<int>(1,std::stoi(input)) : res;
  }
};
