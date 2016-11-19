// Copyright (C) 2016 by Yang Liu

/*
Solution 1
 */
bool wordBreak(string s, unordered_set<string>& wordDict) {
  const int N(s.size());
  std::vector<bool> dp(N+1,false);
  dp[0] = true;
  for(int i=1;i<=N;++i){
    for(int j=i-1;j>=0;--j){
      if( dp[j] && wordDict.find( s.substr(j,i-j) ) != wordDict.end()){
        dp[i] = true;
        break;
      }
    }
  }
  return dp[N];
}
/*
Solution 2
*/
bool wordBreak(string s, unordered_set<string>& wordDict) {
  const int n(s.size());
  vector<bool> dp(n+1,false);
  dp[0] = true;
  for (int i=0; i<n; ++i) {
    for (int len = n-i;len>=1;--len) {
      if (dp[i] && wordDict.find(s.substr(i,len))!= wordDict.end()) {
        dp[i+len] = true;
      }
    }
  }
  return dp[n];
}
