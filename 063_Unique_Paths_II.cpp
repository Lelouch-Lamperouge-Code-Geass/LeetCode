/*
Space complexity O(MN)
*/
class Solution {
public:
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if(obstacleGrid.empty()) return 0;
    const std::size_t row_size(obstacleGrid.size()),col_size(obstacleGrid[0].size());
    vector<vector<int>> dp(row_size+1,vector<int>(col_size+1,0));
    dp[0][1] = 1;
    for(int i=1;i<=row_size;++i){
      for(int j=1;j<=col_size;++j){
        if(obstacleGrid[i-1][j-1]==1){
          dp[i][j] = 0;
        } else {
          dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
      }
    }
    return dp[row_size][col_size];
  }
};

/*
Space complexity O(N)
 */
class Solution {
public:
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    if (obstacleGrid.empty()) return 0;
    const std::size_t row_size(obstacleGrid.size()),col_size(obstacleGrid[0].size());
    vector<int> path_count(col_size,0);
    for (std::size_t i=0;i<col_size && obstacleGrid[0][i]==0 ;++i) path_count[i] = 1;
    for (std::size_t i=1;i<row_size;++i) {
      for (std::size_t j=0;j<col_size;++j) {
        if (obstacleGrid[i][j]==1) {
          path_count[j] = 0;
        } else {
          path_count[j] = j==0? path_count[j] : path_count[j]+path_count[j-1] ;
        }
      }
    }
    return path_count[col_size-1];
  }
};
