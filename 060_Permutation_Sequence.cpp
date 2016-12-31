/*
index: 0 1 2 3 
factorial : 1 1 2 6
chars : '1' '2' '3' '4'
*/
class Solution {
public:
  string getPermutation(int n, int k) {
    std::string reval("");
    vector<int> factorial(n,1);
    vector<char> chars(n,'1');
    for (int i=1;i<n;++i) {
      factorial[i] = factorial[i-1] * i;
      chars[i] = '1' + i;
    }

    -- k ;
    while (n) {
      int i = k / factorial[n-1];
      reval.push_back(chars[i]);
      chars.erase(chars.begin()+i);

      k %= factorial[n-1];
      -- n;
    }
    return reval;
  }
};
