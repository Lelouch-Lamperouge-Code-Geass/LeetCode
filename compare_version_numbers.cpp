// Copyright (C) 2016 by Yang Liu
class Solution {
public:
  int compareVersion(string version1, string version2) {
    const int n1(version1.size()), n2(version2.size());
    for ( int i(0),j(0); i<n1 || j<n2; ) {
      int val1(0),val2(0);
      while(i<n1 && version1[i]!='.') val1 = val1*10 + version1[i++] - '0';
      while(j<n2 && version2[j]!='.') val2 = val2*10 + version2[j++] - '0';
      if (val1>val2) return 1;
      if (val1<val2) return -1;

      ++ i, ++j; //skip '.'
    }

    return 0;
  }
};
