class Solution {
public:
  string decodeString(string s) {
    std::size_t pos(0);
    return Decode(s, pos);
  }
private:
  std::string Decode(const std::string & s, std::size_t & pos) {
    std::string reval("");
    const std::size_t s_size(s.size());
    while (pos < s_size && s[pos] != ']') { //alpha
      if (std::isalpha(s[pos])) {
        reval.push_back(s[pos++]);
      } else {
        // digit
        const std::size_t non_digit_pos = s.find_first_not_of("0123456789", pos);
        int num = std::stoi(s.substr(pos, non_digit_pos - pos));

        pos = non_digit_pos;

        ++ pos; // skip '['
        std::string internal_str = Decode(s, pos);
        ++ pos; // skip ']'

        for (int i = 0; i < num; ++i) {
          reval += internal_str;
        }
      }
    }

    return reval;
  }
};
