class Solution {
public:
  bool isScramble(string s1, string s2) {
    // Make sure their length are the same
    const int s1_size(s1.size()), s2_size(s2.size());
    if(s1_size!=s2_size) return false;
    // If they are the same
    if (s1==s2) return true;
    
    // Not the same, let's make sure each char count are the same
    vector<int> counter(256,0);
    for (int i=0;i<s1_size;++i) {
      ++ counter[s1[i]];
      -- counter[s2[i]];
    }
    vector<int>::const_iterator non_zero = std::find_if_not(counter.begin(),counter.end(),
                                                            [](int x){return x!=0});
    if (non_zero!=counter.end()) return false;

    for (int i=1;i<s1_size;++i) {
      if ( isScramble(s1.substr(0,i),s2.substr(0,i) 
                      && isScramble(s1.substr(i),s2.substr(i)) )
           || isScramble(s1.substr(0,i),s2.substr(s1_size-i) 
                         && isScramble(s1.substr(i),s2.substr(0,s1_size-i)))
           ) return true;
    }
    return false;
  }
};
