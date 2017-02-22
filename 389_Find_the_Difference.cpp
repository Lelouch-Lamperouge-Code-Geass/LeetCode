/***
   Solution 1 : bit manipulation
 ***/

class Solution {
public:
  char findTheDifference(string s, string t) {
    char reval(0);
    for (char c : s) {
      reval  ^= c;
    }

    for (char c : t) {
      reval  ^= c;
    }

    return reval;
  }
};


/***
  Solution 2 : use counter
 ***/

class Solution {
public:
  char findTheDifference(string s, string t) {
    std::vector<int> counter(256,0);
    for (char c : s) {
      ++ counter[c];
    }

    for (char c : t) {
      -- counter[c];
    }

    auto iter = std::find_if(counter.begin(), counter.end(), [](int val){ return val != 0;});
    return char(iter - counter.begin());
  }
};
