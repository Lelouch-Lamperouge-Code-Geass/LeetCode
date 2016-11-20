class Solution {
 public:
  void reverseWords(string& s) {
    std::reverse(s.begin(), s.end());
    const int n(s.size());
    int index(0);
    for (int i = 0; i < n; ++i) {
      if (s[i] != ' ') {
        if (index != 0) s[index++] = ' ';
        int j = i;
        while (j < n && s[j] != ' ') s[index++] = s[j++];
        std::reverse(s.begin() + index - (j - i), s.begin() + index);
        i = j;
      }
    }
    s.erase(s.begin() + index, s.end());
  }
};
