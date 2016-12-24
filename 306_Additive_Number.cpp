class Solution {
public:
  bool isAdditiveNumber(string num) {
    const std::size_t num_size(num.size());
    for (std::size_t len1=1;len1<num_size;++len1) {
      for (std::size_t len2=1;len2<=(num_size-len1)/2;++len2) {
        if ( Check(num.substr(0,len1),num.substr(len1,len2),num.substr(len1+len2)) )
          return true;
      }
    }
    return false;
  }
private:
  bool Check(const string & num1, const string & num2, const string & rest) {
    if (num1.size()>1 && num1[0]=='0' || num2.size()>1 && num2[0]=='0') return false;
    const std::string sum = AddNum(num1,num2);
    if (rest==sum) return true;
    if (rest.size()<sum.size() || rest.substr(0,sum.size()) != sum)
      return false;
    return Check(num2,sum,rest.substr(sum.size()));
  }
  std::string AddNum(const string & num1, const string & num2) {
    const std::size_t num1_size(num1.size()), num2_size(num2.size());
    std::string res("");
    std::size_t i1(num1_size-1),i2(num2_size-1);
    int carry(0);
    while (i1<num1_size || i2 < num2_size || carry) {
      int val(0);
      if (i1<num1_size) val += num1[i1--]- '0';
      if (i2<num2_size) val += num2[i2--]- '0';
      if (carry) val += carry;
      res.push_back('0'+val%10);
      carry = val/10;
    }
    std::reverse(res.begin(),res.end());
    return res;
  }
};
