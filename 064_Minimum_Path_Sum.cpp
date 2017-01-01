/*
Space complexity O(MN)
*/
class Solution {
public:
  int minPathSum(vector<vector<int>>& grid) {
    if(grid.empty()) return 0;
    const std::size_t row_size(grid.size()), col_size(grid[0].size());
    vector< vector<int> > min_sum(row_size+1,vector<int>(col_size+1,INT_MAX));
    min_sum[0][1] = 0;
    for (int i=1;i<=row_size;++i) {
      for (int j=1; j<=col_size; ++j) {
        min_sum[i][j] = std::min(min_sum[i-1][j],min_sum[i][j-1]) + grid[i-1][j-1];
      }
    }

    return min_sum[row_size][col_size];
  }
};

/*
space complexity O(N)
*/
class Solution {
public:
  int minPathSum(vector<vector<int>>& grid) {
    if(grid.empty()) return 0;
    const std::size_t row_size(grid.size()), col_size(grid[0].size());
    vector<int> min_sum(col_size,0);
    for (std::size_t i=0;i<col_size;++i) min_sum[i] = i!=0? min_sum[i-1]+grid[0][i] : grid[0][i];
    for (std::size_t i=1;i<row_size;++i) {
      for (std::size_t j=0;j<col_size;++j) {
        if (j!=0) {
          min_sum[j] = std::min(min_sum[j-1],min_sum[j]) + grid[i][j];
        }  else {
          min_sum[j] +=  grid[i][j];
        }
      }
    }
    return min_sum[col_size-1];
  }
};
