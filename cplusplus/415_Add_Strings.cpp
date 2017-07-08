// Notice that in the description, it says
// "The length of both num1 and num2 is < 5100."
// Therefore, we can use integer to represt the index here.
// int range [-2147483648 to 2147483647]
// It's always good to ask interviewer what is the length range of string.
// If super long string is possible, we need use std::size_t.
class Solution {
public:
  string addStrings(string num1, string num2) {
    if (num1.empty()) return num2;
    if (num2.empty()) return num1;
    std::string reval(num1.size() + num2.size(),' ');
    int carry(0);
    int index1(num1.size() - 1), index2(num2.size() - 1);
    int index(reval.size() - 1);
    while (index1 >= 0 || index2 >= 0 || carry > 0) {
      int cur_val(0);
      if (index1 >= 0) cur_val += (num1[index1--] - '0');
      if (index2 >= 0) cur_val += (num2[index2--] - '0');
      cur_val += carry;

      reval[index--] = ('0' + cur_val % 10);
      carry = cur_val / 10;
    }

    std::size_t nonzero_pos = reval.find_first_not_of(" 0");
    if (nonzero_pos == std::string::npos) return "0";
    return reval.substr(nonzero_pos, reval.size() - nonzero_pos);
  }
};
