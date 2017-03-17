class Solution {
public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty()) return false;
    const int row_size(matrix.size()),col_size(matrix[0].size());
    for ( int row(0),col(col_size-1);row<row_size && col>=0; ) {
      const int cur_val = matrix[row][col];
      if (cur_val == target) {
        return true;
      } else if(cur_val>target){
        -- col;
      } else {
        ++ row;
      }
    }
    return false;
  }
};
