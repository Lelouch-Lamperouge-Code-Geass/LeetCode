/***
To get max length of increasing sequences:

Do DFS from every cell
Compare every 4 direction and skip cells that are out of boundary or smaller
Get matrix max from every cell's max
Use matrix[x][y] <= matrix[i][j] so we don't need a visited[m][n] array
The key is to cache the distance because it's highly possible to revisit a cell
***/

class Solution {
public:
  int longestIncreasingPath(vector<vector<int>>& matrix) {
    if (matrix.empty()) return 0;
    const std::size_t row_size(matrix.size()), col_size(matrix[0].size());
    vector<vector<int>> memoization(row_size, vector<int>(col_size,0));
    int reval(0);
    for (std::size_t i = 0; i < row_size; ++i) {
      for (std::size_t j = 0; j < col_size; ++j) {
        reval = std::max(reval, LongestPathForCell(matrix,i,j,memoization));
      }
    }
    return reval;
  }

  int LongestPathForCell(vector<vector<int>>& matrix, std::size_t row, std::size_t col,
                         vector<vector<int>> & memoization) {
    if (memoization[row][col] != 0) return memoization[row][col];
    int reval(1);
    int cur_val = matrix[row][col];
    matrix[row][col] = INT_MIN;
    if(row>0 && cur_val < matrix[row-1][col])
      reval = std::max(reval, 1 + LongestPathForCell(matrix, row-1, col, memoization));
    if(row+1<matrix.size() && cur_val < matrix[row+1][col])
      reval = std::max(reval, 1 + LongestPathForCell(matrix, row+1, col, memoization));
    if(col>0 && cur_val < matrix[row][col-1])
      reval = std::max(reval, 1 + LongestPathForCell(matrix, row, col-1, memoization));
    if(col+1<matrix[0].size() && cur_val < matrix[row][col+1])
      reval = std::max(reval, 1 + LongestPathForCell(matrix, row, col+1, memoization));
    matrix[row][col] = cur_val; // revert back
    memoization[row][col] = reval; // Memoize the result
    return reval;
  }
};
