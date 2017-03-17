class Solution {
public:
  void reverseWords(string &s) {
    std::reverse(s.begin(),s.end());
    const std::size_t n (s.size());
    std::size_t index(0);
    for (std::size_t i=0;i<n;++i) {
      if (s[i]!=' ') {
        if (index!=0) s[index++] = ' ';
        std::size_t j = i;
        while (j<n && s[j]!=' ') s[index++] = s[j++];
        std::reverse( s.begin()+index-(j-i) , s.begin()+index );
        i = j;
      }
    }
    s.erase(s.begin()+index,s.end());

  }
};
