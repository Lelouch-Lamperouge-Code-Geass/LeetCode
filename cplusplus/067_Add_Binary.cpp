class Solution {
public:
  string addBinary(string a, string b) {
    std::string res("");
    const std::size_t a_size(a.size()),b_size(b.size());
    std::size_t i(a_size-1),j(b_size-1);
    int carry(0);
    while (i<a_size || j<b_size || carry) {
      int cur_val(carry);
      if (i<a_size) cur_val += a[i--]-'0';
      if (j<b_size) cur_val += b[j--]-'0';
      res.push_back('0'+cur_val%2);
      carry = cur_val / 2;
    }
    std::reverse(res.begin(),res.end());
    return res;
  }
};
