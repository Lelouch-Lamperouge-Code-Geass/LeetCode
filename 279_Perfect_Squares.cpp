/* Solution 1 */
class Solution {
public:
  int numSquares(int n) {
    vector<int> dp(n+1,INT_MAX);
    dp[0] = 0;
    for (int i=1;i<=n;++i) {
      int val = INT_MAX;
      for (int j=1;j*j<=i;++j) {
        val = std::min(dp[i-j*j]+1,val);
      }
      dp[i] = val;
    }
    return dp[n];
  }
};

/* Solution 2, optimize on solution 1 */
class Solution {
public:
  int numSquares(int n) {
    static vector<int> dp {0};
    while (dp.size() <= n) {
      int m = dp.size(), squares = INT_MAX;
      for (int i=1; i*i<=m; ++i)
        squares = min(squares, dp[m-i*i] + 1);
      dp.push_back(squares);
    }
    return dp[n];
  }
};
