Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

```
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
```

The total number of unique paths is 2.

__Note__: m and n will be at most 100.
  

# Solution
  
  
Well, this problem is similar to Unique Paths. The introduction of obstacles only changes the boundary conditions and make some points unreachable (simply set to 0).

Denote the number of paths to arrive at point (i, j) to be P[i][j], the state equation is ```P[i][j] = P[i - 1][j] + P[i][j - 1]``` if ```obstacleGrid[i][j] != 1``` and ```0``` otherwise.

Now let's finish the boundary conditions. In the Unique Paths problem, we initialize P[0][j] = 1, P[i][0] = 1 for all valid i, j. Now, due to obstacles, some boundary points are no longer reachable and need to be initialized to 0. For example, if obstacleGrid is like [0, 0, 1, 0, 0], then the last three points are not reachable and need to be initialized to be 0. The result is [1, 1, 0, 0, 0].

Now we can write down the following (unoptimized) code. Note that we pad the obstacleGrid by 1 and initialize dp[0][1] = 1 to unify the boundary cases.  

__Time complexity O(MN), space complexity O(MN)__  
  
```cpp
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
```
Well, the code is accepted but it has some obvious redundancy. There are two major concerns:

Each time when we update path[i][j], we only need path[i - 1][j] (at the same column) and path[i][j - 1] (at the left column), so it is unnecessary to maintain the full m*n matrix. Maintaining two columns is enough.
There are some cases that the loop can be terminated earlier. Suppose obstacleGrid = [[0, 1, 0, 0], [0, 1, 0, 0], [0, 1, 0, 0]], then we can see that it is impossible to reach the bottom-right corner after updating the second column since the number of paths to reach each element in the second column is 0.

Further inspecting, keeping two vectors only serve for the purpose of recovering pre[i], which is simply cur[i] before its update. So we can use only one vector and the space is further optimized.  
  
__Time complexity O(MN), space complexity O(N)__
 
  
```cpp
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
```
