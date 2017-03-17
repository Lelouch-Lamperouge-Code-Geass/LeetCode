/* Solution 1 : 2 counters */
class Solution {
public:
  string getHint(string secret, string guess) {
    int bull(0),cow(0),n(secret.size());
    vector<int> s_counter(10,0), g_counter(10,0);
    for(int i=0;i<n;++i) {
      if(secret[i] == guess[i]) {
        ++ bull;
      } else {
        ++ s_counter[secret[i]-'0'];
        ++ g_counter[guess[i]-'0'];
      }
    }

    for(int i=0;i<=9;++i) {
      cow += std::min(s_counter[i],g_counter[i]);
    }

    return std::to_string(bull)+"A"+std::to_string(cow)+"B";
  }
};

/* Solution 2 : 1 counter */
class Solution {
public:
  string getHint(string secret, string guess) {
    int bulls(0),cows(0);
    std::vector<int> count(10,0);
    for(std::size_t i=0;i<secret.size();++i){
      if(secret[i]==guess[i]){
        ++ bulls;
      } else {
        if(++ count[secret[i]-'0'] <= 0) ++ cows;
        if(-- count[guess[i]-'0'] >= 0) ++ cows;
      }
    }
    return std::to_string(bulls) + "A" + std::to_string(cows) + "B";
  }
};
