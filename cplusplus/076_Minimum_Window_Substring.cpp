
class Solution {
public:
  string minWindow(string s, string t) {
    unordered_map<char, int> counter;
    for (char c : t) {
      ++ counter[c];
    }
    const std::size_t s_size(s.size()),t_size(t.size());
    std::size_t min_start(0),min_len(INT_MAX),remain(t_size),cur_start(0);
    for (std::size_t i=0;i<s_size;++i) {
      if (counter.count(s[i])!=0) {
        if (counter[s[i]]>0) --remain;
        -- counter[s[i]];
        while (remain==0) {
          if (counter.count(s[cur_start])!=0) {
            if (i-cur_start+1<min_len) {
              min_start = cur_start;
              min_len = i-cur_start+1;
            }
            ++ counter[s[cur_start]];
            if (counter[s[cur_start]]>0) ++ remain;
          }
          ++ cur_start;
        }
      }
    }
    return min_len==INT_MAX? "" : s.substr(min_start,min_len);
  }
};

/*
Using vector instead of hashmap could yield better performance here.
*/
class Solution {
public:
  string minWindow(string s, string t) {
    vector<int> counter(256,0);
    for (char c : t) {
      ++ counter[c];
    }

    int start(0),min_start(0),min_len(INT_MAX),count(t.size());
    for (int i=0;i<s.size();++i) {
      if(counter[s[i]] > 0) --count; // the char we need
      -- counter[s[i]];
      while (count==0) { //all chars have been found
        int cur_len = i-start+1;
        if (cur_len < min_len) {
          min_start = start;
          min_len = cur_len;
        }
        // begin increase start
        if (counter[s[start]]==0) {
          ++ count;
        }
        ++ counter[s[start]];
        ++ start;
      }
    }
    return min_len==INT_MAX? "" : s.substr(min_start,min_len);
  }
};
