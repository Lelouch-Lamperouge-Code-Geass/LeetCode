class Solution {
public:
  int firstUniqChar(string s) {
    std::vector<int> counter(256,0);
    for (char c : s) {
      ++ counter[c];
    }

    for (std::size_t index = 0, s_size(s.size()); index < s_size; ++index) {
      if (counter[s[index]] == 1) {
        return index;
      }
    }

    return -1;
  }
};
