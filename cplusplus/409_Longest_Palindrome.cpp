class Solution {
public:
  int longestPalindrome(string s) {
    int reval(0);
    int counter[256] = {0};

    for (char c : s) {
      ++ counter[c];
    }

    for (int i = 0; i < 256; ++i) {
      if (counter[i] > 0 && counter[i] % 2 == 0 ) reval += counter[i];
      if (counter[i] > 1 && counter[i] % 2 == 1 ) reval += counter[i] - 1;
    }

    if (reval < s.size()) reval += 1;

    return reval;
  }
};
