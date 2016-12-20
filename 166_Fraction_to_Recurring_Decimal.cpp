class Solution {
public:
  string fractionToDecimal(int numerator, int denominator) {
    if (denominator == 0) return "INVALID";
    if (numerator == 0) return "0";
    std::string res("");
    int sign = (numerator<0 ^ denominator<0) ? -1 : 1;
    if (sign==-1) res.push_back('-');
    long abs_num(std::labs(numerator)), abs_deno(std::labs(denominator));
    res += std::to_string(abs_num/abs_deno);
    if (abs_num%abs_deno==0) return res;
    res.push_back('.');
    abs_num %= abs_deno;
    unordered_map<int,std::size_t> visited;
    while (abs_num) {
      if (visited.count(abs_num)!=0) {
        res.insert(res.begin()+visited[abs_num],'(');
        res.push_back(')');
        break;
      } else {
        visited[abs_num] = res.size();
        abs_num *= 10;
        res.push_back('0'+abs_num/abs_deno);
        abs_num %= abs_deno;
      }
    }
    return res;
  }
};
