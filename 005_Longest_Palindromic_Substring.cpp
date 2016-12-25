class Solution {
public:
  string longestPalindrome(string s) {
    std::size_t start(0),len(0),s_size(s.size());
    for (std::size_t i=0;i<s_size; ) {
      std::size_t left(i),right(i);
      while(right+1<s_size && s[right+1]==s[i]) ++ right;
      i = right + 1;
      while(left-1<s_size && right+1<s_size && s[left-1]==s[right+1])
        --left, ++ right;
      if (right-left+1>len) {
        start = left;
        len = right-left+1;
      }

    }
    return s.substr(start,len);
  }
};
