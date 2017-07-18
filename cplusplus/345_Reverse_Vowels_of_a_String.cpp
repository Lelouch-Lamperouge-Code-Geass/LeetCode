class Solution {
public:
  string reverseVowels(string s) {
    if (s.empty()) return s;
    static const std::string VOWELS("aeiouAEIOU");
    std::size_t begin(0), end(s.size()-1);
    while (begin < end) {
      begin = s.find_first_of(VOWELS, begin);
      end = s.find_last_of(VOWELS, end);
      if (begin < end) {
        std::swap(s[begin], s[end]);
        ++ begin;
        -- end;
      }
    }
    return s;
  }
};
