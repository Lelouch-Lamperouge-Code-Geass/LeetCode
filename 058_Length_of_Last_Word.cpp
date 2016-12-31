class Solution {
public:
  int lengthOfLastWord(string s) {
    int end(s.size()-1);
    while (end>=0 && !std::isalpha(s[end])) -- end;
    if (end==-1) return 0;
    int start = end;
    while (start-1>=0 && std::isalpha(s[start-1])) -- start;
    return end - start + 1;
  }
};
