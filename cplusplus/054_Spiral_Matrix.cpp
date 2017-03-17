class Solution {
public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if (matrix.empty()) return vector<int>();
    vector<int> res;
    int row_size(matrix.size()), col_size(matrix[0].size());
    int start_row(0),end_row(row_size-1),start_col(0),end_col(col_size-1);

    while (start_row<=end_row && start_col<=end_col) {
      // top row
      for (int i=start_col;i<=end_col;++i) res.push_back(matrix[start_row][i]);
      ++ start_row;
      if (start_row>end_row) break;

      // right-most column
      for (int i=start_row;i<=end_row;++i) res.push_back(matrix[i][end_col]);
      -- end_col;
      if (start_col>end_col) break;

      // bottom row
      for (int i=end_col;i>=start_col;--i) res.push_back(matrix[end_row][i]);
      -- end_row;
      if (start_row>end_row) break;

      // left-most column
      for (int i=end_row;i>=start_row;--i) res.push_back(matrix[i][start_col]);
      ++ start_col;
      if (start_col>end_col) break;
    }
    return res;
  }
};
